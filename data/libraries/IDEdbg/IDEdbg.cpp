#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "linked_list.h"
#include "variable.h"
#include "frame.h"

// Contains the list of the frames
linked_list* frames;

// Public
void DbgInit(int baud_rate)
{
	frames=NULL;
	Serial.begin(baud_rate);
}

void DbgNewFrame(const char* name)
{
	// Create a new frame and add it as an element on the frames' list
	frames=linked_list_element_push_front(frames, frame_create(name));
}

void DbgCloseFrame()
{
	linked_list_remove_front(frames, frame_free);
}

void _DbgWatchVariable(const char* name, variable_type type, int size, void* data)
{
	variable* var=variable_create(name, type, size, data);
	
	frame_add_variable((frame*)linked_list_first_element(frames)->data, var);
}

void _DbgWatchVariable(const char* name, int* data)
{
	return _DbgWatchVariable(name, _int, sizeof(&data), (void*)data);
}

void _DbgWatchVariable(const char* name, unsigned int* data)
{
	return _DbgWatchVariable(name, _unsigned_int, sizeof(&data), (void*)data);
}

void _DbgWatchVariable(const char* name, char* data)
{
	return _DbgWatchVariable(name, _char, sizeof(&data), (void*)data);
}

void _DbgWatchVariable(const char* name, unsigned char* data)
{
	return _DbgWatchVariable(name, _unsigned_char, sizeof(&data), (void*)data);
}

void _DbgWatchVariable(const char* name, float* data)
{
	return _DbgWatchVariable(name, _float, sizeof(&data), (void*)data);
}

void _DbgWatchVariable(const char* name, double* data)
{
	return _DbgWatchVariable(name, _double, sizeof(&data), (void*)data);
}

void _DbgWatchVariable(const char* name, const char** data)
{
	return _DbgWatchVariable(name, _char_pointer, sizeof(&data), (void*)data);
}

void _DbgWatchVariable(const char* name, char** data)
{
	return _DbgWatchVariable(name, (const char**)data);
}

void _DbgWatchVariable(const char* name, void* data)
{
	return _DbgWatchVariable(name, _void_pointer, sizeof(&data), (void*)data);
}

void DbgSendTrace(const char* format, ...)
{
	va_list list;
	va_start(list, format);
	
	Serial.print("<trace>");
	
	// Read all the format string
	int i=0;
	while(format[i])
	{
		if(format[i]=='%')
		{
			// Get the next char
			++i;
			
			// If we are not at the end of the string
			if(format[i]==NULL)
			{
			}
			else if(format[i]=='i')
			{
				int value=va_arg(list, int);
				Serial.print(value, DEC);
				++i;
			}
			else if(format[i]=='x')
			{
				int value=va_arg(list, int);
				Serial.print("0x");
				Serial.print(value, HEX);
				++i;
			}
			else if(format[i]=='c')
			{
				int value=va_arg(list, int);
				Serial.print(value, BYTE);
				++i;
			}
			else if(format[i]=='s')
			{
				char* value=va_arg(list, char*);
				Serial.print(value);
				++i;
			}
			else //if(format[i]=='%')
			{
				Serial.print(format[i], BYTE);
				++i;
			}
		}
		else
		{
			Serial.print(format[i], BYTE);
			++i;
		}
	}
	
	Serial.print("</trace>");

	va_end(list);
}

void _DbgSendState(const char* filename, int line)
{
	Serial.print("<frames>");

	int frameCount=linked_list_length(frames);
	linked_list* tmpFrame=linked_list_first_element(frames);
	
	for(int i=0; tmpFrame!=NULL && i<frameCount; ++i)
	{
		generateFrameTrace((frame*)tmpFrame->data);
		tmpFrame=tmpFrame->next;
	}

	Serial.print("</frames>");
}

// Useless
void IDEdbg_printCurrentFrameVariables()
{
	// Just print the list
	linked_list_print((linked_list*)frames->data, show_variable);
}
