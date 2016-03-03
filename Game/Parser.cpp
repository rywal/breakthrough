#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

//------GLOBAL-VARIABLE------//
ofstream output;
int error;
int line_number;
string delimiters;
size_t buffer_size;
char* str;
char* pch;
string f_or_h;
vector<string> command_line;
//---------------------------//


void do_command(vector<string> command_line){
	for(int i = 0; i<command_line.size();i++){
		cout<<command_line[i]<<endl;
	}
	cout<<"End of Doc"<<endl;
}

//------------------------------------------//
//-----------Below-is-main-intake-----------//
//------------------------------------------//

void clear_input(){ //  This
	cin.clear();   //   Ensures
	cin.sync();   //    cin is
	cin.ignore();//     cleared (For sure)
}

void handle_action(string command, char* pch){
	//------Continued-Lexer-for-both-inputs------//
	output<<"Given input: " <<command<<endl;
	while (pch != NULL) {
		string temp = pch;
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //FORCE LOWERCASE
		command_line.push_back(temp); //put the token into a vector to make the command easy to parse
		pch = strtok (NULL, delimiters.c_str());
	}
	//-------------------------------------------//
	error=0;
	if(command_line[0]=="exit" && command_line.size()==1){//Checking for "EXIT" command - Preventing SegFault
		output<<"-=-=-=-=-EXITED-=-=-=-=-"<<endl;
		exit(0);
	} else{	
		do_command(command_line);   /*/---Where-the-command-is-executed--/*/
	}
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
	delimiters = " ,();\n";
	line_number=1;
	//--------------------------------//

	printf("Intake from file [f] or hand[h]?\n(\".txt\"'s in input will be assumed as a file)\n>");//Giving better testing handles
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
				
				//------Lexer-for-file-input-commands------//
				pch = strtok (str, delimiters.c_str()); //tokenizes the command
				//-----------------------------------------//
				
				handle_action(command, pch); /*/---Where-the-command-is-processed--/*/
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
			
			//------Lexer-for-hand-typed-commands------//
			pch = strtok ((char*)command.c_str(), delimiters.c_str()); //tokenizes the command
			//-----------------------------------------//
			
			handle_action(command, pch); /*/---Where-the-command-is-processed--/*/
		}
	}
	output<<"-=-=-=-=-=END-=-=-=-=-=-";
	output.close();
    return 0;
}