// A simple program that takes all newly-detected peaks and prints them to a csv file.
// Currently the integral does not appear to be working -- probably firmware side.
// Is it possible two peaks in a row have the exact same height with no downtime between them?
// Probably not something I need to worry about but it would be good to work that out
// To make sure that it's okay to detect peaks by whether the peak value itself changes.
// If not there is another firmware value I could retrieve 
// but trying to avoid including unecessary variables.
// Trying to move to ROOT but it's causing segfaults before getting into the main func 
// or even before variable declaration?

#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
/*//ROOT
#include "TTree.h"
#include "TFile.h"
#include "Rtypes.h"*/

#include  "DiscriminatorTest4_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"

bool verbose = false;
//Registers
NI_HANDLE handle;
int cutoff_q;
//int counts_q;
//uint32_t counts;

FILE *fp;
/*std::string outputfile="out.root";
std::string BOARD_IP_ADDRESS = "134.84.150.42";
char *board_ip_char = const_cast<char*>(BOARD_IP_ADDRESS.c_str());*/

int main(int argc, char* argv[])
{
	// printf("We made it to the main function.\n");

	//Connect to the board. 
	R_Init();
	//If can't connect to the board, abort.
	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		printf("Unable to connect to the board!\n"); return (-1); 
	};


	//Configure settings
	//cutoff_q = REG_thresh_SET(8192-11,&handle); 	//Set cutoff for GT check
	//cutoff_q = REG_thresh_SET(8192+950,&handle); 	//Set cutoff for GT check
	cutoff_q = REG_thresh_SET(8192-900, &handle);	//Set cutoff for GT check
	//cutoff_q = REG_reset_SET(1,&handle); 	//
	//cutoff_q = REG_reset_SET(0,&handle); 	//
	
	
	//*//Collect data
	int imax=1000000;
	for(int i=0; i<imax; i++){
	//  printf("\n Total count from run: %d\n",counts); //Print the total number of counts from the run
	  printf("Counts collected: %d\n",imax-1);
	}
	//counts_q = REG_Counts_GET(&counts, &handle);
	//printf("\n Total count from run: %d\n",counts); //Print the total number of counts from the run
	printf("Counts collected: %d\n",imax-1);
	return 0;
}
