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

#include  "PuBeTrigger6_lib.h"

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
time_t tic, toc;
const char* program_name = "scanrate";
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
	{0,		0,			0,	0},
};

void print_usage(FILE* stream, int exit_code){
	fprintf (stream, "Usage:  %s options [ inputfile(s) ]\n", program_name);
  	fprintf (stream,
	" -v,			--verbose	<level>	Print verbose messages at the specified level (level 1 if unspecified).\n"
	" -s,-q,		--silent,--quiet,		Print nothing.\n"
	" -l,			--log		<file>		Log terminal output.\n"
	" -V, 			--version			Print version and exit.\n"
	" -h,-?,		--help				Print this help function.\n"
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
	//Read options
	int index;
	int iarg=0;
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "+l:n:o:shd:v::V", longopts, &index);

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
		}
	}

	fp = fopen("out.csv","w");

	//Connect to the board. 
	if(verbose > 0){
		printf("Running in verbose mode. Verbosity:%d\n",verbose);
	};
	R_Init();
	//If can't connect to the board, abort.
	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		if(verbose>-1){printf("Unable to connect to the board!\n");};
		if(logfile != NULL){fprintf(logfile,"Unable to connect to the board at %s!\n",BOARD_IP_ADDRESS);};
		return (-1); 
	}else{
		if(verbose>0){printf("Connected.\n");};
		if(logfile != NULL){fprintf(logfile,"Connected to board at %s\n",BOARD_IP_ADDRESS);};
	};

	//Configure settings
	int thrs = 0;	        //amount LESS THAN 8192 for threshold.
        int top = 8192; //way high so it's irrelevant
        int delay = 3; 
        int gate = 10; 
	int inhib = 50;		//inhibition time on trigger block
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
		thrs_q = REG_thrs_SET(8192-thrs,&handle);	//Set cutoff for GT check
	}else if(polarity==1){
		thrs_q = REG_thrs_SET(8192+thrs,&handle);	//addition isn't working?
	}else{printf("Polarity is invalid! (Must be 1 or 0.) Aborting...\n"); return -1;}
        top_q = REG_top_SET(8192-top,&handle);	//set upper level
	inhib_q = REG_inhib_SET(inhib,&handle);			//Set number of samples to delay data by
	delay_q = REG_delay_SET(delay,&handle);			//Set number of samples to delay data by
	gate_q = REG_gate_SET(gate,&handle);			
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
	
	fprintf(fp,"treshold, rate\n"); // add a header row
	if(verbose>0){printf("Collecting data! \n");};
	//Collect data
	int i;
        for(i=0; i<1024; i++){	
            //reset the threshold
			if(verbose>1){printf("Updating threshold:\n");};
			thrs = 8*i;
			if(verbose>1){printf("%d\n",thrs);};

	        if(polarity==0){
	        	thrs_q = REG_thrs_SET(8192-thrs,&handle);	//Set cutoff for GT check
	        }else if(polarity==1){
	        	thrs_q = REG_thrs_SET(8192+thrs,&handle);	//addition isn't working?
	        }else{printf("Polarity is invalid! (Must be 1 or 0.) Aborting...\n"); return -1;}

			//wait
			sleep(10);
			
			//get the rate
			if(verbose > 1){printf("Retreiving data...\n");};
			rate_q=RATE_METER_RateMeter_0_GET_DATA(rateval,ratechan,ratetimeout, &handle, &rateread_data, &ratevalid_data);
			if(verbose > 1){printf("Rateval: %f\n",rateval[0]/10.0);};

			//write the rate
			fprintf(fp,"%d, %f\n",thrs,rateval[0]/10.0);
	        if(verbose>1){printf("thresh: %d ; rate: %f Hz\n",thrs,rateval[0]/10.0);};
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
