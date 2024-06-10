#include "UniversalTriggerShared.h"
//#include "Legacy/R76Replica_lib.h"
//#include "R76Replica_lib.h" //double include?
//#include "Legacy/Def.h"
//#include "Def.h" //double include?
#include "Legacy/RegisterFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
//blind copy from example
#include "../scisdk_rebuild/scisdk_defines.h"
#include "../scisdk_rebuild/SciSDK_DLL.h"
#include "../scisdk_rebuild/NIErrorCode.h"
#include "../scisdk_rebuild/scisdk_core.h"
#include "SCIDK_Lib.h"

//Variables
//=======================================================================================
//Structs
const struct option longopts[] =
{
	{"gate",	required_argument,	0,	'g'},
	{"delay",	required_argument,	0,	'd'},
	{"inhibit",	required_argument,	0,	'i'},
	{"help",	no_argument,		0,	'h'},
	{"log",		optional_argument,	0,	'l'},
	{"quiet",	no_argument,		0,	'q'},
	{"silent",	no_argument,		0,	's'},
	{"verbose",	optional_argument,	0,	'v'},
	{"version",	no_argument,		0,	'V'},
	{"det",		required_argument,	0,	'D'},
	{"thresh",	required_argument,	0,	't'},
	{"top",		required_argument,	0,	'T'},
	{"range",	required_argument,	0,	'r'},
	{"reset",	no_argument,		0,	'R'},
	{"force",	no_argument,		0,	'f'},
	{"skip",	required_argument,	0,	'S'},
	{"polarity",optional_argument,	0,	'p'},
	{"pre-int",	required_argument,	0,	'P'},
	{"int-time",required_argument,	0,	'I'},
	{"config",	optional_argument,	0,	'c'},
	{"wait",	required_argument,	0,	'w'},
	{0,		0,			0,	0},
};

//Defaults
int verbose = 0;
float thrs = 14300;	        //distance from baseline for threshold.
uint32_t value = 4294967295;
int gate_u = 100;
int gate_l = 10;
float range_l = 0;
float range_u = 8;
float range_s = 1;
int delay = 20;
int inhib = 1000;
int baseline = 0;
float top = 100000000;
int int_time = 250; //this seems to be a good default based on oscilloscope readout.
int pre_int = 100;   //^same here
//things you probably won't change
int polarity = 1;	//zero for negative, one for positive
//Register-reading Variables
int delay_q;
int gate_uq;
int gate_lq;
int inhib_q;
int polarity_q;
char* selection;
int *disable_q; // array of disable instead of 24 initializations
int *disable;
int *thresh_q;
//int *spectra_qs; //need separate type for spectra_q when holding values vs success
uint32_t *spectra_q;
uint32_t *specread_q;
uint32_t *specvalid_q;
int disable_t[32];
int thresh_t[32];
uint32_t spectra_t[32];
int specdat[32*17*BUFFER_SIZE];
uint32_t specvalid_t[32];
uint32_t spec_dl[32*17*BUFFER_SIZE];
uint32_t size = 1024;
int reset_q;
int read_q;
int write_q;
int empty_q;
int full_q;
int fifo_q;
int skip_q;
int custom_q;
int int_time_q;
int baseline_q;
int pre_int_q;
int stopwrite_q;
uint32_t read_data;
uint32_t valid_data;
uint32_t custom;
uint32_t status;
uint32_t skip = -1; //by default, don't skip pieces.
uint32_t fifo;
uint32_t empty;
uint32_t full;
//Command-line-reading Variables
int ind;
int iarg=0;
int gateflag=0;
int gateflagu=0;
int gateflagl=0;
int rangeflag=0;
int delayflag=0;
int inhibflag=0;
int threshflag=0;
int detflag=0;
int topflag=0;
int polflag=0;
int skipflag=0;
int preflag=0;
int intflag=0;
int baseflag=0;
int reset=0;
int force=0;
int wait=1;
const char* configfilename;
char* rtemp;
char* gtemp;
//Other Variables
int i;
char userinput[3];
time_t tic, toc;
FILE *logfile;
FILE *configfile;
//Rate Counter Variables
int rate_q;
int unreduced_q;
uint32_t unreduced[160];
uint32_t rateval[160]; //needs to be pre-allocated
uint32_t ratechan=1;
uint32_t ratetimeout=10; //timeout in ms
uint32_t rateread_data=0;
uint32_t ratevalid_data=0;

//Functions
//=======================================================================================

