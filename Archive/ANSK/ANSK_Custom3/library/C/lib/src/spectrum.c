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

#include  "ANSK_Custom3_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"

bool verbose = true;
//Registers
NI_HANDLE handle;
int thrs_q;
int inib_q;
int polarity_q;
int inttime_q;
int pre_q;
int pileup_q;
int gain_q;
int ofs_q;
int read_q;
int spectrum_q;
int status_q;
uint32_t spectrum_status = 100; //return 100 if it didn't retrieve status correctly.

FILE *fp;
/*std::string outputfile="out.root";
std::string BOARD_IP_ADDRESS = "134.84.150.42";
char *board_ip_char = const_cast<char*>(BOARD_IP_ADDRESS.c_str());*/

int main(int argc, char* argv[])
{
	// printf("We made it to the main function.\n");

	//Connect to the board. 
	if(verbose){printf("Running in verbose mode.\n");};
	R_Init();
	//If can't connect to the board, abort.
	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		printf("Unable to connect to the board!\n"); return (-1); 
	}else{
		printf("Connected.\n");
	};
	//Open file to write to.
	if(verbose){printf("Opening file to write to...\n");};
	fp = fopen("../../../data/out.csv","w");

	//Configure settings
	if(verbose){printf("Configuring...\n");};
	read_q = REG_read_SET(0,&handle);
	thrs_q = REG_thrs_SET(8192+0,&handle); 	//Set cutoff for GT check
	inttime_q = REG_inttime_SET(200,&handle);	//Set number of samples to integrate over
	inib_q = REG_inib_SET(50,&handle);		//Set number of samples to delay data by
	polarity_q = REG_polarity_SET(0,&handle);      //Set polarity to negative
        pre_q = REG_pre_SET(40,&handle);               //Set time between trigger and start of area to integrate
        pileup_q = REG_pileup_SET(40,&handle);         //Set pile-up rejection time
        gain_q = REG_gain_SET(1,&handle);              //Set gain
        ofs_q = REG_ofs_SET(8192,&handle);             //Set offset of baseline(?) for integrator block.

        //Clear acquisition in preparation for run.
	spectrum_q = SPECTRUM_Spectrum_0_STOP(&handle);//Stop acquisition.
        //SPECTRUM_Spectrum_0_FLUSH(&handle);		//Flush all unwanted old data.
        if(verbose){
		status_q = SPECTRUM_Spectrum_0_STATUS(&spectrum_status,&handle);
        	printf("Spectrum run status: %d (Retrieval success code: %d, set success code: %d)\n",spectrum_status,status_q,spectrum_q);
        }
	
	/*//Open ROOT file
	TFile *f = TFile::Open(outputfile.c_str(),"recreate");
	TTree *t = new TTree("peaks","peaks");
	t->Branch("peakval",&dpeakval,"peakval/D");*/

	//Run phase - undo reset
	if(verbose){printf("Running!\n");};
	SPECTRUM_Spectrum_0_START(&handle);
	if(verbose){
        	spectrum_q = SPECTRUM_Spectrum_0_STATUS(&spectrum_status,&handle);
        	printf("Spectrum run status: %d\n",spectrum_status);
        }
	
	//Collect data
	int imax=1000000;
	for(int i=0; i<imax; i++){
		//wait a while
	};
	
	//*/
	/*t->Write("",TObject::kOverwrite);
	f->Close();*/
	fclose(fp);
	return 0;
}
