import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 4321
BYTE_TO_SEND = b'\x20'

'''
Motor -> x61 x60
Luz -> x01 02 03 04 08 10 1F
buzina -> x21 
'''

def send_byte():
    try:
        # Create a socket object
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
           
        # Connect to the server
        sock.connect((SERVER_IP, SERVER_PORT))
           
        # Send the byte
        sock.sendall(BYTE_TO_SEND)
           
        print(f"Sent byte {BYTE_TO_SEND} to {SERVER_IP}:{SERVER_PORT}")
    except socket.error as e:
        print(f"Socket error: {e}")
    finally:
        # Close the socket
        sock.close()

if __name__ == "__main__":
    send_byte()