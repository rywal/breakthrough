//
//  Server code
//
//  Socket portions used from http://www.linuxhowtos.org/C_C++/socket.htm
//

#include "Parser.h" //Game called here also
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


// Display errors from socket programming
void socket_error(const char *msg)
{
    perror(msg);
    exit(1);
}


int main(){
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	sprintf(temp_buffer, "The current file is: %s", __FILE__);//For use for OUTPUT.txt
	def_vars();//Defines variables for nicer Main()
	signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
	signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
	//------^-^-^-^AT-BEGINING-^-^-^-^-----//
	
	
	
	// Begin socket programming
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    
    // Create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        socket_error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5155;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    // Bind the socket to available address and port
    if (::bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        socket_error("ERROR on binding");
    
    // Wait for a client to connect; accept when they do
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        socket_error("ERROR on accept");
    
    // Read/Write with client
    string welcome = "PASSWORD";
    n = write(newsockfd, welcome.c_str(), welcome.length());
    if (n < 0) socket_error("ERROR writing to socket");
    
    bzero(buffer,256);
    
    n = read(newsockfd,buffer,255);
    if (n < 0) socket_error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    
    if (n < 0) socket_error("ERROR writing to socket");
    
    // Close socket when finished
    close(newsockfd);
    close(sockfd);
    
    // End socket programming
    
    
	//----------Example-use-of-parser----------//
//	while(1){
//		take_command(line_number);
//	}
	//----------------------------------------//
	
	
	
	
	
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	output<<"=-=-=-=-=-=-EXITED-=-=-=-=-=-=";
	output.close();
	//------^-^-^-^-^-AT-END-^-^-^-^-^------//
	return 0;
}