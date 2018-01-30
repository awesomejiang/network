import re
import os

class Files(object):
	__redirect_map = {}
	def __init__(self):
		filename = "www/redirect.defs"

		with open(filename) as f:
			for line in f:
				split = re.split(r'[\s]', line)
				self.__redirect_map[split[0]] = split[1]



	def exist(self, string):

		return os.path.isfile("www"+string)

	def redirected(self, string):

		return self.__redirect_map.get(string) != None

	def mime(self, string):
		if self.redirected(string):
			return self.__redirect_map.get(string) + "\r\n"
		else:
			filename = "www" + string
			with open(filename) as f:
				return f.read() + "\r\n"


