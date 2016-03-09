//
//  Server code
//
//  Socket portions used from http://www.linuxhowtos.org/C_C++/socket.htm
//

#include "globals.h"
#include "Game.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// Established used variables
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n;
Game new_game;


// Display errors from socket programming
void socket_error(const char *msg)
{
    perror(msg);
    exit(1);
}


// Output to socket
bool socket_output(char* out){
    if(write(newsockfd, out, out.length()) == -1){
        socket_error("ERROR: Unable to output to socket");
        return false;
    }
    
    return true;
}


// Check if a string matched a known difficulty
bool is_difficulty(string d){
    if(d=="easy"||d=="medium"||d=="hard"){
        return true;
    } else{
        return false;
    }
}


// Check if a string matches the IPv4 format
bool is_ip(string s){
    char* temp;
    vector<string> ips;
    
    temp = strtok((char*)s.c_str(), ".");
    while (temp != NULL){
        ips.push_back(temp);
        temp = strtok (NULL, ".");
    }
    if(ips.size()!=4){
        //IP address did not have correct amount of sets of numbers
        error = 6;
        return false;
    }
    char *ptr;
    for(int i = 0; i<ips.size();i++){
        if(atoi(ips[i].c_str())==0 && ips[i].c_str()!="0"){ //NOT AN INTEGER
            sprintf(out_buffer, "In an IP check: %s is not an Integer", ips[i].c_str());
            output_function(7);
            return false;
        } else if(atoi(ips[i].c_str())<=255){ //An IP address must not go beyond 255
            //Do nothing
        } else{
            sprintf(out_buffer, "IP is out of range");
            output_function(8);
            return false;
        }
    }
    return true;
}


// Check if a string looks to be a hostname
bool is_hostname(string h){
    if(h.size()>=49){
        sprintf(out_buffer, "Hostname cannot exceed 49 characters");
        output_function(9);
        return false;
    }
    for(int i=0; i<h.size();i++){
        if(!isalnum(h[i])&&(h[i]!='-')){
            sprintf(out_buffer, "%c  is an invalid character for a hostname",h[i]);
            output_function(10);
            return false;
        }
    }
    return true;
}


// Check if a string is either a hostname or IPv4 address
bool is_server(string s){
    if(is_ip(s) || is_hostname(s)){
        error = 0;
        return true;
    } else{
        if(error=6){ //Prevent false negatives in Output.txt
            sprintf(out_buffer, "IP address did not have correct amount of sets of numbers");
            output_function(6);
        }
        //Error is given by is_ip/is_hostname
        return false;
    }
}


// Check if a string containing a port checks out
bool is_port(string p){
    for(int i=0; i<p.size();i++){
        if(!isdigit(p[i])){
            sprintf(out_buffer, "%c is not a valid character in a port",p[i]);
            output_function(11);
            return false;
        }
    }
    if(atoi(p.c_str())>0){
        return true;
    } else{
        sprintf(out_buffer, "A port must be a postive integer.");
        output_function(12);
        return false;
    }
}


// Check if a string matches a known direction
bool is_dir(string d){
    return (d=="fwd"||d=="left"||d=="right");
}


// Take a string and output the direction
DIRECTION to_dir(string d){
    if(d=="fwd"){
        return FWD;
    } else if(d=="left"){
        return LEFT;
    } else if(d=="right"){
        return RIGHT;
    }
}


