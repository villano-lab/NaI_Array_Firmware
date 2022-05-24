// Include
// ======================================================================
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
#include  "UT1AReplica_lib.h"
#include "../../../../../SCIDK-SDKLinux/libSCIDK/include/SCIDK_API_C.h"
#define BOARD_SERIAL_NUMBER "0001"

// Variables
// ======================================================================
int ret;
uint32_t    val;
int verbose = 0;
//Registers
NI_HANDLE handle;
int thrs_q;
int top_q;
int delay_q;
int gate_uq;
int gate_lq;
int inhib_q;
int polarity_q;
char* selection;
uint32_t value;
int disable_q[2]; // array of disable_q instead of 24 initializations
int disable[2];
time_t tic, toc;
const char* program_name = "scanwindow";
FILE *fp;
FILE *logfile;

// Functions
// ======================================================================
const struct option longopts[] =
{
	{"gate",	required_argument,	0,	'g'},
	{"help",	no_argument,		0,	'h'},
	{"log",		optional_argument,	0,	'l'},
	{"quiet",	no_argument,		0,	'q'},
	{"silent",	no_argument,		0,	's'},
	{"verbose",	optional_argument,	0,	'v'},
	{"version",	no_argument,		0,	'V'},
	{"det",		required_argument,	0,	'd'},
	{"thresh",	required_argument,	0,	't'},
	{0,		0,			0,	0},
};

