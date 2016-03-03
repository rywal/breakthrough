#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

//------GLOBAL-VARIABLE------//
ofstream output;
int error;
int line_number;
string delimiters;
size_t buffer_size;
char* str;
char* pch;
//---------------------------//

void clear_input(){ //  This
	cin.clear();   //   Ensures
	cin.sync();   //    cin is
	cin.ignore();//     cleared (For sure)
}

int file_input(FILE *input, string filename, bool is_open){
	//--------Local-Variables--------//
	vector<string> command_list;
	//-------------------------------//
	
	while(!feof(input)){ //get a command from the file
		getline(&str, &buffer_size, input); 
		string command(str);
		printf("The given command is: %s\n",str); //prints the command back to the user
		pch = strtok (str, delimiters.c_str()); //tokenizes the command
		while (pch != NULL) {
			command_list.push_back(pch); //put the token into a vector to make the command easy to parse
			pch = strtok (NULL, delimiters.c_str());
		}
		if(command_list[0]=="EXIT" && command_list.size()==1){//Checking for "EXIT" command - Preventing SegFault
			output<<"-=-=-=-=-EXITED-=-=-=-=-"<<endl;
			exit(0);
		} else{	
		//This marks the beginning of the query/command interpretation
			//query_or_command(db, command_list);   //////////////////////////////////////////////////////////////////
		}
		if(error==0){
			output<<"Line number "<<line_number<<" was successful!"<<endl; //Prints status to Output file
		} else {
			output<<"Line number "<<line_number<<" FAILED!"<<endl; //Prints status to Output file
		}
		//prepare for next command
		command_list.clear();
		free(pch);
		line_number++;
		error=0;
	}
	fclose(input);
}

int main() {
	output.open ("Output.txt");
	output<<"-=-=-=-=-BEGIN=-=-=-=-=-"<<endl;
	//------Definining-Variables------//
	int i=0;
	buffer_size=0;
	delimiters = " ,();\n";
	vector<string> command_list;
	line_number=1;
	//--------------------------------//
	
	string f_or_h;
	printf("Intake from file [f] or hand[h]?\n(\".txt\"'s in input will be assumed as a file)\n>");//Giving better testing handles
	cin >>  f_or_h;
	clear_input();//Clears CIN
	if(f_or_h == ""){f_or_h="h";} //Assume that you want to write by hand
	int loop=1;
	while (loop==1){
		if(f_or_h != "h" && f_or_h != "H" && f_or_h != "f" && f_or_h != "F" && !strstr(f_or_h.c_str(),".txt")){
			clear_input();//Clears CIN
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
			loop=1;
			while (loop==1){ //Ask for input multiple times
				printf("Please input the file you would like to use. \n(Please note, this is automated, no other input will be read)\n>");
				cin>>input_f;
				string input_w = "Game/" + input_f;
				filename = "Game/" + input_f;
				input=fopen(input_w.c_str(), "r");
				if(!input){
					printf("\nThe file: %s not found!", filename.c_str());
					printf("\nPlease place the input folder as in the same folder as %s.\n\n", __FILE__);
				}else{loop=0;}
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		//file_input(db, input, filename, false);//Where the action happens
	} else if (f_or_h == "h" || f_or_h == "H"){
		while(1){
			error=0;
			printf("Please enter a command:\n");
			string command;
			std::getline (std::cin,command);
			
			pch = strtok ((char*)command.c_str(), delimiters.c_str());//Lexer
				while (pch != NULL) {
					command_list.push_back(pch);
					pch = strtok (NULL, delimiters.c_str());
			}
			if(command_list[0]=="EXIT" && command_list.size()==1){//Preventing SegFault
				exit(0);
			} else{
				//query_or_command(db, command_list); ////////////////////////////////////////////////////////////////
				}
			if(error==0){
				output<<"Command number "<<line_number<<" was successful!"<<endl;
			} else{
				output<<"Command number "<<line_number<<" Failed!"<<endl;
			}
			command_list.clear();
			free(pch);
			line_number++;
		}
	}
	output<<"-=-=-=-=-=END-=-=-=-=-=-";
	output.close();
    return 0;
}