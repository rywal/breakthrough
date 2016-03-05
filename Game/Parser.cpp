#include "Parser.h"

int main() {
	//------Need-to-include-in-each-MAIN------//
	output.open ("Output.txt");
	output<<"=-=-=-=-=-=-BEGIN=-=-=-=-=-=-="<<endl;
	line_number=1;
	signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
	signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
	//------^-^-^-^-^-^-^-^-^-^-^-^-^-^-^------//
	
	//Example of a main-----------------------------------------------------//
	while(true){
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
		if(f_or_h == "f" || f_or_h == "F"){
			parse_file(line_number);
		} else if (f_or_h == "h" || f_or_h == "H"){
			take_command(line_number);
		}
	}
	output.close();
    return 0;
	//Example of a main-----------------------------------------------------//
}