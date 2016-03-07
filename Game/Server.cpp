#include "Parser.h" //Game called here also

int main(){
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	sprintf(temp_buffer, "The current file is: %s", __FILE__);//For use for OUTPUT.txt
	def_vars();//Defines variables for nicer Main()
	signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
	signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
	//------^-^-^-^AT-BEGINING-^-^-^-^-----//
	
	
	
	
	//----------Example-use-of-parser----------//
	while(1){
		take_command(line_number);
	}
	//----------------------------------------//
	
	
	
	
	
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	output<<"=-=-=-=-=-=-EXITED-=-=-=-=-=-=";
	output.close();
	//------^-^-^-^-^-AT-END-^-^-^-^-^------//
	return 0;
}