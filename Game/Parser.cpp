int main() {
	output.open ("Output.txt");
	output<<"-=-=-=-=-BEGIN=-=-=-=-=-"<<endl;
	Database db("db");
	char* str;
	char* pch;
	int i=0;
	size_t buffer_size=0;
	string delimiters = " ,();\n";
	vector<string> command_list;	
	if(!output){ //This should never happen
		printf("\nThe Output file is not found!");
		exit(EXIT_FAILURE);//Showing error status code
	}
	string f_or_h;
	printf("For this run, would you like to take input from an \"Input.txt\" file [f], or type commands in by hand[h]?\n(If your input has a \".txt\" in it, it'll be processes as a file)\n>");//Giving better testing handles
	cin >>  f_or_h;
	int loop=1;
	while (loop==1){
		if(f_or_h != "h" && f_or_h != "H" && f_or_h != "hand" && f_or_h != "f" && f_or_h != "F" && f_or_h != "file" && !strstr(f_or_h.c_str(),".txt")){
			cin.clear();//  This
			cin.sync();//   Ensures
			cin.ignore();// Everything is cleared (For sure)
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
			printf("Please input the file you would like to use. \n(Please note, this is automated, no other input will be read)\n>");
			cin.clear();//  This
			cin.sync();//   Ensures
			cin.ignore();// Everything is cleared (For sure)
			cin>>input_f;
			string input_w = "Game/" + input_f;
			filename = "Game/" + input_f;
			input=fopen(input_w.c_str(), "r");
		}
		//file_input(db, input, filename, false);//Where the action happens
	} else if (f_or_h == "h" || f_or_h == "H" || f_or_h == "hand"){
		cin.clear();
		cin.sync();
		cin.ignore();
		int command_number=1;
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
			} else{query_or_command(db, command_list);}
			if(error==0){
				output<<"Command number "<<command_number<<" was successful!"<<endl;
			} else{
				output<<"Command number "<<command_number<<" Failed!"<<endl;
			}
			command_list.clear();
			free(pch);
			command_number++;
		}
	}
	output.close();
    return 0;
}