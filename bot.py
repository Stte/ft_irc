#!/usr/bin/python3

import socket
import argparse

parser = argparse.ArgumentParser(description='IRC Bot')

parser.add_argument('-p', type=int, required=True, help='Port to connect to')
parser.add_argument('-pw', type=str, required=True, help='Password for the server')

args = parser.parse_args()

botnick = "Spoof"
server = "localhost"
port = args.p
password = args.pw

global IRC
IRC = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IRC.connect((server, port))
IRC.send((f"PASS {password}\r\n").encode('utf-8'))
IRC.send((f"USER {botnick} {botnick} {botnick} {botnick}\r\n").encode('utf-8'))
IRC.send((f"NICK {botnick}\r\n").encode('utf-8'))

def ping(aswer):
	IRC.send((f"PONG :{aswer}\r\n").encode('utf-8'))

def sendmsg(msg, channel):
	IRC.send(("PRIVMSG "+ channel +" :"+ msg +"\r\n").encode('utf-8'))

def joinchan(chan):
	IRC.send(("JOIN "+ chan +"\r\n").encode('utf-8'))
	IRC.send(("PRIVMSG "+ chan +" :Hello! I am a bot.\r\n").encode('utf-8'))
	IRC.send(("PRIVMSG "+ chan +" :Type !quote to get a random quote.\r\n").encode('utf-8'))

def send_data(message):
	IRC.send((message + '\r\n').encode('utf-8'))

def main():
	while (1):
		ircmsg = ""
		ircmsg = IRC.recv(2048).decode('utf-8')
		ircmsg = ircmsg.strip('\n\r')
		if ircmsg.find("PING :") != -1:
			ping("Hehehe")
		if (ircmsg.find("INVITE") != -1):
			joinchan("#" + ircmsg.split('#')[1])
		if ircmsg.find("PRIVMSG") != -1:
			channel = ircmsg.split('PRIVMSG',1)[1].split(':',1)[0].strip()
			message = ircmsg.split('PRIVMSG',1)[1].split(':',1)[1].strip()
			if (message.find('!quote') != -1):
				sendmsg("Insanity is doing the same thing over and over again and expecting different results.", channel)

if __name__=="__main__":
	main()
