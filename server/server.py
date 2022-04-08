import socket
from datetime import datetime

# create a socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# enable quick restart
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# set port number
port = 5000
sock.bind(('', port))

# set client connection queue size
sock.listen(5)

# loop and wait for new connections
try:
    while 1:
        newSocket, address = sock.accept()
        while 1:
            receivedData = newSocket.recv(1024)
            if not receivedData: break
            clean = receivedData.decode("utf-8")

            out_str = ""

            if len(clean) == 0:
                out_str = "0.00"
            elif len(clean) == 1:
                out_str = f"0.0{clean}"
            elif len(clean) == 2:
                out_str = f"0.{clean}"
            else:
                out_str = f"{clean[0]}.{clean[1]}{clean[2]}"
            
            now = datetime.now()
            dt_string = now.strftime("[%Y-%m-%d %H:%M:%S]")
            print(f"{dt_string} VOLTAGE -> {out_str}V")
        newSocket.close()
finally:
    sock.close()
