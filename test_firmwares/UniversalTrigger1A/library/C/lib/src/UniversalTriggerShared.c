#include "UniversalTriggerShared.h"
#include "UniversalTrigger1A_lib.h"
#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

//Variables/*
//=======================================================================================
//Structs
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

//Defaults
int verbose = 0;
int thrs = 4192;	        //amount LESS THAN 8192 for threshold.
uint32_t value = 16777215;
int gate_u = 100; 
int gate_l = 1;
//Register-reading Variables
NI_HANDLE handle;
int thrs_q;
int thrs_q;
int top_q;
int delay_q;
int gate_uq;
int gate_lq;
int inhib_q;
int polarity_q;
char* selection;
int *disable_q; // array of disable instead of 24 initializations
int *disable;
int disable_t[24];
//Command-line-reading Variables
int ind;
int iarg=0;
int gateflag=0;
char* gtemp;
//Other Variables
time_t tic, toc;
FILE *fp;
FILE *logfile;


//Functions
//=======================================================================================

//Printing functions

void copyright(){
    printf("Copyright (c) 2022 Anthony Villano, Kitty Harris \n");
    printf("License: The Expat license  <https://spdx.org/licenses/MIT.html> \n");
    printf("This is free software: you are free to change and redistribute it. \n");
    printf("There is NO WARRANTY, to the extent permitted by law. \n");
}


//Parsing functions
int parse_detector_switch(char* selection){
    int value; //need this in order to parse it inside the else statement.
    if(strcmp(selection,"PuBe") == 0 || strcmp(selection, "All") == 0 || strcmp(selection, "all") == 0){
        return 16777215;
    }else if(strcmp(selection, "22Na") == 0|| strcmp(selection, "Na22") == 0 || strcmp(selection, "Na-22") == 0 || strcmp(selection, "22na") == 0 || strcmp(selection, "na22") == 0 || strcmp(selection, "na-22") == 0){
        return 7168; //10, 11, 12 (or 11, 12, 13 counting from 1)
    }else if(strcmp(selection, "none") == 0 || strcmp(selection, "None") == 0){
        return 0;
    }else{ //If it's actually a number, use the number
        value = atoi(selection);
        if(value < 0 || value > 16777215){
            printf("Detector argument invalid. Please supply an integer from 0 to 16777215 or valid source ('PuBe', '22Na', 'All', 'None')");
            return -1;
        }else{
            return value;
        }
    };
}

//Converting functions
int *on_to_off(int *off, int on, int verbose){
    if(verbose > 1){
		printf("Bitwise detector numeric value supplied: %d\n",on);
	}
	on = on ^ 16777215; //Bitwise flip since we're enabling but firmware is disabling.
	//We'll disable anything that's 1 after the flip and leave everything else on
    if(verbose > 1){
		printf("Bit-flipped detector value: %d\n",value);
	}
	if(verbose > 2){
		for(int i=0;i<24;i++){
			printf("%d",on>>i & 1);
		}
		printf("\n");
	}
    for(int i=0; i<24; i++){
		if(verbose > 1){printf("%d: %d, %d \n",i,on >> i, (on >> i) & 1);}
		off[i] = (on >> i) & 1;
	}
    if(verbose>0){
		printf("Set to enable the following detectors: ");
		for(int i=0;i<24;i++){
			if(disable[i] == 0){
				printf("%d, ",i);
			}
		}
		printf("\b\b.\n");
	};
	if(verbose>1){
		printf("Set to disable the following detectors: ");
		for(int i=0;i<24;i++){
			if(disable[i] == 1){
				printf("%d, ",i);
			}
		}
		printf("\b\b.\n");
	}
    return off;
}

//Other functions

int connect(int verbose){
    R_Init();
	//If can't connect to the board, abort.
	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		if(verbose>-1){printf("Unable to connect to the board!\n");};
		if(logfile != NULL){fprintf(logfile,"Unable to connect to the board at %s!\n",BOARD_IP_ADDRESS);};
		return (-1); 
	}else{
		if(verbose>0){printf("Connected.\n");};
		if(logfile != NULL){fprintf(logfile,"Connected to board at %s\n",BOARD_IP_ADDRESS);};
        return 0;
	};
}

int *disable_dets(int *disable_q, int disable[24]){
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
    return disable_q;
}

int kbhit(void){
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
