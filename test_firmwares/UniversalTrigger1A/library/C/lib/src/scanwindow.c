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

const char* program_name = "scanwindow";

void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage:  %s options \n", program_name);
  	fprintf (stream,
		" -d,	--det	<# or source name>	Choose which detectors to trigger on (default: all).\n"
		"					Number values are bitwise from 0 to all 1s in 24 bit (16777215).\n"
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

int main(int argc, char* argv[])
{
	int gateflag = 0;

	//Before reading arguments, turn on all detectors and set gate values.
	//This makes sure they are set to defaults without potentially overwriting user input
	int thrs = 4192;	        //amount LESS THAN 8192 for threshold.
	value = 16777215;
	int gate_u = 100; 
	int gate_l = 1;

	//Read options
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "+d:t:l::shv::Vg:", longopts, &ind);
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
			copyright();
			return 0;
			break;
		case 'l':
			if(optarg){logfile = fopen(optarg,"w");
			}else{logfile = fopen("log.txt","w");};
			break;
		case 'd':
			selection = optarg;
			value = parse_detector_switch(selection);
			if(value < 0 ){return -1;} //If there's an error, pass it through.
			break;
		case 't':
			if(verbose > 1){printf("Threshold supplied: %s\n",optarg);}
			thrs = atoi(optarg);
			if(verbose > 1){printf("Threshold successfully set to %d.\n",thrs);}
			break;
		case 'g':
			if(verbose > 2){printf("Hey I'm in case g\n");}
			gateflag = 1;
			gtemp = optarg;
			break;
		}
	}

	fp = fopen("out.csv","w");

	//Verbosity message
	if(verbose > 0){
		printf("Running in verbose mode. Verbosity: %d\n",verbose);
	};

	//Convert gtemp into the two gates.
	if(gateflag == 1){ //if gate was set,
		if(verbose > 2){printf("Are we even supposed to be here? %d\n",gateflag);}
		if(verbose > 1){printf ("Splitting string \"%s\" into tokens:\n",gtemp);}
			gate_l = atoi(strtok (gtemp," ,.-"));
			gate_u = atoi(strtok (NULL," ,.-"));
		if(verbose > 1){printf("%d, %d\n",gate_l,gate_u);}
	}

	//Detector on/off
	if(verbose > 1){
		printf("Detector string value supplied: %s\n",selection);
	}
	disable = on_to_off(disable_t,value,verbose);

	//Connect to the board. 
	int connect_q = connect(verbose);
	if(connect_q != 0){return connect_q;}

	disable_q = disable_dets(disable_t, disable);

	for(int i=0; i<24; i++){
		if(disable_q[i] != 0){
			printf("Unable to set on/off state of detector #%d! Aborting.\n",i);
			return -1;
		}
	}

	//Configure settings
    int top = thrs; //top of the window in trigger window
	int inhib = 1000;		//inhibition time on trigger block
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
		thrs_q = REG_thrsh_SET(8192-thrs,&handle);	//Set cutoff for GT check
	}else if(polarity==1){
		thrs_q = REG_thrsh_SET(8192+thrs,&handle);	//addition isn't working?
	}else{printf("Polarity is invalid! (Must be 1 or 0.) Aborting...\n"); return -1;}
	top_q = REG_top_SET(8192-top,&handle);	//Set cutoff for GT check
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

	        	top_q = REG_top_SET(8192-top,&handle);	//Set cutoff for GT check

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
