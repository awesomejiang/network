import sys
import getopt
import socket
import time
import threading

#globals
lck = threading.Lock()
rtt = []
thread_end_number = 0



#arguments
server_ip = "localhost"
server_port = 8080
count = 10
period = 1.0
timeout = 10.0



def get_args():
	try:
		options, args = getopt.getopt(sys.argv[1:], "h", (
			["help", "server_ip=", "server_port=", "count=", "period=", "timeout="]))
	except getopt.GetoptError:
		print "Cannot parse cmd-line options properly."
		sys.exit()

	global server_ip, server_port, count, period, timeout
	for name, value in options:
		if name in ("-h", "--help"):
			usage()
			sys.exit()
		if name in ("--server_ip"):
			server_ip = value
		if name in ("--server_port"):
			server_port = int(value)
		if name in ("--count"):
			count = int(value)
		if name in ("--period"):
			period = float(value)/1000
		if name in ("--timeout"):
			timeout = float(value)/1000

def usage():
	print "Here is the usage function."
	print "Usage: python " + sys.argv[0] + " [options]"
	print "[options]:"
	print "-h/--help:                       call usage function"
	print "--server_ip=<server ip addr>:    default: hostname"
	print "--server_port=<server port>:     default: 8080"
	print "--count=<number of pings>:       default: 10"
	print "--period=<wait interval>:        default: 1000(ms)"
	print "--timeout=<timeout>:             default: 10000(ms)"



now = lambda : int(round(time.time()*1000))

def send_msg(seq_num):
	#create a socket
	clientsocket = socket.socket(
		socket.AF_INET, socket.SOCK_DGRAM)

	#set timeout
	clientsocket.settimeout(timeout)

	#send msg to server
	time_begin = now()
	text = "PING\t" + str(seq_num) + "\t" + str(time_begin) + "\r\n"
	clientsocket.sendto(text, (server_ip, server_port))

	#try to recv response from server
	global rtt, thread_end_number
	try:
		msg = clientsocket.recvfrom(server_port)[0]
	except socket.error, e:
		pass
	else:
		#update the val into rtt
		elapsed_time = now() - time_begin
		lck.acquire()
		rtt.append(elapsed_time)
		lck.release()

		#print result
		print ("PONG\t" + server_ip + ":\tseq=" + str(seq_num)
				 + "\ttime=" + str(elapsed_time) + "ms")

	#close socket
	clientsocket.close()

	#thread_end ++
	lck.acquire()
	thread_end_number += 1
	lck.release()



def main():
	#set arguments
	get_args()

	time_begin = now()

	print "PING\t" + server_ip

	for i in xrange(0, count):
		t = threading.Timer(i*period, send_msg, args = [i+1])
		t.start()

	#wait until all threads end
	while thread_end_number != count:
		pass

	#print stats
	print "\n--- " + server_ip + " ping statistics ---"
	print (str(count) + " transmitted, "
			+ str(len(rtt)) + " received, "
			+ (str((count-len(rtt))*100/count) if count>0 else "-")
			+ "% loss, time " + str(now()-time_begin) + " ms")
	print ("rtt min/avg/max = "
			+ (str(min(rtt)) if len(rtt)>0 else "0") + "/"
			+ (str(sum(rtt)/len(rtt)) if len(rtt)>0 else "0") + "/"
			+ (str(max(rtt)) if len(rtt)>0 else "0") )



if __name__ == '__main__':
	main()