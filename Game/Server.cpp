//
//  Server code
//
//  Socket portions used from http://www.linuxhowtos.org/C_C++/socket.htm
//
#include "globals.h"
#include "Game.h"

#define BUFFER_SIZE 1024

// Socket variables
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[BUFFER_SIZE];
struct sockaddr_in serv_addr, cli_addr;
int n;
Game new_game;
string correct_password = "breakthrough";

// Globals from parser.h
int error = 0;
char out_buffer[50];
ofstream output;
int line_number = 1;
size_t buffer_size;
char temp_buffer[50];


void  ctrl_c(int signo){//This is to protect formatting of output
    if (newsockfd) {
        shutdown(newsockfd, 2);
    }
    
    if (sockfd) {
        shutdown(sockfd, 2);
    }
    if (signo == SIGINT){
        output<<"=-=-=-=-=-=-CTRL+C-=-=-=-=-=-=";
        output.close();
        exit(0);
    } else if(signo == SIGSEGV){
        if(error==0){
            printf("\n\nThere has been a Segmentation Fault with unknown error");
        }else{
            printf("\n\nThere has been a Segmentation Fault. The error code is: %d", error);
        }
        output<<"^-^-^-Segmentation Fault-^-^-^";
        output.close();
        exit(139);//System Error code
    }
}


// Prints error message buffer
void output_function(int err){
    printf("%s", out_buffer);
    output<<out_buffer<<endl;
    error=err;
}


// Display errors from socket programming
void socket_error(const char *msg)
{
    perror(msg);
    exit(1);
}


