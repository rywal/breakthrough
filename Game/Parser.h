#include <algorithm>
#include <boost/regex.hpp>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Game.h"

using namespace std;

//------GLOBAL-VARIABLE------//
ofstream output;
int error; //Give error message for debugging/output
int line_number;
string delimiters;
size_t buffer_size;
char* str;
char* pch;
string f_or_h;
vector<string> command_line;
Game new_game;
//---------------------------//

void  ctrl_c(int signo){//This is to protect formatting of output
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

bool is_difficulty(string d){
	if(d=="easy"||d=="medium"||d=="hard"){
		return true;
	} else{
		return false;
	}
}

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
			output<<"In an IP check: " << ips[i].c_str()<<" is not an Integer"<<endl;
			error = 7;
			return false;
		} else if(atoi(ips[i].c_str())<=255){ //An IP address must not go beyond 255
			//Do nothing
		} else{
			output<<"IP is out of range"<<endl;
			error = 8;
			return false;
		}
	}
	return true;
}

bool is_hostname(string h){
	if(h.size()>=49){
		output<<"Hostname cannot exceed 49 characters"<<endl;
		error = 9;
		return false;
	}
	for(int i=0; i<h.size();i++){
		if(!isalnum(h[i])&&(h[i]!='-')){
			output<<h[i]<<" is an invalid character for a hostname"<<endl;
			error = 10;
			return false;
		}
	}
	return true;
}


bool is_server(string s){
	if(is_ip(s) || is_hostname(s)){
		error = 0;
		return true;
	} else{
		if(error=6){ //Prevent false negatives in Output.txt
			output<<"IP address did not have correct amount of sets of numbers"<<endl;
		}
		//Error is given by is_ip/is_hostname
		return false;
	}
}

bool is_port(string p){
	for(int i=0; i<p.size();i++){
		if(!isdigit(p[i])){
			output<<p[i]<<" is not a valid character in a port"<<endl;
			error = 11;
			return false;
		}
	}
	if(atoi(p.c_str())>0){
		return true;
	} else{
		output<<"A port must be a postive integer."<<endl;
		error = 12;
		return false;
	}
}

bool is_dir(string d){
	return (d=="fwd"||d=="left"||d=="right");	
}

DIRECTION to_dir(string d){
	if(d=="fwd"){
		return FWD;
	} else if(d=="left"){
		return LEFT;
	} else if(d=="right"){
		return RIGHT;
	}
}

