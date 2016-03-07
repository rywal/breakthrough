#include "Parser.h" //Game called here also

int main(){
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	sprintf(temp_buffer, "The current file is: %s", __FILE__);//For use for OUTPUT.txt
	def_vars();//Defines variables for nicer Main()
	signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
	signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
	//------^-^-^-^AT-BEGINING-^-^-^-^-----//
	
	//Example of a main-----------------------------------------------------//
	string f_or_h;
	while(true){
		while(1){
		printf("file[f] or hand[h]?\n>");//Giving better testing handles
		cin >>  f_or_h;
		clear_input();//Clears CIN
		int loop=1;
		while (loop==1){
				if(f_or_h != "h" && f_or_h != "H" && f_or_h != "f" && f_or_h != "F"){
					printf("Please re-enter your prefered input method [f\\h]\n>");//TEST MAIN
					cin >>  f_or_h;
				} else{loop=0;}
			}
			if(f_or_h == "f" || f_or_h == "F"){
				parse_file(line_number);
			} else if (f_or_h == "h" || f_or_h == "H"){
				while(1){
					take_command(line_number);
				}
			}
		}
	}
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	output<<"=-=-=-=-=-=-EXITED-=-=-=-=-=-=";
	output.close();
	//------^-^-^-^-^-AT-END-^-^-^-^-^------//
    return 0;
}