void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage:  %s options \n", program_name);
  	fprintf (stream,
	" -d,	--det	<# or source name>	Choose which detectors to trigger on (default: all).\n"
	"					Number values are bitwise from 0 to all 1s in 2-bit (3).\n"
	" -t,	--thresh	<threshold>		Set the value of the threshold (default: 4192). \n"
	" -g,	--gate	'<lower #> <upper #>'	Set the gate times for the upper and lower triggers in arbitrary(?) time units (integer. defaults: 1-100)\n"
	"					The two entries are delimited by spaces, commas, or dashes. Both must be provided.\n"
	" -v,	--verbose	<level>		Print verbose messages at the specified level (1 if unspecified).\n"
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

// lines 96-101 are ascii art
//  __  __       _         ______                _   _             
// |  \/  |     (_)       |  ____|              | | (_)            
// | \  / | __ _ _ _ __   | |__ _   _ _ __   ___| |_ _  ___  _ __  
// | |\/| |/ _` | | '_ \  |  __| | | | '_ \ / __| __| |/ _ \| '_ \ 
// | |  | | (_| | | | | | | |  | |_| | | | | (__| |_| | (_) | | | |
// |_|  |_|\__,_|_|_| |_| |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|

// Main
// ======================================================================
int main(int argc, char* argv[])
{
	//Before reading arguments, turn on all detectors and set gate values.
	//This makes sure they are set to defaults without potentially overwriting user input
	int thrs = 1024;	        //amount LESS THAN 2048 for threshold.
	value = 3;
	int gate_u = 100; 
	int gate_l = 1;

		//Read options
	int index;
	int iarg=0;
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "+d:t:l::shv::Vg:", longopts, &index);

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
			printf("Scan Window\n");
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
			selection = optarg;
			if(strcmp(selection,"PuBe") == 0 || strcmp(selection, "All") == 0 || strcmp(selection, "all") == 0){
				value = 3;
			/*}else if(strcmp(selection, "22Na") == 0|| strcmp(selection, "Na22") == 0 || strcmp(selection, "Na-22") == 0 || strcmp(selection, "22na") == 0 || strcmp(selection, "na22") == 0 || strcmp(selection, "na-22") == 0){
				value = 7168; //10, 11, 12 (or 11, 12, 13 counting from 1)*/
			}else if(strcmp(selection, "none") == 0 || strcmp(selection, "None") == 0){
				value = 0;
			}else{ //If it's actually a number, use the number
				value = atoi(selection);
				if(value < 0 || value > 3){
					printf("Detector argument invalid. Please supply an integer from 0 to 3 or valid source ('PuBe', 'All', 'None')");
					return -1;
				};
			};
		case 't':
			thrs = atoi(optarg);
		case 'g':
			if(verbose > 1){printf ("Splitting string \"%s\" into tokens:\n",optarg);}
				gate_l = atoi(strtok (optarg," ,.-"));
				gate_u = atoi(strtok (NULL," ,.-"));
			if(verbose > 1){printf("%d, %d\n",gate_l,gate_u);}
		}
	}

	fp = fopen("out.csv","w");

	//Verbosity message
	if(verbose > 0){
		printf("Running in verbose mode. Verbosity: %d\n",verbose);
	};

	//Detector on/off
	if(verbose > 1){
		printf("Detector string value supplied: %s\n",selection);
	}
	if(verbose > 1){
		printf("Bitwise detector numeric value supplied: %d\n",value);
	}
	value = value ^ 16777215; //Bitwise flip since we're enabling but firmware is disabling.
	//We'll disable anything that's 1 after the flip and leave everything else on
	if(verbose > 2){
		for(int i=0;i<24;i++){
			printf("%d",value>>i & 1);
		}
		printf("\n");
	}
	for(int i=0; i<24; i++){
		if(verbose > 1){printf("%d: %d, %d \n",i,value >> i, (value >> i) & 1);}
		disable[i] = (value >> i) & 1;
	}
	if(verbose > 1){
		printf("Bit-flipped detector value: %d\n",value);
	}
	if(verbose>0){
		printf("Set to enable the following detectors: ");
		for(int i=0;i<2;i++){
			if(disable[i] == 0){
				printf("%d, ",i);
			}
		}
		printf("\b\b.\n");
	};
	if(verbose>1){
		printf("Set to disable the following detectors: ");
		for(int i=0;i<2;i++){
			if(disable[i] == 1){
				printf("%d, ",i);
			}
		}
		printf("\b\b.\n");
	}

	//Connect to the board. 
	if(USB2_ConnectDevice(BOARD_SERIAL_NUMBER, &handle) != 0) { 
		printf("Unable to connect to the board!\n"); 
		if(logfile != NULL){fprintf(logfile,"Unable to connect to the board at %s!\n",BOARD_SERIAL_NUMBER);};
		return (-1);
	}else{
		if(verbose>0){printf("Connected.\n");};
		if(logfile != NULL){fprintf(logfile,"Connected to board at %s\n",BOARD_SERIAL_NUMBER);};
	};

	disable_q[0 ] = REG_disable_A_SET (disable[0 ], &handle);
	disable_q[1 ] = REG_disable_B_SET (disable[1 ], &handle);

	for(int i=0; i<2; i++){
		if(disable_q[i] != 0){
			printf("Unable to set on/off state of detector #%d! Aborting.\n",i);
			return -1;
		}
	}

	//Configure settings
    int top = thrs; //top of the window in trigger window
	int inhib = 50;		//inhibition time on trigger block
	int delay = 50;
	//things you probably won't change
	int polarity = 0;	//zero for negative, one for positive
	//things that are set based on external factors
	double extgain = 5;	//gain set from the browser interface
	
	if(logfile != NULL){
		fprintf(logfile,"============ Settings ============\n");
		fprintf(logfile,"Starting threshold:			%d\n",thrs);
		fprintf(logfile,"Trigger Inhibition Time:		%d\n",inhib);
		fprintf(logfile,"Polarity (Neg 0, Pos 1):		%d\n",polarity);
		fprintf(logfile,"External gain (filename only):	%g\n\n",extgain); //need a better name for "external gain"
	};
	
	//Pass them along to the system
	if(verbose>0){printf("Configuring...\n");};
	if(polarity==0){
		thrs_q = REG_thrsh_SET(2048-thrs,&handle);	//Set cutoff for GT check
	}else if(polarity==1){
		thrs_q = REG_thrsh_SET(2048+thrs,&handle);	//addition isn't working?
	}else{printf("Polarity is invalid! (Must be 1 or 0.) Aborting...\n"); return -1;}
	top_q = REG_top_SET(2048-top,&handle);	//Set cutoff for GT check
	inhib_q = REG_inhib_SET(inhib,&handle);			//Set number of samples to delay data by
	delay_q = REG_delay_SET(delay,&handle);			
	gate_uq = REG_gate_u_SET(gate_u,&handle);			
	gate_lq = REG_gate_l_SET(gate_l,&handle);	
	
	polarity_q = REG_polarity_SET(polarity,&handle);	//Set polarity to negative
	
	//Run phase - undo reset
	if(verbose>0){printf("Setting up rate counter... \n");};
	tic = time(NULL);

        //set up the rate counter
        int rate_q;
        uint32_t rateval[160]; //needs to be pre-allocated
        uint32_t ratechan=1;
        uint32_t ratetimeout=10; //timeout in ms
        uint32_t rateread_data=0;
        uint32_t ratevalid_data=0;
	
	fprintf(fp,"ttop, rate\n"); // add a header row
	if(verbose>0){printf("Collecting data! \n");};
	//Collect data
        sleep(10); //sleep before data taking
	int i;
        for(i=0; i<102; i++){	
            //reset the threshold
			if(verbose>1){printf("Updating top window:\n");};
			top = thrs+40*i;
			if(verbose>1){printf("%d\n",top);};
	        top_q = REG_top_SET(2048-top,&handle);	//Set cutoff for GT check
			//wait
			sleep(10);
			
			//get the rate
			if(verbose > 1){printf("Retreiving data...\n");};
			rate_q=RATE_METER_RateMeter_0_GET_DATA(rateval,ratechan,ratetimeout, &handle, &rateread_data, &ratevalid_data);
			if(verbose > 1){printf("Rateval: %f\n",rateval[0]/10.0);};

			//write the rate
			fprintf(fp,"%d, %f\n",top,rateval[0]/10.0);
	        if(verbose>1){printf("top: %d ; rate: %f Hz\n",top,rateval[0]/10.0);};
	};

	if(verbose>0){printf("Data collection complete.\n");};
	toc = time(NULL);
	int elapsed = (int)toc-(int)tic; 	//total time elapsed
	if(verbose>1){
		printf("%d to %d\n",(int)tic,(int)toc);
		printf("%d\n",elapsed);	//debug
	};
	int hours = floor(elapsed / 3600);
	int minutes = floor((elapsed % 3600)/60);
	int seconds = floor((elapsed % 60));
	char* timestamp = malloc(100);
	snprintf(timestamp,100,"%02d-%02d-%02d",hours,minutes,seconds);
	if(verbose>1){printf("Timestamp: %s\n",timestamp);};
	if(verbose>-1){printf("Time elapsed: %02d:%02d:%02d \n",hours,minutes,seconds);};
	if(verbose>1){printf("Closing files...");};
	if(logfile != NULL){fclose(logfile);};
	fclose(fp);
	return 0;
}

 