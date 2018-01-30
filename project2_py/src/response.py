import re
import sys
import platform
import time

from files import *

class Response(object):
	def __init__(self, clnt_sock, buf):
		self.__f = Files()
		self.__clnt_sock = clnt_sock
		buf = re.split(r'[\s]', buf)
		if len(buf) > 2:
			self.__method = buf[0]
			self.__web = buf[1]
			self.__protocol = buf[2]
		else:
			self.__method = ""
			self.__web = ""
			self.__protocol = ""


	def run(self):
		content = self.__build_headline__() \
				+ "Connection: close\r\n" \
				+ self.__build_date__() \
				+ "Server: " + platform.uname()[1] \
					+ "/" + platform.uname()[2] + "\r\n" \
				+ self.__build_content_type__()

		if self.__f.redirected(self.__web):
			content += "Location: " + self.__build_body__()

		if self.__method == "GET" and self.__f.exist(self.__web):
			content += "\r\n" + self.__build_body__()

		self.__clnt_sock.send(content)


	def __build_headline__(self):
		string = self.__protocol + " "
		if self.__method == "GET" or self.__method == "HEAD":
			if self.__f.exist(self.__web):
				string += "200 OK\r\n"
			elif self.__f.redirected(self.__web):
				string += "301 Moved Permanently\r\n"
			else:
				string += "404 Not Found\r\n"
		else:
			if (self.__method == "POST" or self.__method == "PUT" or self.__method == "DELETE"
				or self.__method == "TRACE" or self.__method == "CONNECT"):
				string += "405 Method Not Allowed\r\n"
			else:
				string += "400 Bad Request\r\n"

		return string

	def __build_date__(self):
		string = "Date: " \
			+ time.strftime("%a, %d %b %Y %H:%M:%S %Z", time.localtime()) \
			+ "\r\n"

		return string


	def __build_content_type__(self):
		pos = self.__web.rfind('.')
		if pos != -1:
			string = self.__web[pos+1:]
		else:
			string = ""

		if string == "html":
			string = "text/" + string
		elif string == "txt":
			string = "text/plain"
		elif string == "pdf":
			string = "application/" + string
		elif string == "png" or string == "jpeg":
			string = "image/" + string
		else:
			string = "unknown"

		return "Content-Type: " + string + "\r\n"

	def __build_body__(self):

		return self.__f.mime(self.__web) 
