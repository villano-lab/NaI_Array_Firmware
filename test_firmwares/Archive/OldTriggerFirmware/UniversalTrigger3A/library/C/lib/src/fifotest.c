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

#include  "UniversalTrigger3A_lib.h"
#include  "UniversalTriggerShared.h"

const char* program_name = "fifotest";

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
			printf("Scan Rate\n");
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
	int connect_q = connect_staticaddr(verbose);
	if(connect_q != 0){
		printf("Board connection error code: %d\n",connect_q);
		return connect_q;
	}
	
	//set up variables before reset.
	read_q = REG_read_SET(0,&handle);
	if(read_q != 0){
		printf("Error! Failed to set the `read` variable.\n");
		return read_q;
	}
	write_q = REG_write_SET(0,&handle);
	if(write_q != 0){
			printf("Error! Failed to set the `write` variable.\n");
			return write_q;
		}	
	int i=0;
	if(verbose>0){printf("Running until interrupt. Press any key to stop printing.\n");}
	if(verbose>0){printf("If you are not getting any triggers, please try running `setthresh.exe -R` and try again.\n");}
	
	//Reset everything real quick
	ratereset_q = REG_ratereset_SET(1,&handle);
	if(ratereset_q != 0){
		printf("Error! Failed to set the 'reset' variable.\n");
		return ratereset_q;
	}	
	ratereset_q = REG_ratereset_SET(0,&handle);
	if(ratereset_q != 0){
		printf("Error! Failed to set the 'reset' variable.\n");
		return ratereset_q;
	}
	stopwrite_q = REG_stopwrite_SET(0,&handle);
	if(stopwrite_q != 0){
		printf("Error! Failed to set the `stopwrite` variable.\n");
		return stopwrite_q;
	}
	tic = time(NULL);
	empty = 0;
	
	//Main loop!============================================================
	// =====================================================================
	while(empty != 1){
		//print a warning if we're not keeping up.
		end = clock();
		if(verbose > 2){printf("Time spent re-entering the loop: %f us\n.",(double)(end - begin)*1000000/CLOCKS_PER_SEC);}
		begin = clock();
		full_q = REG_full_GET(&full,&handle);
		if(full_q != 0){
			printf("Error! Failed to get the `full` variable.\n");
			return full_q;
		}
		if(full == 1){
			toc = time(NULL);
			if(verbose>-1){printf("WARNING: The FIFO is full! Temporarily disabling writing. Number of entries before filling: %d. Seconds taken to fill FIFO: %d\n",i,(int)toc-(int)tic);}
			if(logfile != NULL){fprintf(logfile,"FIFO was full. Temporarily disabling writing. Seconds to fill fifo: %d.\n",(int)toc-(int)tic);}
			stopwrite_q = REG_stopwrite_SET(1,&handle);
                	if(stopwrite_q != 0){
                        	printf("Error! Failed to set the `stopwrite` variable.\n");
                        	return stopwrite_q;
                	}
		}
		end = clock();
		if(verbose > 2){printf("Time spent handling whether the FIFO was full: %f us\n.",(double)(end - begin)*1000000/CLOCKS_PER_SEC);}
		//read out a piece
		begin = clock();
		read_q = REG_read_SET(1,&handle);
		if(read_q != 0){
			printf("Error! Failed to set the `read` variable.\n");
			return read_q;
		}
		read_q = REG_read_SET(0,&handle);
		if(read_q != 0){
			printf("Error! Failed to set the `read` variable.\n");
			return read_q;
		}
		fifo_q = REG_fifo_GET(&fifo,&handle);
		if(fifo_q != 0){
			printf("Error! Failed to get the `fifo` variable.\n");
			return fifo_q;
		}
		end = clock();
		if(verbose > 2){printf("Time spent retrieving an entry: %f us\n.",(double)(end - begin)*1000000/CLOCKS_PER_SEC);}
		//print fifo variable
		begin = clock();
		i++;
		toc = time(NULL);
		if(verbose > 0 && verbose < 3){printf("%u (%d); ",fifo,i);}
		if(logfile != NULL){fprintf(logfile,"%u (%d)\n",fifo,i);}
		empty_q = REG_empty_GET(&empty,&handle);
		if(empty_q != 0){
			printf("\nError! Failed to get the `empty` variable.\n");
			return empty_q;
		}
		
		end = clock();
		if(verbose > 2){printf("Time spent setting up to start the loop over again: %f us\n.",(double)(end - begin)*1000000/CLOCKS_PER_SEC);}
		begin = clock();
	}
	//when we're done emptying,
	if(verbose > -1){
		fflush(stdout); //flush the print buffer here
		printf("Emptied the FIFO! Number of entries this round (%d seconds): %d (FIFO size: something big that I forgot, like 10 or 100 thousand?).\n",(int)toc-(int)tic,i);
		if(logfile != NULL){fprintf(logfile,"Emptied %d entries over the course of %d seconds.\n",i,(int)toc-(int)tic);}
	}
	
	printf("\n"); //be nice to the terminal
	//stop reading & writing and reset.
	read_q = REG_read_SET(0,&handle);
		if(read_q != 0){
			printf("Error! Failed to set the `write` variable.\n");
			return read_q;}
	write_q = REG_write_SET(0,&handle);
	if(write_q != 0){
			printf("Error! Failed to set the `write` variable.\n");
			return write_q;
		}	
	ratereset_q = REG_ratereset_SET(1,&handle);
	if(ratereset_q != 0){
		printf("Error! Failed to set the 'reset' variable.\n");
		return ratereset_q;
	}	
	ratereset_q = REG_ratereset_SET(0,&handle);
	if(ratereset_q != 0){
		printf("Error! Failed to set the 'reset' variable.\n");
		return ratereset_q;
	}
	return 0;
}	
