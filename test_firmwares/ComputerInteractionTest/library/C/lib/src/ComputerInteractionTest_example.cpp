#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
//ROOT
#include "TTree.h"
#include "TFile.h"
#include "Rtypes.h"

#include  "ComputerInteractionTest_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"

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
std::string outputfile="out.root";

int main(int argc, char* argv[])
{
	//Configure phase
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
	
	//Open ROOT file
	TFile *f = TFile::Open(outputfile.c_str(),"recreate");
	TTree *t = new TTree("peaks","peaks");
	t->Branch("peakval",&dpeakval,"peakval/D");

	//Run phase
	reset = REG_reset_SET(0, &handle);
	printf("counter (reset=0): %d\n",counter);
	run = REG_runcfg_SET(1,&handle); 
	printf("Run       :%d\n",run);
	ret = REG_integral_GET(&data, &handle);
	printf("Data (run): %d\n",data);
	printf("Ret       : %d\n",ret);
	peak = REG_peak_GET(&peakval, &handle);
	printf("Peak working? %d\n",peak);
	printf("Peak (run): %d\n",peakval);
	
	//*//While loop for checking for flukes
	for(int i=0; i++; i<100000000){
		ret = REG_integral_GET(&data, &handle);
		testreg = REG_counter_GET(&counter, &handle);
		strobe = REG_strobecount_GET(&strobecount, &handle);
		trigger = REG_trigcount_GET(&triggercount, &handle);
		peak = REG_peak_GET(&peakval, &handle);
		dpeakval = double(peakval);
		t->Fill();
		if (peakval != lastpeak){
			
			if (verbose){ // Print a bunch of results
				printf("Integral: %d\n",data);
				printf("Count: %d\n",counter);
				printf("Strobe Count: %d\n",strobecount);
				printf("Trigger Count: %d\n",triggercount);
				printf("Peak: %d\n", peakval);
			}
			lastpeak = peakval;
		}
		
	}//*/
	t->Write("",TObject::kOverwrite);
	f->Close();
	return 0;
}
