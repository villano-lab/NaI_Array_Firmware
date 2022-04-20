// A simple program that takes all newly-detected peaks and prints them to a csv file.
// Trying to move to ROOT but it's causing segfaults before getting into the main func 
// or even before variable declaration?

#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <getopt.h>

/*//ROOT
#include "TTree.h"
#include "TFile.h"
#include "Rtypes.h"*/

#include  "UniversalTrigger0_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"

int verbose = 0;
//Registers
NI_HANDLE handle;
int thrs_q;
int top_q;
int delay_q;
int gate_q;
int inhib_q;
int polarity_q;
uint32_t value;
int disable_q[24]; // array of disable_q instead of 24 initializations
time_t tic, toc;
const char* program_name = "setthresh";
FILE *fp;
FILE *logfile;
/*std::string outputfile="out.root";
std::string BOARD_IP_ADDRESS = "134.84.150.42";
char *board_ip_char = const_cast<char*>(BOARD_IP_ADDRESS.c_str());*/

const struct option longopts[] =
{
	{"help",	no_argument,		0,	'h'},
	{"log",		optional_argument,	0,	'l'},
	{"quiet",	no_argument,		0,	'q'},
	{"silent",	no_argument,		0,	's'},
	{"verbose",	optional_argument,	0,	'v'},
	{"version",	no_argument,		0,	'V'},
	{"det",		required_argument,	0,	'd'},
	{"thresh",	required_argument,	0,	't'}
	{0,		0,			0,	0},
};

void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage:  %s options [ inputfile(s) ]\n", program_name);
  	fprintf (stream,
	" -d,	--det	<# or source name>	Choose which detectors to trigger on (default: all).\n"
	"					Number values are bitwise from 0 to all 1s in 24 bit (16777215).\n"
	" -t,	--thresh	<threshold>		Set the value of the threshold (default: 4192). \n"
	" -v,	--verbose	<level>		Print verbose messages at the specified level (default: 1).\n"
	" -s,-q,	--silent,--quiet,		Print nothing.\n"
	" -l,	--log		<file>		Log terminal output.\n"
	" -V, 	--version			Print version and exit.\n"
	" -h,-?,	--help				Print this help function.\n"
);
  exit (exit_code);
};

int kbhit(void)
        {
          struct termios oldt, newt;
          int ch;
          int oldf;

          tcgetattr(STDIN_FILENO, &oldt);
          newt = oldt;
          newt.c_lflag &= ~(ICANON | ECHO);
          tcsetattr(STDIN_FILENO, TCSANOW, &newt);
          oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
          fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

          ch = getchar();

          tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
          fcntl(STDIN_FILENO, F_SETFL, oldf);

          if(ch != EOF)
          {
            ungetc(ch, stdin);
            return 1;
          }

          return 0;
        }

