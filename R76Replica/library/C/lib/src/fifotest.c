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

/*//ROOT
#include "TTree.h"
#include "TFile.h"
#include "Rtypes.h"*/

//#include  "Legacy/R76Firmware_lib.h"
#include  "UniversalTriggerShared.h"

const char* program_name = "fifotest";
FILE *fp;

void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage:  %s options \n", program_name);
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
	clock_t begin, end;
	//Read options
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "d:i:l::shv::Vg:D:T:", longopts, &ind);
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
			printf("FIFO Test\n");
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

	spectra_STATUS(spectra_t);
        for(i=0;i<24;i++){
                printf("Status spectrum #%d: %d\n",i,spectra_t[i]);
        }

	//set up variables before reset.
	int_time_q = __abstracted_reg_write(int_time,SCI_REG_int_time,(NI_HANDLE*)sdk);
	if(int_time_q != 0){
		printf("Error! Failed to set the `int_time` variable. \n");
		return int_time_q;
	}
	pre_int_q = __abstracted_reg_write(pre_int_q,SCI_REG_int_pre,(NI_HANDLE*)sdk);
	if(pre_int_q != 0){
		printf("Error! Failed to set the `pre_int` variable. \n");
		return pre_int;
	}
	__abstracted_reg_write(baseline_q,SCI_REG_base_CH0,(NI_HANDLE*)sdk);
	baseline_q = __abstracted_reg_write(baseline_q,SCI_REG_base_CH1,(NI_HANDLE*)sdk);
	if(baseline_q != 0){
		printf("Error! Failed to set the `baseline` variable. \n");
		return baseline;
	}
	if(verbose>0){printf("If you are not getting any triggers, please try resetting register values by running `./setregisters -R` and try again.\n");}

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
	int empty = 0;

	if(verbose > 0){printf("Setup complete; starting acquisition.\n");}
	//Main loop!============================================================
	// =====================================================================
	// CPACK_CP_0_START((NI_HANDLE*)sdk); //comment out if no custom packet yet
	sleep(30); //wait a little while so we can get some data before exiting.
	while(empty != 1){
		//print a warning if we're not keeping up.
		end = clock();
		if(verbose > 2){printf("Time spent re-entering the loop: %f us\n.",(double)(end - begin)*1000000/CLOCKS_PER_SEC);}
		begin = clock();
		//read out a piece
		/*available_q = CPACK_CP_0_DATA_AVAILABLE(&available,(NI_HANDLE*)sdk); //comment out if no custom packet yet
		if(available_q != 0){
			printf("Error! Failed to check for available data from custom packet.\n");
			return available_q;
		}
		status_q = CPACK_CP_0_STATUS(&status,(NI_HANDLE*)sdk);
		if(status_q != 0){
			printf("Error! Failed to check status of custom packet.\n");
			return status_q;
		}*/
		/*no longer works this way
		fifo_q = REG_fifo_GET(&fifo,(NI_HANDLE*)sdk);
		if(fifo_q != 0){
			printf("Error! Failed to download data from fifo.\n");
			return fifo_q;
		}*/
		end = clock();
		if(verbose > 2){printf("Time spent retrieving an entry: %f us\n.",(double)(end - begin)*1000000/CLOCKS_PER_SEC);}
		//print fifo variable
		begin = clock();
		i++;
		toc = time(NULL);
		fflush(stdout); //flush the print buffer here
		if(verbose > 0 && verbose < 3){printf("Result: %u (#%d)\n",fifo,i);}
		if(logfile != NULL){fprintf(logfile,"%u (%d)\n",fifo,i);}
		/*register no longer exists
		empty_q = REG_empty_GET(&empty,(NI_HANDLE*)sdk);
		if(empty_q != 0){
			printf("\nError! Failed to get the `empty` variable.\n");
			return empty_q;
		}*/
		end = clock();
		if(verbose > 2){printf("Time spent setting up to start the loop over again: %f us\n.",(double)(end - begin)*1000000/CLOCKS_PER_SEC);}
		begin = clock();
	}
	//when we're done emptying,
	if(verbose > -1){
		fflush(stdout); //flush the print buffer here
		printf("Emptied the FIFO! Number of entries this round (%d seconds): %d (FIFO size: 131072).\n",(int)toc-(int)tic,i);
		if(logfile != NULL){fprintf(logfile,"Emptied %d entries over the course of %d seconds.\n",i,(int)toc-(int)tic);}
	}

	//stop reading & writing and reset.
	if(verbose>0){printf("Stopping FIFO...\n");}
	reset_q = REG_reset_SET(0,(NI_HANDLE*)sdk);
        if(reset_q != 0){
                printf("Error! Failed to set the 'reset' variable.\n");
                return reset_q;
        }
	reset_q = REG_reset_SET(1,(NI_HANDLE*)sdk);
	if(reset_q != 0){
		printf("Error! Failed to set the 'reset' variable.\n");
		return reset_q;
	}

	// Spectrum section
	if(verbose>0){printf("Testing spectrum...\n");}
	spectra_STOP(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to stop spectrum %d.\n",i);
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

	spectra_FLUSH(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to flush spectrum %d.\n",i);
			return spectra_t[i];
		}
	}

	spectra_START(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to start spectrum %d.\n",i);
			return spectra_t[i];
		}
	}

	if(verbose>0){printf("Taking spectrum data for 100 seconds...\n");}
	sleep(10000);

	spectra_STOP(spectra_t);
	for(i=0;i<24;i++){
		if(spectra_t[i] != 0){
			printf("Error! Failed to stop spectrum %d.\n",i);
			return spectra_t[i];
		}
	}

	if(verbose>0){printf("Done taking spectrum data!\n");}
	spectra_STATUS(spectra_t);
	for(i=0;i<24;i++){
		printf("Status spectrum #%d: %d\n",i,spectra_t[i]);
	}

	spectra_DOWNLOAD(spec_dl,1000,spectra_t,specvalid_t);
	for(i=0;i<32;i++){
		printf("Downloaded data (Spectrum #%d): \n",i);
			for(int j=0;j<BUFFER_SIZE+17;j++){
				printf("%d, ",spec_dl[i+j]);
			}
		printf("\n\n\n");
	}

	return 0;
}	
