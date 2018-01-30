import sys

from src.myserver import *


def main():

	#create an server socket
	port = int(sys.argv[1])
	
	server = Myserver(port)

	print "Http server is now open..."

	server.run()


if __name__ == '__main__':
	main()
