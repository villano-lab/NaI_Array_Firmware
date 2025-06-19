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
#include <time.h>
/*//ROOT
#include "TTree.h"
#include "TFile.h"
#include "Rtypes.h"*/

#include  "Integration_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"

bool verbose = false;
//Registers
NI_HANDLE handle;
int cutoff_q;
int gate_q;
int reset_q;
int integral_q;
uint32_t integral;
int delay_q;
int counts_q;
uint32_t counts;

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

	//Open file to write to.
	fp = fopen("../../../data/out.csv","w");

	//Configure settings
	reset_q = REG_Reset_SET(1,&handle); 		//Set everything to off for configuration
	cutoff_q = REG_Cutoff_SET(8192+800,&handle); 	//Set cutoff for GT check
	gate_q = REG_Gate_SET(200,&handle);		//Set number of samples to integrate over
	delay_q = REG_Delay_SET(50,&handle);		//Set number of samples to delay data by
	
	/*//Open ROOT file
	TFile *f = TFile::Open(outputfile.c_str(),"recreate");
	TTree *t = new TTree("peaks","peaks");
	t->Branch("peakval",&dpeakval,"peakval/D");*/

	//Run phase
	reset_q = REG_Reset_SET(0, &handle);
	
	//Collect data
	int imax=1000000;
	for(int i=0; i<imax; i++){
		integral_q = REG_Integral_GET(&integral, &handle);
		// t->Fill();
		if (verbose){ 					// Print the result
			printf("Pulse: %d\n",integral);
		}else{	printf("\b\b\b\b\b\b\b\b\b\b %d",i); } // or print progress only.
		fprintf(fp, "%d\n", integral);			//Save the value
		//clock_t start_time = clock();
		//while (clock() < start_time + 1){ //wait
		//};
	}
	counts_q = REG_Counts_GET(&counts, &handle);
	printf("\n Total count from run: %d\n",counts); //Print the total number of counts from the run
	printf("Counts collected: %d\n",imax-1);
	//*/
	/*t->Write("",TObject::kOverwrite);
	f->Close();*/
	fclose(fp);
	return 0;
}