//Printing functions
//https://stackoverflow.com/a/700184
void printbits(unsigned char v) {
  int i; // for C89 compatability
  for(i = 24; i >= 0; i--) putchar('0' + ((v >> i) & 1));
}
void copyright(){
    printf("Copyright (c) 2022 Anthony Villano, Kitty Harris \n");
    printf("License: The Expat license  <https://spdx.org/licenses/MIT.html> \n");
    printf("This is free software: you are free to change and redistribute it. \n");
    printf("There is NO WARRANTY, to the extent permitted by law. \n");
}
void subhelp(FILE* stream){
	fprintf (stream, "\n===============================================================\n");
	fprintf (stream, "setregisters: utility for setting register values\n");
	fprintf (stream, "----------\n");
	system("./setregisters -h");
}

//Parsing functions
int parse_detector_switch(char* selection){
    if(strcasecmp(selection,"muon") == 0 || strcasecmp(selection,"muons") == 0){
    	return 14680064; //21, 22, 23
    }else if(strcasecmp(selection,"PuBe") == 0 || strcasecmp(selection, "All") == 0 ){
        return 4294967295;
    }else if(strcasecmp(selection, "NaI") == 0 || strcasecmp(selection, "22na") == 0 || strcasecmp(selection, "na22") == 0 || strcasecmp(selection, "na-22") == 0){
        return 7168; //10, 11, 12
    }else if(strcasecmp(selection, "none") == 0){
        return 0;
    }else{ //If it's actually a number, use the number
        value = atoi(selection);
        if(value < 0 || value > 4294967295){
            printf("Detector argument invalid. Please supply an integer from 0 to 4294967295 or valid source ('PuBe', '22Na', 'Muon', 'All', 'None')");
            return -1;
        }else{
            return value;
        }
    };
}
int parse_gate(char* gatestring, int verbose){
	if(gatestring != NULL){
		if(verbose > 2){printf("Are we even supposed to be here? %d\n",gateflag);}
		if(verbose > 1){printf ("Splitting string \"%s\" into tokens:\n",gatestring);}
		gate_l = atoi(strtok (gatestring," ,.-:"));
		gate_u = atoi(strtok (NULL," ,.-:"));
	}else{
		if(verbose > 0){printf("Using default values for gates, lower %d and upper %d.\n",gate_l,gate_u);}
	}
		if(verbose > 1){printf("%d, %d\n",gate_l,gate_u);}
	return(gate_l); //really though why are these ints instead of void
}
int parse_range(char* rangestring, int verbose){
	if(verbose > 2){printf("Are we even supposed to be here? %d\n",rangeflag);}
	if(verbose > 1){printf ("Splitting string \"%s\" into tokens:\n",rangestring);}
	range_l = atof(strtok (rangestring," ,-:"));
	range_u = atof(strtok (NULL," ,-:"));
	range_s = atof(strtok (NULL," ,-:"));
	if(verbose > 1){printf("%f, %f, %f\n",range_l,range_u,range_s);}
	return(range_l); //don't know why I made this an int but this seems useful.
}
void print_timestamp(int elapsed, int verbose){
	int hours = floor(elapsed / 3600);
	int minutes = floor((elapsed % 3600)/60);
	int seconds = floor(elapsed % 60);
	if(verbose>-1){printf("Time elapsed: %02d:%02d:%02d \n",hours,minutes,seconds);};
	if(verbose>1){printf("Closing files...");};
}
void read_config(const char* filename){
	configfile = fopen(filename,"r");
	char line[256]; //declare the line variable
	int linenumber = 0;
	while(fgets(line, 256, configfile) != NULL){
		linenumber++;
		char arg[128],val[128];
		//printf("Checking if comment... ");
		if(line[0] == '#' || line[0] == '\n' || strcmp(line,"\n") == 0 || strcmp(line,"\r\n") == 0){continue;} //skip comments and blanks
		//printf("Not comment.\n");
		if(sscanf(line, "%s %s", arg, val) != 2){
			fprintf(stderr, "Syntax error, line %d: %s", linenumber, line);
			continue;
		}
		if(strcasecmp(arg,"delay") == 0 || strcasecmp(arg,"del") == 0){
			delay = atoi(val);
			delayflag = 1;
		}else if(strcasecmp(arg,"detectors") == 0 || strcasecmp(arg,"det") == 0 || strcasecmp(arg,"dets") == 0){
			value = parse_detector_switch(val);
			if(value < 0){exit(value);}
			detflag = 1;
		}else if(strcasecmp(arg,"gate_lower") == 0 || strcasecmp(arg,"gate_l") == 0 || strcasecmp(arg,"gl") == 0 || strcasecmp(arg,"g_l") == 0 || strcasecmp(arg,"gate_low") == 0){
			gate_l = atoi(val);
			gateflagl = 1;
		}else if(strcasecmp(arg,"gate_upper") == 0 || strcasecmp(arg,"gate_u") == 0 || strcasecmp(arg,"gu") == 0 || strcasecmp(arg,"g_u") == 0 || strcasecmp(arg,"gate_up") == 0 || strcasecmp(arg,"gate_hi") == 0 || strcasecmp(arg,"gate_high") == 0){
			gate_u = atoi(val);
			gateflagu = 1;
		}else if(strcasecmp(arg,"inhib") == 0 || strcasecmp(arg,"inhibit") == 0 || strcasecmp(arg,"inhibition") == 0){
			inhib = atoi(val);
			inhibflag = 1;
		}else if(strcasecmp(arg,"log") == 0 || strcasecmp(arg,"logging") == 0 || strcasecmp(arg,"logfile") == 0){
			logfile = fopen(val,"w");
		}else if(strcasecmp(arg,"range_lower") == 0){
			range_l = atoi(val);
		}else if(strcasecmp(arg,"range_upper") == 0){
			range_u = atoi(val);
		}else if(strcasecmp(arg,"range_stepsize") == 0){
			range_s = atoi(val);
		}else if(strcasecmp(arg,"thresh_lower") == 0 || strcasecmp(arg,"thresh") == 0){
			thrs = atof(val);
			threshflag = 1;
		}else if(strcasecmp(arg,"thresh_upper") == 0 || strcasecmp(arg,"thresh_top") == 0 || strcasecmp(arg,"top") == 0){
			top = atof(val);
			topflag = 1;
		}
	}
	fclose(configfile);
}

