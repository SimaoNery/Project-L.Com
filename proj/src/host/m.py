import socket

def send_byte_to_socket():
    # Define the target address and port
    host = 'localhost'
    port = 4321
    
    # Create a socket object
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # Connect to the server
        s.connect((host, port))
        
        # Define the byte to send
        byte_to_send = bytes([0xA0])
        
        # Send the byte
        s.sendall(byte_to_send)
        
        # Optional: Receive a response (if expected)
        # response = s.recv(1024)
        # print('Received', repr(response))

# Run the function to send the byte
send_byte_to_socket()