// Output to socket
bool socket_output(const char* out){
    if(write(newsockfd, out, strlen(out)) == -1){
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


// Take a string and output the difficulty
DIFFICULTY to_diff(string d){
    if(d=="easy"){
        return EASY;
    } else if(d=="medium"){
        return MEDIUM;
    } else if(d=="hard"){
        return HARD;
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
            socket_output("; IP address given is not an integer\nILLEGAL\n");
            return false;
        } else if(atoi(ips[i].c_str())<=255){ //An IP address must not go beyond 255
            //Do nothing
        } else{
            sprintf(out_buffer, "IP is out of range");
            output_function(8);
            socket_output("; IP address given is out of range\nILLEGAL\n");
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
        socket_output("; Hostname cannot exceed 49 characters\nILLEGAL\n");
        return false;
    }
    for(int i=0; i<h.size();i++){
        if(!isalnum(h[i])&&(h[i]!='-')){
            sprintf(out_buffer, "%c  is an invalid character for a hostname",h[i]);
            output_function(10);
            socket_output("; Invalid character given in hostname\nILLEGAL\n");
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
            socket_output("; IP address did not have correct format\nILLEGAL\n");
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
            socket_output("; Invalid character given in port number\nILLEGAL\n");
            return false;
        }
    }
    if(atoi(p.c_str())>0){
        return true;
    } else{
        sprintf(out_buffer, "A port must be a postive integer.");
        output_function(12);
        socket_output("; Port number must be positive\nILLEGAL\n");
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
bool do_command(vector<string> command_line){
    if(command_line.size()==0){
        socket_output("; No input was given\nILLEGAL\n");
        return true;
    } else if(command_line[0]=="exit"){//Checking for "EXIT" command - Preventing SegFault
        if(command_line.size()==1){
            socket_output("OK\n");
            output<<endl<<"=-=-=-=-=-=-EXITED-=-=-=-=-=-=";
            output.close();
            return false;
        } else{
            socket_output("; Exit had too many arguments\nILLEGAL\n");
            sprintf(out_buffer, "Exit had too many arguments");
            output_function(1);
        }
    } else if(command_line[0]==";"){
        socket_output("OK\n");
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
            socket_output("OK\n");
            new_game.display_toggle();
        } else{
            socket_output("; Display had too many arguments\nILLEGAL\n");
            sprintf(out_buffer, "Display had too many arguments");
            output_function(2);
        }
    } else if(command_line[0]=="undo"){
        if(command_line.size()==1){
            new_game.undo();
        } else{
            socket_output("; Undo had too many arguments\nILLEGAL\n");
            sprintf(out_buffer, "Undo had too many arguments");
            output_function(3);
        }
    } else if(command_line[0]=="human-ai"){
        if(command_line.size()==2){
            if(is_difficulty(command_line[1].c_str())){
                socket_output("OK\n");
                new_game.set_game_type(HA, EASY);
            } else{
                socket_output("; Not a valid difficulty\nILLEGAL\n");
                sprintf(out_buffer, "%s  is not a difficulty", command_line[1].c_str());
                output_function(4);
            }
        } else{
            socket_output("; Incorrect arguments\nILLEGAL\n");
            sprintf(out_buffer, "Human-AI had incorrect amount of arguments");
            output_function(5);
        }
    } else if(command_line[0]=="ai-ai"){
        if(command_line.size()==6){
            if(is_server(command_line[1])){
                if(is_port(command_line[2])){
                    if(is_difficulty(command_line[4])&& is_difficulty(command_line[5])){
                        // Setup our AI for the difficulty given
                        new_game.set_game_type(HA, to_diff(command_line[4]) );
                        new_game.display_toggle();
                        
                        // Setup the connection to other server
                        int csockfd, cportno, cn;
                        struct sockaddr_in cserv_addr;
                        struct hostent *cserver;
                        
                        char cbuffer[BUFFER_SIZE];
                        cportno = stoi(command_line[2]);
                        csockfd = socket(AF_INET, SOCK_STREAM, 0);
                        cserver = gethostbyname(command_line[1].c_str());
                        if (cserver == NULL) {
                            fprintf(stderr,"ERROR, no such host\n");
                            return false;
                        }
                        bzero((char *) &cserv_addr, sizeof(cserv_addr));
                        cserv_addr.sin_family = AF_INET;
                        bcopy((char *)cserver->h_addr,
                              (char *)&cserv_addr.sin_addr.s_addr,
                              cserver->h_length);
                        cserv_addr.sin_port = htons(cportno);
                        
                        // Attempt to connect to other server
                        if (connect(csockfd,(struct sockaddr *) &cserv_addr,sizeof(cserv_addr)) < 0)
                            socket_output("ERROR connecting");
                        
                        string from_opponent;
                        
                        // Read to see if they asked for password
                        bzero(buffer,BUFFER_SIZE);
                        read(csockfd,cbuffer,BUFFER_SIZE-1);
                        from_opponent = string(cbuffer);
                        if (from_opponent.compare("PASSWORD")) {
                            string pass = command_line[3];
                            write(csockfd,pass.c_str(),pass.length());
                        } else {
                            socket_output("; Unexpected output from server\n");
                            socket_output(from_opponent.c_str());
                            socket_output("; End output\n");
                            return false;
                        }
                        
                        // Read to see if they accepted password
                        bzero(buffer,BUFFER_SIZE);
                        read(csockfd,cbuffer,BUFFER_SIZE-1);
                        from_opponent = string(cbuffer);
                        if (from_opponent.compare("WELCOME")) {
                            string opponent_game = "HUMAN-AI " + command_line[5];
                            write(csockfd, opponent_game.c_str(), opponent_game.length());
                        } else {
                            socket_output("; Server did not accept the password given\n");
                            return false;
                        }
                        
                        string current_move = new_game.ai->make_move( &new_game );
                        bool continue_playing = true;
                        while (continue_playing) {
                            write(csockfd, current_move.c_str(), current_move.length());
                            
                            bzero(buffer,BUFFER_SIZE);
                            read(csockfd,cbuffer,BUFFER_SIZE-1);
                            from_opponent = string(cbuffer);
                            
                            string cdelimiters = " \n";
                            
                            vector<string> ccommand_line;
                            char* cpch;
                            cpch = strtok ((char*)from_opponent.c_str(), cdelimiters.c_str()); //tokenizes the command
                            
                            //------Continued-Lexer-for-both-inputs------//
                            while (cpch != NULL) {
                                string temp = cpch;
                                transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //FORCE LOWERCASE
                                if (temp != "" && temp != " " && temp != "OK") {
//                                    cout << "Pushing: " << temp << "|\n";
                                    ccommand_line.push_back(temp); //put the token into a vector to make the command easy to parse
                                }
                                output<<temp<<" "; // For output file
                                temp.clear();
                                cpch = strtok (NULL, cdelimiters.c_str());
                            }
                            
                            continue_playing = do_command(ccommand_line);
                            
                            current_move = new_game.ai->make_move( &new_game );
                            cout << current_move << "\n";
                        }
                        
                        close(csockfd);
                        
                        error=0;
                    } else{
                        socket_output("; Invalid difficulty\nILLEGAL\n");
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
                            socket_output("OK\n");
                            new_game.update(tc, t2-48, to_dir(command_line[1].c_str()));
                        } else{
                            socket_output("; Invalid move\nILLEGAL\n");
                            sprintf(out_buffer, "%c%c %s is an invalid move\n", tc,t2, command_line[1].c_str());
                            if(new_game.get_display())
								new_game.display_board();
                            output_function(16);
                        }
                    } else{
                        socket_output("; Invalid direction\nILLEGAL\n");
                        sprintf(out_buffer, "%s is not a valid direction", command_line[1].c_str());
                        output_function(17);
                    }
                } else{
                    socket_output("; Invalid row number\nILLEGAL\n");
                    sprintf(out_buffer, "%c  is not a valid row number", t2);
                    output_function(18);
                }
            } else{
                socket_output("; Invalid column letter\nILLEGAL\n");
                sprintf(out_buffer, "%c  is not a valid column letter", tc);
                output_function(19);
            }
        } else{
//            socket_output("; Move command had incorrect number of arguments\nILLEGAL\n");
            sprintf(out_buffer, "Move had incorrect amount of arguments");
            output_function(20);
        }
    }else{
        socket_output("; Not a valid move\nILLEGAL\n");
        sprintf(out_buffer, "%s is not a valid command", command_line[0].c_str());
        output_function(21);
    }
    
    if (new_game.game_over()) {
        string winner = new_game.who_won();
        sprintf(out_buffer, "%s", winner.c_str());
        output_function(0);
        
        return false;
    }
    
    return true;
}


int main(int argc, char *argv[]){
	//------INCLUDE-WITH-ALL-MAINS-USED------//
    sprintf(temp_buffer, "The current file is: %s", __FILE__);//For use for OUTPUT.txt
    buffer_size=0;
    output.open ("Output.txt");
    output<<"=-=-=-=-=-=-BEGIN=-=-=-=-=-=-="<<endl;
    output<< temp_buffer << endl;
    line_number=1;
	signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
	signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
	//------^-^-^-^AT-BEGINING-^-^-^-^-----//
	
	
	// Create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        socket_error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    if (argv[1]) {
        portno = atoi(argv[1]);
    } else {
        portno = 5155;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    // Bind the socket to available address and port
    if (::bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        socket_error("ERROR on binding");
    
    cout << "Server started on port " << portno << "\n";
    
    // Wait for a client to connect; accept when they do
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while(1) {
        newsockfd = accept(sockfd,
                           (struct sockaddr *) &cli_addr,
                           &clilen);
        if (newsockfd < 0)
            socket_error("ERROR on accept");
        
        new_game = Game(newsockfd);
        
        socket_output("PASSWORD\n");
        
        bzero(buffer,BUFFER_SIZE);
        
        n = read(newsockfd,buffer,BUFFER_SIZE-1);
        if (n < 0) socket_error("ERROR reading from socket");
        
        string password = string(buffer);
        if (password.compare(0, correct_password.size() , correct_password) != 0) {
            socket_output("Incorrect password\n");
            shutdown(newsockfd, 2);
            continue;
        }
        
        socket_output("WELCOME\n");
        
        bool user_wants_to_continue = true;
        //----------Example-use-of-parser----------//
        while(user_wants_to_continue){
            bzero(buffer,BUFFER_SIZE);
            n = read(newsockfd,buffer,BUFFER_SIZE-1);
            string command = string(buffer);
            if (!isalpha(command.back())) {
                command = command.substr(0, command.length() - 1);
            }
            if (!isalpha(command.back())) {
                command = command.substr(0, command.length() - 1);
            }
//            cout << "Command given: " << command << " of size: " << command.length() << endl;
            string delimiters = " \n";
            
            vector<string> command_line;
            char* pch;
            pch = strtok ((char*)command.c_str(), delimiters.c_str()); //tokenizes the command
            
            //------Continued-Lexer-for-both-inputs------//
            while (pch != NULL) {
                string temp = pch;
                transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //FORCE LOWERCASE
                if (temp != "" && temp != " ") {
//                    cout << "Pushing: " << temp << "|\n";
                    command_line.push_back(temp); //put the token into a vector to make the command easy to parse
                }
                output<<temp<<" "; // For output file
                temp.clear();
                pch = strtok (NULL, delimiters.c_str());
            }
            
            user_wants_to_continue = do_command(command_line);
        }
        //----------------------------------------//
        
        // Close socket when finished
        shutdown(newsockfd, 2);
    }
    shutdown(sockfd, 2);
    // End socket programming
	
	
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	output<<"=-=-=-=-=-=-EXITED-=-=-=-=-=-=";
	output.close();
	//------^-^-^-^-^-AT-END-^-^-^-^-^------//
	return 0;
}
