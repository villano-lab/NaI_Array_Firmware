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

#include  "ComputerInteractionTest_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"

//Global Variables
bool verbose = false;
int ret;
int run;
int strobe;
int reset;
int trigger;
int peak;
int testreg;
uint32_t data;
uint32_t counter;
uint32_t strobecount;
uint32_t triggercount;
uint32_t peakval;
uint32_t lastpeak = 0;
double dpeakval;
FILE *fp;
/*std::string outputfile="out.root";
std::string BOARD_IP_ADDRESS = "134.84.150.42";
char *board_ip_char = const_cast<char*>(BOARD_IP_ADDRESS.c_str());*/

int main(int argc, char* argv[])
{
	// printf("We made it to the main function.\n");

	//Configure phase
	fp = fopen("out.csv","w");
	NI_HANDLE handle;	
	R_Init();

	//If can't connect to the board, abort.
	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		printf("Unable to connect to the board!\n"); return (-1); 
	};

	//Set everything to off for configuration
	run = REG_runcfg_SET(0,&handle); 
	reset = REG_reset_SET(1,&handle);
	testreg = REG_counter_GET(&counter, &handle);
	
	/*//Open ROOT file
	TFile *f = TFile::Open(outputfile.c_str(),"recreate");
	TTree *t = new TTree("peaks","peaks");
	t->Branch("peakval",&dpeakval,"peakval/D");*/

	//Run phase
	reset = REG_reset_SET(0, &handle);
	if (counter == 0){
		printf("Counter reset! Collecting data.\n");
	}else{
		printf("Counter did not reset. Aborting.\n");
		return 1;
	}
	run = REG_runcfg_SET(1,&handle); 
	ret = REG_integral_GET(&data, &handle);
	peak = REG_peak_GET(&peakval, &handle);
	
	//*//Collect data
	for(int i=0; i<1000000; i++){
		//ret = REG_integral_GET(&data, &handle);
		testreg = REG_counter_GET(&counter, &handle);
		//strobe = REG_strobecount_GET(&strobecount, &handle);
		//trigger = REG_trigcount_GET(&triggercount, &handle);
		peak = REG_peak_GET(&peakval, &handle);
		// dpeakval = double(peakval);
		// t->Fill();
		if (peakval != lastpeak){
			if (verbose){ // Print a bunch of results
				//printf("Integral: %d\n",data);
				printf("Count: %d\n",counter);
				//printf("Strobe Count: %d\n",strobecount);
				//printf("Trigger Count: %d\n",triggercount);
				printf("Peak: %d\n", peakval);
			// or print progress only.
			}else{	printf("\b\b\b\b\b\b\b\b\b\b %d",i); }
			fprintf(fp, "%d\n", peakval);	//Print the new peak to the file.
			lastpeak = peakval;		//Update the current peak value.
		}
	}//*/
	/*t->Write("",TObject::kOverwrite);
	f->Close();*/
	fclose(fp);
	return 0;
}
