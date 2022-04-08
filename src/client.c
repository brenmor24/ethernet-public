#define ENC28J60_DDR DDRB
#define ENC28J60_PORT PORTB
#define ENC28J60_SI_PIN_DDR DDB3
#define ENC28J60_SI_PIN PORTB3
#define ENC28J60_SO_PIN_DDR DDB4
#define ENC28J60_SCK_PIN_DDR DDB5
#define ENC28J60_SCK_PIN PORTB5

#define ENC28J60_RESET_PIN_DDR DDB0
#define ENC28J60_RESET_PIN PORTB0
#define ENC28J60_INT_PIN_DDR DDB1
#define ENC28J60_INT_PIN PORTB1
#define ENC28J60_CS_PIN_DDR DDB2
#define ENC28J60_CS_PIN PORTB2


#define NET_IP 192, 168, 1, 149
#define NET_MAC 0x74, 0x69, 69, 0x2D, 0x30, 0x31
#define NET_BUFFER_SIZE 400
#define TCP_MAX_CONNECTIONS 2


#define F_CPU 16000000UL

#include "../lib/lcd/HD44780.c"
#include "../lib/analog/analog_read.c"

#include "../lib/network/tcp.c"
#include "../lib/network/network.c"
#include <stdio.h>

unsigned char TcpOnNewConnection(const unsigned char connectionId){
    return NET_HANDLE_RESULT_DROP;
}

void TcpOnConnect(const unsigned char connectionId){}
void TcpOnIncomingData(const unsigned char connectionId, const unsigned char *data, unsigned short dataLength){}
void TcpOnDisconnect(const unsigned char connectionId){}

void TcpSynchNotPersitentClientExample(){
    unsigned char serverIp[IP_V4_ADDRESS_SIZE] = {192, 168, 1, 129};
    unsigned char clientConId = TcpConnect(serverIp, 5000, 6000);

    if(clientConId == TCP_INVALID_CONNECTION_ID){
        puts("Tcp connect error");
        return;
    }

    double voltage = (5.0)*(1024.0 - (double)ReadADC(5))/(1024.0);
    int volt_int = (int) (voltage*100);
    int whole = volt_int/100;
    int decimal = volt_int%100;

    LCD_Clear();
    LCD_GotoXY(0, 0);
    LCD_PrintString("VOLTAGE: ");
    LCD_PrintInteger(whole);
    LCD_PrintString(".");
    LCD_PrintInteger(decimal);
    LCD_PrintString("V");

    char volt_str[5];
    sprintf(volt_str, "%d", volt_int);

    if(!TcpSendData(clientConId, 5000, volt_str, strlen(volt_str))){
        TcpDisconnect(clientConId, 1000);
        puts("Send request error");
        return;
    }

    TcpDisconnect(clientConId, 5000);
    putchar('\n');
}

int main(){
    LCD_Setup();
    InitADC();
    NetInit();
    for(;;){
        // handle incoming packet in application
        NetHandleNetwork();

        TcpSynchNotPersitentClientExample();
        _delay_ms(1000);
    }
}
