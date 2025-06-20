#include "Legacy/Def.h"
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

//#include  "Legacy/R76Firmware_lib.h"
#include  "UniversalTriggerShared.h"

const char* program_name = "getspectrum";
int waittime=12; //default 2 minutes data
FILE *fp;

void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage:  %s options \n", program_name);
    fprintf (stream, WAIT_TEXT);
	fprintf (stream, VERBOSE_TEXT);
	fprintf (stream, SILENT_TEXT);
	fprintf (stream, LOG_TEXT);
	fprintf (stream, VERSION_TEXT);
	fprintf (stream, HELP_TEXT);

	exit (exit_code);
};


int main(int argc, char* argv[])
{
	SciSDK* sdk = new SciSDK;
	//Read options
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "l::sh?v::Vw:", longopts, &ind);
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
			if(optarg){
				verbose = atoi(optarg);
			}else{verbose = 1;};
			break;
		case '?':
			print_usage(stdout,0);
			return 0;
			break;
		case 'V':
			printf("Get Spectrum\n");
			copyright();
			return 0;
			break;
		case 'l':
			if(optarg){
				logfile = fopen(optarg,"w");
			}else{
				logfile = fopen("log.txt","w");
			};
			break;
        case 'w':
            waittime = atoi(optarg);
            break;
		}
	}

	fp = fopen("out.csv","w");

	//Verbosity message
	if(verbose > 0){
		printf("Running in verbose mode. Verbosity: %d\n",verbose);
	};

	//Connect to the board.
        SciSDK* _sdk = new SciSDK;
        int connect_q = SCIDK_ConnectUSB(BOARD_SERIAL_NUMBER,(NI_HANDLE*)_sdk);
	if(connect_q != 0){
		printf("Board connection error code: %d\n",connect_q);
		return connect_q;
	}

	int i=0;

	//Reset everything real quick
	reset_q = REG_reset_SET(1,(NI_HANDLE*)sdk);
	if(reset_q != 0){
		printf("Error! Failed to set the 'reset' variable.\n");
		return reset_q;
	}
	reset_q = REG_reset_SET(0,(NI_HANDLE*)sdk);
	if(reset_q != 0){
		printf("Error! Failed to set the 'reset' variable.\n");
		return reset_q;
	}
	tic = time(NULL);

	// Spectrum section
	/* this doesn't work, and I don't think it has ever worked.
	spectra_PARAMS(spectra_t,0,0,0);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to set parameters for spectrum %d.\n",i);
			return spectra_t[i];
		}
	}*/

	spectra_STOP(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to stop spectrum %d.\n",i);
			return spectra_t[i];
		}
	}

	spectra_FLUSH(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to flush spectrum %d.\n",i);
			return spectra_t[i];
		}
	}

	spectra_RESET(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to reset spectrum %d.\n",i);
			return spectra_t[i];
		}
	}

	if(verbose > 0){printf("Setup complete; starting acquisition.\n");}

	spectra_START(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to start spectrum %d.\n",i);
			return spectra_t[i];
		}
	}
    
	spectra_STATUS(spectra_t);
	for(i=0;i<24;i++){
		if(verbose>0){printf("Status spectrum #%d: %d\n",i,spectra_t[i]);}
	}

    if(verbose > 0){printf("Gathering data for %d seconds.\n",waittime*10);}
    for(i=0;i < waittime;i++){
        if(verbose > 0){printf("%f %% \r",(double)i/waittime);}
        sleep(10); //wait a little while so we can get some data before exiting.
    }

	spectra_STOP(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to stop spectrum %d.\n",i);
			return spectra_t[i];
		}
	}

	uint32_t temp = SPECTRUM_Spectrum_0_STOP((NI_HANDLE*)sdk);
	if(temp != 0){
		printf("Error! Failed to stop spectrum 0.\n");
		return temp;
	}
	uint32_t temp2 = SPECTRUM_Spectrum_0_STATUS(&temp,(NI_HANDLE*)sdk);
	if(temp2 != 0){
		printf("Error! Faield to retrieve status of spectrum 0.\n");
		return temp2;
	}
	printf("Spectrum 0 status: %d\n",temp);
	

	sleep(1); //maybe it needs a moment to catch up?

	if(verbose>0){printf("Done taking spectrum data!\n");}
	spectra_STATUS(spectra_t);
	for(i=0;i<24;i++){
		if(verbose>0){printf("Status spectrum #%d: %d\n",i,spectra_t[i]);}
	}

	spectra_DOWNLOAD(spec_dl,1000,spectra_t,specvalid_t);
	for(i=0;i<32;i++){
		printf("Donwloaded data (Spectrum #%d): \n",i);
			for(int j=0;j<BUFFER_SIZE+17;j++){
				printf("%d, ",spec_dl[i+j]);
			}
		printf("\n\n\n");
	}

	return 0;
}	