void do_command(vector<string> command_line){
	if(command_line.size()==0){
		error=22;
		output<<"No input was given"<<endl;
	} else if(command_line[0]=="exit"){//Checking for "EXIT" command - Preventing SegFault
		if(command_line.size()==1){
			output<<"=-=-=-=-=-=-EXITED-=-=-=-=-=-=";
			output.close();
			exit(0);
		} else{
			output<<"Exit had too many arguments"<<endl;
			error=1;
		}
	} else if(command_line[0]==";"){
		output<<"COMMENT: ";
		printf("\n");
		string single_string;
		single_string.push_back(';');
		single_string.push_back(' ');
		if(command_line.size()==1){
			printf("Empty comment");
			output<<"EMPTY COMMENT";
		}
		for(int i=1; i<command_line.size(); i++){
			output<<command_line[i].c_str()<<" ";
			//printf("%s ", command_line[i].c_str());
			for(int g=0;g<command_line[i].size(); g++){
				single_string.push_back(command_line[i][g]);
			}
			single_string.push_back(' ');
		}
		cout<<endl<<single_string<<endl;
		output<<endl;
		/*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
	} else if(command_line[0]=="display"){
		if(command_line.size()==1){
			new_game.display_toggle();
		} else{
			output<<"Display had too many arguments"<<endl;
			error=2;
		}
	} else if(command_line[0]=="undo"){
		if(command_line.size()==1){
			new_game.undo();
		} else{
			output<<"Undo had too many arguments"<<endl;
			error=3;
		}
	} else if(command_line[0]=="human-ai"){
		if(command_line.size()==2){
			if(is_difficulty(command_line[1].c_str())){
				/*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
			} else{
				output<<command_line[1].c_str()<<" is not a difficulty"<<endl;
				error=4;
			}
		} else{
			output<<"Human-AI had incorrect amount of arguments"<<endl;
			error=5;
		}	
	} else if(command_line[0]=="ai-ai"){
		if(command_line.size()==6){
			if(is_server(command_line[1])){
				if(is_port(command_line[2])){
					if(is_difficulty(command_line[4])&& is_difficulty(command_line[5])){
						error=0;
						/*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
					} else{
						output<<"Incorrect input for difficulty"<<endl;
						error=13;
					}
				} else{
					output<<command_line[2]<<" is not a port"<<endl;
					error=14;
				}
			} else{
				output<<command_line[1]<<" is not a server"<<endl;
				//Error given in is_server
			}
		} else{
			output<<"AI-AI had incorrect amount of arguments"<<endl;
			error=15;
		}
	} else if(command_line[0].size()==2){//Is this a MOVE?
		if(command_line.size()==2){
			char tc = command_line[0][0];//tc, standing for Temporary Char
			if(tc=='a'||tc=='b'||tc=='c'||tc=='d'||tc=='e'||tc=='f'||tc=='g'){
				char t2 = command_line[0][1];//t2, standing for Temporary Char #2
				if(t2=='1'||t2=='2'||t2=='3'||t2=='4'||t2=='5'||t2=='6'||t2=='7'||t2=='8'){
					if(is_dir(command_line[1])){
						if(new_game.valid_move(t2-48, tc, to_dir(command_line[1].c_str()))){
							new_game.update(tc, t2-48, to_dir(command_line[1].c_str()));
						} else{
							printf("%c%c is an invalid move\n", tc,t2);
							output<<tc<<t2<<" is an invalid move"<<endl;
							error = 16;
						}
					} else{
						output<<command_line[1]<<" is not a valid direction"<<endl;
						error = 17;
					}
				} else{
					output<<t2<<" is not a valid row number"<<endl;
					error = 18;
				}
			} else{
				output<<tc<<" is not a valid column letter"<<endl;
				error = 19;
			}
		} else{
			output<<"Move had incorrect amount of arguments"<<endl;
			error=20;
		}
	}  else if(command_line.size()==1){//Is this a MOVE?
		output<<"PASSWORD: "<<command_line[0]<<endl;
		/*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
	}else{
		output<<command_line[0].c_str()<<" is not a valid command"<<endl;
		error=21;
	}
}

//------------------------------------------//
//-----------Below-is-main-intake-----------//
//------------------------------------------//

void clear_input(){ //  This
	cin.clear();   //   Ensures
	cin.sync();   //    cin is
	cin.ignore();//     cleared (For sure)
}

void handle_action(string command, int &ln, bool is_file){
	output<<"Given input: ";
	if(is_file){
		//------Lexer-for-file-input-commands------//
		pch = strtok (str, delimiters.c_str()); //tokenizes the command
		//-----------------------------------------//
	} else{
		//------Lexer-for-hand-typed-commands------//
		pch = strtok ((char*)command.c_str(), delimiters.c_str()); //tokenizes the command
		//-----------------------------------------//
	}
	//------Continued-Lexer-for-both-inputs------//
	while (pch != NULL) {
		string temp = pch;
		if(is_file){ //GET RID OF GARBAGE AT END--------//
			string temp2;
			if(temp.size()<=2){
				temp2=temp.c_str();
			} else{
				for(int i=0; (i+2)<temp.size();i++){ //This will copy all but the last two elements
					temp2.push_back(temp[i]);
				}
				for(int g=(temp.size()-2); g<temp.size();g++){//If string has null at end, delete them
					if(!isspace(temp[g])){
						temp2.push_back(temp[g]);
					}
				}
			}
			temp=temp2.c_str();//Put new temp into old temp 
		}//-----------GET RID OF GARBAGE AT END--------//
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //FORCE LOWERCASE
		command_line.push_back(temp); //put the token into a vector to make the command easy to parse
		output<<temp<<" "; // For output file
		temp.clear();
		pch = strtok (NULL, delimiters.c_str());
	}
	output<<endl; //For output file
	//-------------------------------------------//
	error=0;	
	do_command(command_line);   /*/---Where-the-command-is-executed--/*/
	if(error==0){
		output<<"Command number "<<line_number<<" was successful!"<<endl; //Prints status to Output file
	} else {
		output<<"Command number "<<line_number<<" FAILED!"<<endl; //Prints status to Output file
	}
	//prepare for next command
	command_line.clear();
	free(pch);
	line_number++;
	ln=line_number;
}

void take_command(int &ln){ //Take input from command line
	line_number=ln;
	buffer_size=0;
	delimiters = " \n";
	printf("\n>");
	string command;
	signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
	signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
	getline (cin,command);
	handle_action(command, ln, false); /*/---Where-the-command-is-processed--/*/
}

void parse_file(int &ln){//Take input from file
	line_number=ln;
	buffer_size=0;
	delimiters = " \n";
	char* input_file;
	FILE *input;
	string input_f="";//To prevent errors
	printf("Please input the file you would like to use.\n>");
	cin>>input_f;
	string input_w = "Game/" + input_f;
	input=fopen(input_w.c_str(), "r");
	if(!input){
		printf("\nThe file: %s not found!", input_w.c_str());
		printf("\nPlease place the input folder as in the same folder as %s.\n\n", __FILE__);
		output<<"The file: "<<input_w.c_str()<<" was not found"<<endl;
	} else{
		output<<"Input from file started"<<endl;
		while(!feof(input)){ //get a command from the file
			getline(&str, &buffer_size, input); 
			string command(str);
			printf("The given command is: %s",command.c_str()); //prints the command back to the user
			signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
			signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
			handle_action(command.c_str(), ln, true); /*/---Where-the-command-is-processed--/*/
		}
		fclose(input);
		output<<"=-=-=-=-=-=-=EOF-=-=-=-=-=-=-=\n";
	}
}