int main(int argc, char* argv[])
{
	//Before reading arguments, turn on all detectors.
	//This makes sure they are all on by default without potentially overwriting user input
	disable_q[0 ] = REG_disable_det_0_SET (0, &handle);
	disable_q[1 ] = REG_disable_det_1_SET (0, &handle);
	disable_q[2 ] = REG_disable_det_2_SET (0, &handle);
	disable_q[3 ] = REG_disable_det_3_SET (0, &handle);
	disable_q[4 ] = REG_disable_det_4_SET (0, &handle);
	disable_q[5 ] = REG_disable_det_5_SET (0, &handle);
	disable_q[6 ] = REG_disable_det_6_SET (0, &handle);
	disable_q[7 ] = REG_disable_det_7_SET (0, &handle);
	disable_q[8 ] = REG_disable_det_8_SET (0, &handle);
	disable_q[9 ] = REG_disable_det_9_SET (0, &handle);
	disable_q[10] = REG_disable_det_10_SET(0, &handle);
	disable_q[11] = REG_disable_det_11_SET(0, &handle);
	disable_q[12] = REG_disable_det_12_SET(0, &handle);
	disable_q[13] = REG_disable_det_13_SET(0, &handle);
	disable_q[14] = REG_disable_det_14_SET(0, &handle);
	disable_q[15] = REG_disable_det_15_SET(0, &handle);
	disable_q[16] = REG_disable_det_16_SET(0, &handle);
	disable_q[17] = REG_disable_det_17_SET(0, &handle);
	disable_q[18] = REG_disable_det_18_SET(0, &handle);
	disable_q[19] = REG_disable_det_19_SET(0, &handle);
	disable_q[20] = REG_disable_det_20_SET(0, &handle);
	disable_q[21] = REG_disable_det_21_SET(0, &handle);
	disable_q[22] = REG_disable_det_22_SET(0, &handle);
	disable_q[23] = REG_disable_det_23_SET(0, &handle);
	int thrs = 4192;	        //amount LESS THAN 8192 for threshold.

	//Read options
	int index;
	int iarg=0;
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "+d:l::shv::V", longopts, &index);

		switch (iarg){
		case 'h':
			print_usage(stdout,0);
			return 0;
			break;
		case 'q':
			verbose = -1;
			break;
		case 's':
			verbose = -1;
			break;
		case 'v':
			if(optarg){verbose = atoi(optarg);
			}else{verbose = 1;};
			break;
		case '?':
			print_usage(stdout,0);
			return 0;
			break;
		case 'V':
			printf("Integrate!\n");
			printf("Copyright (c) 2022 Anthony Villano, Kitty Harris \n");
			printf("License: The Expat license  <https://spdx.org/licenses/MIT.html> \n");
			printf("This is free software: you are free to change and redistribute it. \n");
			printf("There is NO WARRANTY, to the extent permitted by law. \n");
			return 0;
			break;
		case 'l':
			if(optarg){logfile = fopen(optarg,"w");
			}else{logfile = fopen("log.txt","w");};
			break;
		case 'd':
			if(optarg == "PuBe" || optarg == "All" || optarg == "all"){ //case-insensitive matching
				value = 16777215;
			}else if(optarg == "22Na" || optarg == "Na22" || optarg == "Na-22"){
				value = 14336; //10, 11, 12 (or 11, 12, 13 counting from 1)
			}else if(optarg == "none" || optarg == "None"){
				value = 0;
			}else{ //If it's actually a number, use the number
				value = atoi(optarg);
				if(value < 0 || value > 16777215){
					printf("Detector argument invalid. Please supply an integer from 0 to 16777215 or valid source ('PuBe', '22Na', 'All', 'None')");
					return -1;
				};
			};
				value = value ^ 16777215; //Bitwise flip since we're enabling but firmware is disabling.
				//Now disable anything that's 1 after the flip and leave everything else on
				disable_q[0 ] = REG_disable_det_0_SET ((value >> 0 ) & 1, &handle);
				disable_q[1 ] = REG_disable_det_1_SET ((value >> 1 ) & 1, &handle);
				disable_q[2 ] = REG_disable_det_2_SET ((value >> 2 ) & 1, &handle);
				disable_q[3 ] = REG_disable_det_3_SET ((value >> 3 ) & 1, &handle);
				disable_q[4 ] = REG_disable_det_4_SET ((value >> 4 ) & 1, &handle);
				disable_q[5 ] = REG_disable_det_5_SET ((value >> 5 ) & 1, &handle);
				disable_q[6 ] = REG_disable_det_6_SET ((value >> 6 ) & 1, &handle);
				disable_q[7 ] = REG_disable_det_7_SET ((value >> 7 ) & 1, &handle);
				disable_q[8 ] = REG_disable_det_8_SET ((value >> 8 ) & 1, &handle);
				disable_q[9 ] = REG_disable_det_9_SET ((value >> 9 ) & 1, &handle);
				disable_q[10] = REG_disable_det_10_SET((value >> 10) & 1, &handle);
				disable_q[11] = REG_disable_det_11_SET((value >> 11) & 1, &handle);
				disable_q[12] = REG_disable_det_12_SET((value >> 12) & 1, &handle);
				disable_q[13] = REG_disable_det_13_SET((value >> 13) & 1, &handle);
				disable_q[14] = REG_disable_det_14_SET((value >> 14) & 1, &handle);
				disable_q[15] = REG_disable_det_15_SET((value >> 15) & 1, &handle);
				disable_q[16] = REG_disable_det_16_SET((value >> 16) & 1, &handle);
				disable_q[17] = REG_disable_det_17_SET((value >> 17) & 1, &handle);
				disable_q[18] = REG_disable_det_18_SET((value >> 18) & 1, &handle);
				disable_q[19] = REG_disable_det_19_SET((value >> 19) & 1, &handle);
				disable_q[20] = REG_disable_det_20_SET((value >> 20) & 1, &handle);
				disable_q[21] = REG_disable_det_21_SET((value >> 21) & 1, &handle);
				disable_q[22] = REG_disable_det_22_SET((value >> 22) & 1, &handle);
				disable_q[23] = REG_disable_det_23_SET((value >> 23) & 1, &handle);
			case 't':
				thrs = atoi(optarg)
		}
	}


	//Connect to the board. 
	if(verbose > 0){
		printf("Running in verbose mode. Verbosity:%d\n",verbose);
	};
	R_Init();
	//If can't connect to the board, abort.
	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		printf("Unable to connect to the board!\n"); 
		if(logfile != NULL){fprintf(logfile,"Unable to connect to the board at %s!\n",BOARD_IP_ADDRESS);};
		return (-1); 
	}else{
		if(verbose>0){printf("Connected.\n");};
		if(logfile != NULL){fprintf(logfile,"Connected to board at %s\n",BOARD_IP_ADDRESS);};
	};

	//Configure settings
        printf("Set threshold to: %d.\n",thrs);
	int inhib = 50;		//inhibition time on trigger block
	//things you probably won't change
	int polarity = 0;	//zero for negative, one for positive
	//things that are set based on external factors
	double extgain = 5;	//gain set from the browser interface
	
	if(logfile != NULL){
		fprintf(logfile,"============ Settings ============\n");
		fprintf(logfile,"Threshold:			%d\n",thrs);
		fprintf(logfile,"Trigger Inhibition Time:	%d\n",inhib);
		fprintf(logfile,"Polarity (Neg 0, Pos 1):	%d\n",polarity);
		fprintf(logfile,"External gain (filename only):%g\n\n",extgain); //need a better name for "external gain"
	};
	
	//Pass them along to the system
	if(verbose>0){printf("Configuring...\n");};
	if(polarity==0){
		thrs_q = REG_thrsh_SET(8192-thrs,&handle);	//Set cutoff for GT check
	}else if(polarity==1){
		thrs_q = REG_thrsh_SET(8192+thrs,&handle);	//addition isn't working?
	}else{printf("Polarity is invalid! (Must be 1 or 0.) Aborting...\n"); return -1;}
	inhib_q = REG_inhib_SET(inhib,&handle);			//Set number of samples to delay data by
	polarity_q = REG_polarity_SET(polarity,&handle);	//Set polarity to negative
	

	return 0;
}
