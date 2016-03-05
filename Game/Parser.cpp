#include "Parser.h"

int main() {
	output.open ("Output.txt");
	output<<"=-=-=-=-=-=-BEGIN=-=-=-=-=-=-="<<endl;
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
			output<<"Input from file started"<<endl;
			while(!feof(input)){ //get a command from the file
				getline(&str, &buffer_size, input); 
				string command(str);
				printf("The given command is: %s",command.c_str()); //prints the command back to the user
				signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
				signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
				handle_action(command.c_str(), true); /*/---Where-the-command-is-processed--/*/
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
			signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
			signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
			getline (cin,command);
			handle_action(command, false); /*/---Where-the-command-is-processed--/*/
		}
	}
	output<<"=-=-=-=-=-=-=EOF-=-=-=-=-=-=-=";
	output.close();
    return 0;
}