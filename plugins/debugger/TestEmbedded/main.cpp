#include <stdio.h>

#include "IDEdbg.h"

int main(int argc, char** argv)
{
	char a='a';
	int b=127;
	int c=-25;
	
	const char* str="Je suis mupuf";
	
	float f=123456789.123456789;
	float d=123456789.123456789;
	
	DbgInit();
	
	DbgNewFrame();
	
	DbgWatchVariable(a);
	DbgWatchVariable(b);
	DbgWatchVariable(c);
	DbgWatchVariable(f);
	DbgWatchVariable(d);
	
	IDEdbg_printCurrentFrameVariables();
	
	char* data=IDEdbg_generateDebuggingTraces();
	printf("data=\"%s\"\n", data);
	free(data);
	
	DbgCloseFrame();
	
	/*linked_list* test=linked_list_create();
	
	linked_list_print(test, show_string);
	test=linked_list_element_push_back(test, "poulpe");
	linked_list_print(test, show_string);
	test=linked_list_element_push_back(test, "poulpe2");
	linked_list_print(test, show_string);
	test=linked_list_element_push_back(test, "poulpe3");
	linked_list_print(test, show_string);
	test=linked_list_push_front(test, linked_list_create());
	linked_list_print(test, show_string);
	
	linked_list_free(test, NULL);*/
	
	return 0;
}