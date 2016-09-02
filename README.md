#A Chat System
A chat program with a C client program connecting to a Python server program, inputting the server program’s host and port number for each, to allow users of both to alternate sending messages and eventually terminate the chat. This assignment was intented to demonstrate the one of uses of TCP sockets.

#Instructions 
1) Compile chatclient.c from the command line with "gcc -o chatclient chatclient.c". (This is optional.)<br>
2) Run chatserve from the command line with "python chatserve.py [port_number]", replacing [port_number] with an available port number.<br>
3) Run chatclient from the command line with "./chatclient [hostname] [port]", replacing [hostname] with the name of the host where chatserve is run and [port] with the port number used by chatserver. You can use localhost as the hostname if chatclient and chatserver are run on the same host.<br>
4) Input handles when prompted.<br>
5) Input messages when prompted, or "\quit" to end the connection between chatserve and chatclient and to stop chatclient. Chatserve will continue running and can accept new connections.<br>
6) Send a SIGINT to chatserver to kill the program.<br>
