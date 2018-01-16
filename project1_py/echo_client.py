import sys
import socket

#read input arguments
hostname = sys.argv[1]
port = int(sys.argv[2])

def main():
	#infinite loop
	while 1:
		#create a client socket
		clientsocket = socket.socket(
			socket.AF_INET, socket.SOCK_STREAM)

		#connect to server
		clientsocket.connect((hostname, port))
		#send text to server
		print "Please input the text you want to send:"
		text = raw_input()
		clientsocket.send(text)
		#output echo from server
		echo_text = clientsocket.recv(512)
		print "Received text from server:"
		print echo_text+'\n'
		#disconnect
		clientsocket.close()

if __name__ == '__main__':
	main()
