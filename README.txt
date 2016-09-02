
Name: Lauren Miller
Assignment: Programming Assignment #1 
Class: CS 372 - Introduction to Computer Networks
Date: 7/21/2016

References: http://www.linuxhowtos.org/C_C++/socket.htm, https://docs.python.org/2/howto/sockets.html, http://www.tutorialspoint.com/python/python_networking.htm  

Instructions
1) Compile chatclient.c from the command line with "gcc -o chatclient chatclient.c" (optional)
2) Run chatserve from the command line with "python chatserve.py [port_number]", replacing [port_number] with an available port number
3) Run chatclient from the command line with "./chatclient [hostname] [port]", replacing [hostname] with the name of the host where chatserve is run and [port] with the port number used by chatserver. You can use localhost as the hostname if chatclient and chatserver are run on the same host.
4) Input handles when prompted.
5) Input messages when prompted, or "\quit" to end the connection between chatserve and chatclient and to stop chatclient. Chatserve will continue running and can accept new connections.
6) Send a SIGINT to chatserver to end it.

