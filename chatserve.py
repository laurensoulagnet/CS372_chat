#!/usr/bin/python

#Name: Lauren Miller
#Assignment: Programming Assignment #1 
#Class: CS 372 - Introduction to Computer Networks
#Date: 7/21/2016

#References: https://docs.python.org/2/howto/sockets.html, http://www.tutorialspoint.com/python/python_networking.htm

import socket #the socket module
import sys #command line args
import signal #catching signals

#defining signal catcher, so python doesn't print unnecessary error code
def signal_handler(signal, frame):
	print("")
	quit()
	
signal.signal(signal.SIGINT, signal_handler)

#confirming the correct number of args
if len(sys.argv) == 1:
	print("Correct usage: chatclient [hostname] [port]\n")
	quit()
	
handle = raw_input("\nHandle: ")

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #creating an INET, streaming socket
host = socket.gethostname() #getting local machine name
portno = int(sys.argv[1]) #getting portno

sock.bind((host, portno)) #binding to the port

sock.listen(5) #queue for up to 5 connections

while True: #always looping through accepting connections
	
	conn, addr = sock.accept() #connecting with a client
	
	keep_connection = True
	while keep_connection:

		#getting the initial portno message
		client_message = conn.recv(10) #receiving from the client - the original portno
		print("\nConnection established using port " + client_message + ".\n")
		
		continue_exchange = True
		while continue_exchange:
			
			client_message = conn.recv(513) #receiving from the client - a message (up to 500 characters), client handle, >, space, and \0
			
			if client_message == "\\quit":#checking if the client wants to quit
			
				continue_exchange = False
				keep_connection = False
				
			else: #if the client wants to continue

				print(client_message)
				
				server_message = raw_input(handle + "> ") #getting the server's message 
				
				if server_message == "\\quit": #checking if the server wants to quit, passing along the message if so
					
					full_server_message = server_message
					continue_exchange = False
					keep_connection = False
					
				else: #if the server wants to continue
					full_server_message = handle + "> " + server_message
				
				conn.send(full_server_message)

	conn.close() #closing the connection
	