//Converting functions
int *on_to_off(int *off, int on, int verbose){
    if(verbose > 1){
		printf("Bitwise detector numeric value supplied: %d\n",on);
	}
	on = on ^ 4294967295; //Bitwise flip since we're enabling but firmware is disabling.
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
		if(verbose > 2){printf("success!\n");}
	}
	// if(verbose > 2){printf("moving on...\n");}
    if(verbose>0){
		printf("Set to enable the following detectors: ");
		for(int i=0;i<32;i++){
			if(off[i] == 0){
				printf("%d, ",i);
			}
		}
		printf("\b\b.\n");
	};
	if(verbose>1){
		printf("Set to disable the following detectors: ");
		for(int i=0;i<32;i++){
			if(off[i] == 1){
				printf("%d, ",i);
			}
		}
		printf("\b\b.\n");
	}
    return off;
}
int energy_to_bin(int detnum, float energy){ //take an energy (MeV) and convert it to a bin number
	// convert to keV, since that's how our calibrations were done
	return energy; //circumvent all this other code; don't want to bother calibrating.
	float bin;
	energy = energy * 1000;
	if(detnum == 0){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 1){
		bin = 1.44*energy + 288.21;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 2){
		bin = 1.29*energy + 258.69;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 3){
		bin = 1.28*energy + 318.06;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 4){
		bin = 1.29*energy + 233.09;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 5){
		bin = 1.28*energy + 197.68;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 6){
		bin = 1.36*energy + 321.82;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 7){
		bin = 1.15*energy + 261.98;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 8){
		bin = 1.17*energy + 284.21;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 9){
		bin = 1.42*energy + 389.04;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 10){
		bin = 1.29*energy + 329.41;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 11){
		bin = 1.32*energy + 282.30;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 12){
		bin = 1.26*energy + 319.53;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 13){
		bin = 1.22*energy + 389.48;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 14){
		bin = 1.36*energy + 203.09;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 15){
		bin = 1.12*energy + 421.60;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 16){
		bin = 1.34*energy + 272.15;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 17){
		bin = 1.23*energy + 308.12;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 18){
		bin = 1.28*energy + 267.85;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 19){
		bin = 1.22*energy + 293.62;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 20){
		bin = 1.44*energy + 299.07;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 21){
		bin = 1.18*energy + 286.40;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 22){
		bin = 1.06*energy + 243.29;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 23){
		bin = 1.36*energy + 334.94;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 24){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 25){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 26){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 27){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 28){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 29){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 30){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else if(detnum == 31){
		bin = energy;
		if(verbose > 3){printf("Bin value: %f\n",bin);}
		return bin;
	}else{
		printf("Invalid detector number %d supplied to energy_to_bin function. Must supply a number 0-31.\n",detnum);
		exit(-1);
	}
}

//Other functions

int *disable_dets(int *disable_q, int disable[32], SciSDK* _sdk){
	disable_q[0 ] = __abstracted_reg_write(disable[0 ], SCI_REG_disable_det_CH0, (NI_HANDLE*)_sdk);
	disable_q[1 ] = __abstracted_reg_write(disable[1 ], SCI_REG_disable_det_CH1, (NI_HANDLE*)_sdk);
    return disable_q;
}

int *set_thresholds(const char* side, int polarity, float energy, int *thresh_q, SciSDK* _sdk){
	if(strcasecmp(side,"lower") == 0 || strcasecmp(side,"thrs") == 0 || strcasecmp(side,"thresh") == 0 || strcasecmp(side,"thrsh") == 0 || strcasecmp(side,"lo") == 0 || strcasecmp(side,"low") == 0){
		thresh_q[0 ] = set_by_polarity(SCI_REG_thrsh_CH0, polarity,energy_to_bin(0 ,energy), _sdk);
		thresh_q[1 ] = set_by_polarity(SCI_REG_thrsh_CH1, polarity,energy_to_bin(1 ,energy),_sdk);
	}else if(strcasecmp(side,"upper") == 0 || strcasecmp(side,"up") == 0 || strcasecmp(side,"hi") == 0 || strcasecmp(side,"higher") == 0 || strcasecmp(side,"high") == 0 || strcasecmp(side,"top") == 0){
		thresh_q[0 ] = set_by_polarity(SCI_REG_top_CH0, polarity,energy_to_bin(0 ,energy),_sdk);
		thresh_q[1 ] = set_by_polarity(SCI_REG_top_CH1, polarity,energy_to_bin(1 ,energy),_sdk);
	}else{
		printf("Invalid 'side' passed to set_thresholds. Please submit a bug report.\n");
		exit(-1);
	}
	return thresh_q;
}

uint32_t *spectra_START(uint32_t *spectra_q,SciSDK* _sdk){
	spectra_q[0 ] = SPECTRUM_Spectrum_0_START ((NI_HANDLE*)_sdk);
	spectra_q[1 ] = SPECTRUM_Spectrum_1_START ((NI_HANDLE*)_sdk);
	return spectra_q;
}

uint32_t *spectra_STOP(uint32_t *spectra_q,SciSDK* _sdk){
	spectra_q[0 ] = SPECTRUM_Spectrum_0_STOP ((NI_HANDLE*)_sdk);
	spectra_q[1 ] = SPECTRUM_Spectrum_1_STOP ((NI_HANDLE*)_sdk);
	return spectra_q;
}

uint32_t *spectra_FLUSH(uint32_t *spectra_q,SciSDK* _sdk){
	spectra_q[0 ] = SPECTRUM_Spectrum_0_FLUSH ((NI_HANDLE*)_sdk);
	spectra_q[1 ] = SPECTRUM_Spectrum_1_FLUSH ((NI_HANDLE*)_sdk);
	return spectra_q;
}

uint32_t *spectra_RESET(uint32_t *spectra_q,SciSDK* _sdk){
	spectra_q[0 ] = SPECTRUM_Spectrum_0_RESET ((NI_HANDLE*)_sdk);
	spectra_q[1 ] = SPECTRUM_Spectrum_1_RESET ((NI_HANDLE*)_sdk);
	return spectra_q;
}

uint32_t *spectra_SET(uint32_t rebin, uint32_t limit_mode, uint32_t limit_value, uint32_t *spectra_q,SciSDK* _sdk){
	spectra_q[0 ] = SPECTRUM_Spectrum_0_SET_PARAMETERS (rebin,limit_mode,limit_value,(NI_HANDLE*)_sdk);
	spectra_q[1 ] = SPECTRUM_Spectrum_1_SET_PARAMETERS (rebin,limit_mode,limit_value,(NI_HANDLE*)_sdk);
	return spectra_q;
}

uint32_t *spectra_STATUS(uint32_t *spectra_q,SciSDK* _sdk){
	SPECTRUM_Spectrum_0_STATUS (&spectra_q[0 ],(NI_HANDLE*)_sdk);
	SPECTRUM_Spectrum_1_STATUS (&spectra_q[1 ],(NI_HANDLE*)_sdk);
	return spectra_q;
}

uint32_t *spectra_DOWNLOAD(uint32_t *specdat, uint32_t timeout, uint32_t *specread_q, uint32_t *specvalid_q, SciSDK* _sdk){
	SPECTRUM_Spectrum_0_DOWNLOAD (&specdat[0 *17*BUFFER_SIZE],BUFFER_SIZE, timeout, (NI_HANDLE*)_sdk, &specread_q[0 ], &specvalid_q[0 ]);
	SPECTRUM_Spectrum_1_DOWNLOAD (&specdat[1 *17*BUFFER_SIZE],BUFFER_SIZE, timeout, (NI_HANDLE*)_sdk, &specread_q[1 ], &specvalid_q[1 ]);
	return specdat;
}

int set_by_polarity(uint32_t address, int polarity, int value,SciSDK* _sdk){
	if(polarity==0){
		uint32_t newval = baseline - value;
		return __abstracted_reg_write(newval,address,(NI_HANDLE*)_sdk);
	}else if(polarity==1){
		uint32_t newval = baseline + value;
		return __abstracted_reg_write(newval,address,(NI_HANDLE*)_sdk);
	}else{
		printf("Polarity is invalid! (Must be 1 or 0; was %d.)\n",polarity);
		return -1;
	}
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

