#include "Def.h"
#include "ComputerInteractionTest_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <getopt.h>
#define BOARD_IP_ADDRESS "134.84.150.42"

using namespace std;

const char* program_name = "calibrate";

void help (FILE* stream, int exit_code)
{
	fprintf (stream, "Usage: %s options\n", program_name);
	fprintf(stream,
		"Args go here once they exist\n"
}

#define no_argument 0
#define required_argument 1
#define optional_argument 2

int main(int argc, char* argv[]){
	//start with CL args
	// right now let's just see what my help function looks like.
	help(stdout, 0);
	
	//need to return an int
	return 0;
}