// Take a command and direct it to the correct location
void do_command(vector<string> command_line){
    if(command_line.size()==0){
        sprintf(out_buffer, "No input was given");
        output_function(22);
    } else if(command_line[0]=="exit"){//Checking for "EXIT" command - Preventing SegFault
        if(command_line.size()==1){
            output<<"=-=-=-=-=-=-EXITED-=-=-=-=-=-=";
            output.close();
            exit(0);
        } else{
            sprintf(out_buffer, "Exit had too many arguments");
            output_function(1);
        }
    } else if(command_line[0]==";"){
        output<<"COMMENT: ";
        printf("\n");
        string single_string;
        single_string.push_back(';');
        single_string.push_back(' ');
        if(command_line.size()==1){
            output<<"EMPTY COMMENT";
        }
        for(int i=1; i<command_line.size(); i++){
            output<<command_line[i].c_str()<<" ";
            for(int g=0;g<command_line[i].size(); g++){
                single_string.push_back(command_line[i][g]);
            }
            single_string.push_back(' ');
        }
        cout<<endl<<single_string<<endl;
        output<<endl;
    } else if(command_line[0]=="display"){
        if(command_line.size()==1){
            new_game.display_toggle();
        } else{
            sprintf(out_buffer, "Display had too many arguments");
            output_function(2);
        }
    } else if(command_line[0]=="undo"){
        if(command_line.size()==1){
            new_game.undo_two_turns();
        } else{
            sprintf(out_buffer, "Undo had too many arguments");
            output_function(3);
        }
    } else if(command_line[0]=="human-ai"){
        if(command_line.size()==2){
            if(is_difficulty(command_line[1].c_str())){
                /*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
                new_game.set_game_type(HA, EASY);
            } else{
                sprintf(out_buffer, "%s  is not a difficulty", command_line[1].c_str());
                output_function(4);
            }
        } else{
            sprintf(out_buffer, "Human-AI had incorrect amount of arguments");
            output_function(5);
        }
    } else if(command_line[0]=="ai-ai"){
        if(command_line.size()==6){
            if(is_server(command_line[1])){
                if(is_port(command_line[2])){
                    if(is_difficulty(command_line[4])&& is_difficulty(command_line[5])){
                        new_game.set_game_type(AA, EASY);
                        error=0;
                        /*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
                    } else{
                        sprintf(out_buffer, "Incorrect input for difficulty");
                        output_function(13);
                    }
                } else{
                    sprintf(out_buffer, "%s is not a port", command_line[2].c_str());
                    output_function(14);
                }
            } else{
                output<<command_line[1]<<" is not a server"<<endl;
                printf("%s is not a server", command_line[1].c_str());
                //Error given in is_server
            }
        } else{
            sprintf(out_buffer, "AI-AI had incorrect amount of arguments");
            output_function(15);
        }
    } else if(command_line[0].size()==2){//Is this a MOVE?
        if(command_line.size()==2){
            char tc = command_line[0][0];//tc, standing for Temporary Char
            if(tc=='a'||tc=='b'||tc=='c'||tc=='d'||tc=='e'||tc=='f'||tc=='g' || tc=='h'){
                char t2 = command_line[0][1];//t2, standing for Temporary Char #2
                if(t2=='1'||t2=='2'||t2=='3'||t2=='4'||t2=='5'||t2=='6'||t2=='7'||t2=='8'){
                    if(is_dir(command_line[1])){
                        if(new_game.valid_move(t2-48, tc, to_dir(command_line[1].c_str()))){
                            new_game.update(tc, t2-48, to_dir(command_line[1].c_str()));
                        } else{
                            sprintf(out_buffer, "%c%c %s is an invalid move\n", tc,t2, command_line[1].c_str());
                            output_function(16);
                        }
                    } else{
                        sprintf(out_buffer, "%s is not a valid direction", command_line[1].c_str());
                        output_function(17);
                    }
                } else{
                    sprintf(out_buffer, "%c  is not a valid row number", t2);
                    output_function(18);
                }
            } else{
                sprintf(out_buffer, "%c  is not a valid column letter", tc);
                output_function(19);
            }
        } else{
            sprintf(out_buffer, "Move had incorrect amount of arguments");
            output_function(20);
        }
    }  else if(command_line.size()==1){//Is this a MOVE?
        output<<"PASSWORD: "<<command_line[0]<<endl;
        /*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
    }else{
        sprintf(out_buffer, "%s is not a valid command", command_line[0].c_str());
        output_function(21);
    }
}


int main(){
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	sprintf(temp_buffer, "The current file is: %s", __FILE__);//For use for OUTPUT.txt
	def_vars();//Defines variables for nicer Main()
	signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
	signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
	//------^-^-^-^AT-BEGINING-^-^-^-^-----//
	
	
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