/*
Name: Lauren Miller
Assignment: Programming Assignment #1 
Class: CS 372 - Introduction to Computer Networks
Date: 7/21/2016

References: http://www.linuxhowtos.org/C_C++/socket.htm 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h>

//establishes a connection to the server, returns a file descriptor for the socket
int create_connection(char* hostname, int portno) {
	int sockfd;//the file descriptor for the socket
    struct sockaddr_in serv_addr;//the address for the socket to the server
    struct hostent* server;//the server to connect to, which will be localhost in tests
	
	//connecting to chatserve
    sockfd = socket(AF_INET, SOCK_STREAM, 0);//creating an INET, streaming socket
    if (sockfd < 0)  {
		printf("Error opening socket");
	}
	
    server = gethostbyname(hostname);//getting the server
	
    if (server == NULL) {
		printf("Error: no such host\n");
		exit(0);
    }
	
    //setting the address
    bzero((char *) &serv_addr, sizeof(serv_addr));//setting all the bytes to 0
    serv_addr.sin_family = AF_INET;//setting the type of address to connect with Internet Protocol v4 addresses
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);//copying over the server address
    serv_addr.sin_port = htons(portno);//converting to network byte order
	
	//connecting to the server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		printf("Error connecting\n");
		exit(0);
	}
	
	return sockfd;

}

int main(int argc, char *argv[])
{
    int sockfd;//the file descriptor for the socket
	int n;//returned from read
    char input_buffer[501];//text input by the client - including the message (up to 500), and \0
	char output_buffer[513];//text to/from the server - including the handle, >, space, message (up to 500), and \0
	char handle[11];//the input handle for the user - up to 10 chars, and \0
	char* port_string;//the string version of the port received
	int keep_connection;//measures whether the connection should be kept ongoing or not - as when \quit is input
	
    if (argc < 3) {
		printf("Correct usage: chatclient [hostname] [port]\n\n");
		exit(0);
    }

	sockfd = create_connection(argv[1], atoi(argv[2]));//getting the server, passing in hostname and port number
	
	//gettng the handle of the user - a one-word name, up to 10 characters
	printf("\nHandle: ");
	fgets(handle,sizeof(handle),stdin);
	printf("\n");
	handle[strlen(handle)-1] = '\0';//removing the newline picked up with fgets
	
	port_string = argv[2];//getting the string of the port number
	
	//the first write to the server - the port number
    n = write(sockfd,port_string,strlen(port_string));
    if (n < 0) {
		printf("Error writing to socket\n");
	}
	
	keep_connection = 1;
	while(keep_connection) {
		printf("%s> ", handle);

		//getting message to the server
		bzero(input_buffer,501);
		fgets(input_buffer,500,stdin);
		input_buffer[strlen(input_buffer)-1] = '\0';//removing the newline picked up with fgets
		
		if(strcmp(input_buffer, "\\quit") == 0) {//checking if the client wants to quit
			keep_connection = 0;
			n = write(sockfd,input_buffer,strlen(input_buffer));//telling the server the client's quitting
			if (n < 0) {
				printf("Error writing to socket\n");
			}
		}
		else {//if the client doesn't want to quit
		
			//copying handle into to server
			bzero(output_buffer,513);
			strcpy(output_buffer, handle);
			strcat(output_buffer, "> ");
			strcat(output_buffer, input_buffer);
		
			n = write(sockfd,output_buffer,strlen(output_buffer));
			if (n < 0) {
				printf("Error writing to socket\n");
			}
			
			//reading from the server
			bzero(output_buffer,513);
			
			n = read(sockfd,output_buffer,512);
			if (n < 0) {
				printf("Error reading from socket\n");
			}
			else if (n == 0) {//if the server returns an empty string - might happen with sigint
				keep_connection = 0;
			}
			else if(strcmp(output_buffer, "\\quit") == 0) {//checking if the server wants to quit
				keep_connection = 0;
			}
			else {//if the server doesn't want to quit
				printf("%s\n",output_buffer);
			}
			
		}
	}
	
	//closing the connection
	close(sockfd);
	
    return 0;
}
