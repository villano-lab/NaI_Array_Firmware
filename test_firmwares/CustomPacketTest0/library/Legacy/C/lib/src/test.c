//"Standard" Includes
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
//Includes for this firmware
#include "CustomPacketTest_lib.h"

//Help text
const char* program_name = "test";
void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage: %s [-hv] \n", program_name);
	fprintf (stream, HELP_TEXT);
    fprintf (stream, WAIT_TEXT);

	exit (exit_code);
};

//Other functions
int connect_staticaddr(int verbose){
    R_Init();
	//If can't connect to the board, abort.
	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		if(verbose>-1){printf("Unable to connect to the board!\n");};
		if(logfile != NULL){fprintf(logfile,"Unable to connect to the board at %s!\n",BOARD_IP_ADDRESS);};
		return (-1); 
	}else{
		if(verbose>-1){printf("Connected.\n");};
		if(logfile != NULL){fprintf(logfile,"Connected to board at %s\n",BOARD_IP_ADDRESS);};
        return 0;
	};
}

//Main
int main(int argc, char* argv[])
{
	//Read options
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "h", longopts, &ind);
        switch (iarg){
        case 'h':
            print_usage(stdout,0);
            return 0;
            break;
        case 'v':
			if(optarg){
				verbose = atoi(optarg);
			}else{verbose = 1;};
			break;
        }
    }

    //Connect to the board.
	int connect_q = connect_staticaddr(verbose);
	if(connect_q != 0){
		printf("Board connection error code: %d\n",connect_q);
		return connect_q;
	}
}