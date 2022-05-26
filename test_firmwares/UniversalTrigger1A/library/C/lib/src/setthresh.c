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

#include  "UniversalTrigger1A_lib.h"
#include  "UniversalTriggerShared.h"

const char* program_name = "setthresh";

void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage:  %s options [ threshold ]\n", program_name);
  	fprintf (stream,
		DET_TEXT
		GATE_TEXT
		DELAY_TEXT
		INHIB_TEXT
		VERBOSE_TEXT
		SILENT_TEXT
		LOG_TEXT
		VERSION_TEXT
		HELP_TEXT
);
  exit (exit_code);
};

int main(int argc, char* argv[])
{
	//Before reading arguments, turn on all detectors.
	//This makes sure they are all on by default without potentially overwriting user input

	//Read options
	int index;
	int iarg=0;
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "+D:l::shv::V", longopts, &index);

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
			printf("Set Thresh\n");
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
				value = 16777215;
			}else if(strcmp(selection, "22Na") == 0|| strcmp(selection, "Na22") == 0 || strcmp(selection, "Na-22") == 0 || strcmp(selection, "22na") == 0 || strcmp(selection, "na22") == 0 || strcmp(selection, "na-22") == 0){
				value = 7168; //10, 11, 12 (or 11, 12, 13 counting from 1)
			}else if(strcmp(selection, "none") == 0 || strcmp(selection, "None") == 0){
				value = 0;
			}else{ //If it's actually a number, use the number
				value = atoi(selection);
				if(value < 0 || value > 16777215){
					printf("Detector argument invalid. Please supply an integer from 0 to 16777215 or valid source ('PuBe', '22Na', 'All', 'None')");
					return -1;
				};
			};
		case 'g':
			if(verbose > 1){printf ("Splitting string \"%s\" into tokens:\n",optarg);}
				gate_l = atoi(strtok (optarg," ,.-"));
				gate_u = atoi(strtok (NULL," ,.-"));
			if(verbose > 1){printf("%d, %d\n",gate_l,gate_u);}
		}
	}

	//Main argument
  	if(optind==argc){
    	printf("ERROR! No threshold value was given to set.");
    	exit(1);
  	}
  	int thrs = atoi(argv[optind]);

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
		if(verbose > 2){printf("%d: %d, %d \n",i,value >> i, (value >> i) & 1);}
		disable[i] = (value >> i) & 1;
	}
	if(verbose > 1){
		printf("Bit-flipped detector value: %d\n",value);
	}
	if(verbose>0){
		printf("Set to enable triggering for the following detectors: ");
		for(int i=0;i<24;i++){
			if(disable[i] == 0){
				printf("%d, ",i);
			}
		}
		printf("\b\b.\n");
	};
	if(verbose>1){
		printf("Set to disable triggering for the following detectors: ");
		for(int i=0;i<24;i++){
			if(disable[i] == 1){
				printf("%d, ",i);
			}
		}
		printf("\b\b.\n");
	}

	//Connect to the board. 
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

	disable_q[0 ] = REG_disable_det_0_SET (disable[0 ], &handle);
	disable_q[1 ] = REG_disable_det_1_SET (disable[1 ], &handle);
	disable_q[2 ] = REG_disable_det_2_SET (disable[2 ], &handle);
	disable_q[3 ] = REG_disable_det_3_SET (disable[3 ], &handle);
	disable_q[4 ] = REG_disable_det_4_SET (disable[4 ], &handle);
	disable_q[5 ] = REG_disable_det_5_SET (disable[5 ], &handle);
	disable_q[6 ] = REG_disable_det_6_SET (disable[6 ], &handle);
	disable_q[7 ] = REG_disable_det_7_SET (disable[7 ], &handle);
	disable_q[8 ] = REG_disable_det_8_SET (disable[8 ], &handle);
	disable_q[9 ] = REG_disable_det_9_SET (disable[9 ], &handle);
	disable_q[10] = REG_disable_det_10_SET(disable[10], &handle);
	disable_q[11] = REG_disable_det_11_SET(disable[11], &handle);
	disable_q[12] = REG_disable_det_12_SET(disable[12], &handle);
	disable_q[13] = REG_disable_det_13_SET(disable[13], &handle);
	disable_q[14] = REG_disable_det_14_SET(disable[14], &handle);
	disable_q[15] = REG_disable_det_15_SET(disable[15], &handle);
	disable_q[16] = REG_disable_det_16_SET(disable[16], &handle);
	disable_q[17] = REG_disable_det_17_SET(disable[17], &handle);
	disable_q[18] = REG_disable_det_18_SET(disable[18], &handle);
	disable_q[19] = REG_disable_det_19_SET(disable[19], &handle);
	disable_q[20] = REG_disable_det_20_SET(disable[20], &handle);
	disable_q[21] = REG_disable_det_21_SET(disable[21], &handle);
	disable_q[22] = REG_disable_det_22_SET(disable[22], &handle);
	disable_q[23] = REG_disable_det_23_SET(disable[23], &handle);

	for(int i=0; i<24; i++){
		if(disable_q[i] != 0){
			printf("Unable to set on/off state of detector #%d! Aborting.\n",i);
			return -1;
		}
	}

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
