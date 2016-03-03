#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>
#include <boost/regex.hpp>
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
//---------------------------//

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
		output<<"IP address did not have correct amount of sets of numbers"<<endl;
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


bool is_server(string s){
	cout<<"In server"<<endl;
	
	if(is_ip(s)){
		cout<<"Yes!!"<<endl;
	} else{
		cout<<"Not valid IP"<<endl;
	}
}

void do_command(vector<string> command_line){
	for(int i = 0; i<command_line.size();i++){
		cout<<command_line[i]<<endl;
	}
	if(command_line.size()==0){
		output<<"No input was given"<<endl;
	} else if(command_line[0]=="exit"){//Checking for "EXIT" command - Preventing SegFault
		if(command_line.size()==1){
			output<<"-=-=-=-=-EXITED-=-=-=-=-"<<endl;
			exit(0);
		} else{
			output<<"Exit had too many arguments"<<endl;
			error=1;
		}
	} else if(command_line[0]=="display"){
		if(command_line.size()==1){
			/*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
		} else{
			output<<"Display had too many arguments"<<endl;
			error=2;
		}
	} else if(command_line[0]=="undo"){
		if(command_line.size()==1){
			/*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
		} else{
			output<<"Undo had too many arguments"<<endl;
			error=3;
		}
	} else if(command_line[0]=="human-ai"){
		if(command_line.size()==2){
			if(is_difficulty(command_line[1])){
				/*-------------------------NEED-TO-BE-DEFINED----------------------------------------*/
			} else{
				output<<command_line[1]<<" is not a difficulty"<<endl;
				error=4;
			}
		} else{
			output<<"Human-AI had incorrect amount of arguments"<<endl;
			error=5;
		}
			
	} else if(command_line[0]=="ai-ai"){
		if(command_line.size()==6){
			if(is_server(command_line[1])){
				
			} else{
				output<<command_line[1]<<" is not a server"<<endl;
				error=7;
			}
		} else{
			output<<"AI-AI had incorrect amount of arguments"<<endl;
			error=8;
		}
	}
	
	cout<<"EOF"<<endl<<endl;
}

//------------------------------------------//
//-----------Below-is-main-intake-----------//
//------------------------------------------//

void clear_input(){ //  This
	cin.clear();   //   Ensures
	cin.sync();   //    cin is
	cin.ignore();//     cleared (For sure)
}

void handle_action(string command, bool is_file){
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
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //FORCE LOWERCASE
		command_line.push_back(temp); //put the token into a vector to make the command easy to parse
		output<<temp<<" "; // For output file
		pch = strtok (NULL, delimiters.c_str());
	}
	output<<endl; //For output file
	//-------------------------------------------//
	error=0;	
	do_command(command_line);   /*/---Where-the-command-is-executed--/*/
	if(error==0){
		output<<"Line number "<<line_number<<" was successful!"<<endl; //Prints status to Output file
	} else {
		output<<"Line number "<<line_number<<" FAILED!"<<endl; //Prints status to Output file
	}
	//prepare for next command
	command_line.clear();
	free(pch);
	line_number++;
}

int main() {
	output.open ("Output.txt");
	output<<"-=-=-=-=-BEGIN=-=-=-=-=-"<<endl;
	//------Definining-Variables------//
	int i=0;
	buffer_size=0;
	delimiters = " \n";
	line_number=1;
	//--------------------------------//

	printf("file[f] or hand[h]?\n>");//Giving better testing handles
	cin >>  f_or_h;
	clear_input();//Clears CIN
	int loop=1;
	while (loop==1){
		if(f_or_h != "h" && f_or_h != "H" && f_or_h != "f" && f_or_h != "F" && !strstr(f_or_h.c_str(),".txt")){
			printf("Please re-enter your prefered input method [f\\h]\n>");
			cin >>  f_or_h;
		} else{loop=0;}
	}
	if(f_or_h == "f" || f_or_h == "F" || strstr(f_or_h.c_str(),".txt")){
		char* input_file;
		FILE *input;
		string filename;
		string input_f="";//To prevent errors
		if(strstr(f_or_h.c_str(),".txt")){
			string input_w = "Game/" + f_or_h;
			filename = "Game/" + f_or_h;
			input=fopen(input_w.c_str(), "r");
		}else{
			int loop=1;
			while (loop==1){ //Ask for input multiple times
				printf("Please input the file you would like to use. \n(Please note, this is automated, no other input will be read)\n>");
				cin>>input_f;
				if(input_f == "h" || input_f == "H"){loop==0; break;}//User changed mind
				string input_w = "Game/" + input_f;
				filename = "Game/" + input_f;
				input=fopen(input_w.c_str(), "r");
				if(!input){
					printf("\nThe file: %s not found!", filename.c_str());
					printf("\nPlease place the input folder as in the same folder as %s.\n\n", __FILE__);
				}else{loop=0;}
			}
		}
		if(input_f != "h" && input_f != "H"){
			while(!feof(input)){ //get a command from the file
				getline(&str, &buffer_size, input); 
				string command(str);
				printf("The given command is: %s\n",str); //prints the command back to the user
				handle_action(command, true); /*/---Where-the-command-is-processed--/*/
			}
			fclose(input);
		} else{
			f_or_h="h";
			printf("The user has transfered into the hand-typed command mode\n");
			output<<"The user has transfered into the hand-typed command mode"<<endl;
			clear_input();//Clears CIN
		}
	}
	if (f_or_h == "h" || f_or_h == "H"){
		while(1){
			printf("Please enter a command:\n>");
			string command;
			getline (cin,command);
			handle_action(command, false); /*/---Where-the-command-is-processed--/*/
		}
	}
	output<<"-=-=-=-=-=END-=-=-=-=-=-";
	output.close();
    return 0;
}