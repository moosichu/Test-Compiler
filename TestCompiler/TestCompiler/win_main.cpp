
#include "main.h"

#include <stdio.h>  
#include <string>

void print(std::string arg)
{
	const char* c_string = arg.c_str();
	printf(c_string);
}

int main() {
	return program::start(print);
}