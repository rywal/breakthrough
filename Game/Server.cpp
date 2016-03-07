#include "Parser.h" //Game called here also

int main(){
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	output.open ("Output.txt");
	output<<"=-=-=-=-=-=-BEGIN=-=-=-=-=-=-="<<endl;
	sprintf(temp_buffer, "The current file is: %s", __FILE__);
	output<< temp_buffer << endl;
	buffer_size=0;
	delimiters = " \n";
	line_number=1;
	signal(SIGINT, ctrl_c); //Catch Ctrl+C (For output format)
	signal(SIGSEGV, ctrl_c);//Catch SegFaults (For output format)
	//------^-^-^-^AT-BEGINING-^-^-^-^-----//
	
	
	
	
	//Example use of parser
	while(1){
		take_command(line_number);
	}
	
	
	
	
	
	//------INCLUDE-WITH-ALL-MAINS-USED------//
	output<<"=-=-=-=-=-=-EXITED-=-=-=-=-=-=";
	output.close();
	//------^-^-^-^-^-AT-END-^-^-^-^-^------//
	return 0;
}