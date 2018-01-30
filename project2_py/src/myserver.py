import socket
import threading

from response import *

class Myserver(object):
	def __init__(self, port):

		#create an server socket
		self.__serversocket = socket.socket(
			socket.AF_INET, socket.SOCK_STREAM)
		#bind the socket to host and port
		self.__serversocket.bind(('', port)) #do not bind to ip
		#become a server socket
		self.__serversocket.listen(5)

	def run(self):
		while 1:
			(clientsocket, address) = self.__serversocket.accept()
			thread = threading.Thread(
				target = self.__process_thread__, args = (clientsocket, address))
			thread.start()


	def __process_thread__(self, clientsocket, address):
		text = clientsocket.recv(512)
		#print received text
		#print 'Message received from client:'

		# response to client
		r = Response(clientsocket, text)
		r.run()

		#close response socket
		clientsocket.close()
