import sys
import socket
import threading

#create an server socket
port = int(sys.argv[1])


def process_thread(clientsocket, address):
	text = clientsocket.recv(512)
	#print received text
	print 'Message received from client:'
	print text+'\n'
	#send it back to client
	clientsocket.send(text)
	clientsocket.close()

def main():
	#create an server socket
	serversocket = socket.socket(
		socket.AF_INET, socket.SOCK_STREAM)
	#bind the socket to host and port
	serversocket.bind(('localhost', port))
	#become a server socket
	serversocket.listen(5)

	#infinite loop
	while 1:
		(clientsocket, address) = serversocket.accept()
		thread = threading.Thread(
			target = process_thread, args = (clientsocket, address))
		thread.start()


if __name__ == '__main__':
	main()