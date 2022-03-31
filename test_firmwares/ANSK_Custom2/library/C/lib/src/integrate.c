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
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
/*//ROOT
#include "TTree.h"
#include "TFile.h"
#include "Rtypes.h"*/

#include  "ANSK_Custom2_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"

bool verbose = false;
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
int baseline_q;
int read_q;
int energy_q;
uint32_t energy;
int empty_q;
uint32_t empty;

FILE *fp;
/*std::string outputfile="out.root";
std::string BOARD_IP_ADDRESS = "134.84.150.42";
char *board_ip_char = const_cast<char*>(BOARD_IP_ADDRESS.c_str());*/

int kbhit(void)
        {
          struct termios oldt, newt;
          int ch;
          int oldf;

          tcgetattr(STDIN_FILENO, &oldt);
          newt = oldt;
          newt.c_lflag &= ~(ICANON | ECHO);
          tcsetattr(STDIN_FILENO, TCSANOW, &newt);
          oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
          fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

          ch = getchar();

          tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
          fcntl(STDIN_FILENO, F_SETFL, oldf);

          if(ch != EOF)
          {
            ungetc(ch, stdin);
            return 1;
          }

          return 0;
        }

int main(int argc, char* argv[])
{
	clock_t start = clock();
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

	//Automatically generate a filename.
	char* filepath = "../../../data/";
	char* filename;
	//char* threshstr = "_t%d",(abs(thrs - 8192));
	
	//char filename = "_t" + (str)(abs(thrs - 8192)) + "_i" + (str)inttime + "-" + (str)pre + "-" + (str)pileup + "_h" + (str)inib + "_g" + (str)gain + "-.csv"
	//Open file to write to.
	if(verbose){printf("Opening file to write to...\n");};
	fp = fopen("../../../data/out.csv","w");

	//Configure settings
	if(verbose){printf("Configuring...\n");};
	read_q = REG_read_SET(0,&handle);
	thrs_q = REG_thrs_SET(8192-250,&handle); 	//Set cutoff for GT check
	inttime_q = REG_inttime_SET(100,&handle);	//Set number of samples to integrate over
	inib_q = REG_inib_SET(50,&handle);		//Set number of samples to delay data by
	polarity_q = REG_polarity_SET(0,&handle);      //Set polarity to negative
        pre_q = REG_pre_SET(80,&handle);               //Set time between trigger and start of area to integrate
        pileup_q = REG_pileup_SET(200,&handle);	//Set pile-up rejection time
        gain_q = REG_gain_SET(100,&handle);		//Set gain
        ofs_q = REG_ofs_SET(0,&handle);			//Set offset to supply for integrator block.
	
	/*//Open ROOT file
	TFile *f = TFile::Open(outputfile.c_str(),"recreate");
	TTree *t = new TTree("peaks","peaks");
	t->Branch("peakval",&dpeakval,"peakval/D");*/

	//Run phase - undo reset
	if(verbose){printf("Running!\n");};
	
	//Collect data
	while(!kbhit()){
		empty_q = REG_empty_GET(&empty,&handle); //check if the FIFO is empty.
		if(empty){if(false){printf("Fifo was empty this time.\n");};
		}else{
			read_q = REG_read_SET(1,&handle); // flip read on and off to retrieve data
			read_q = REG_read_SET(0,&handle);
			energy_q = REG_energy_GET(&energy, &handle);
		// t->Fill();
			fprintf(fp, "%d\n", energy);		//Save the value
			if(verbose){printf("Pulse: %d\n",energy);};
		};
	};
	//*/
	/*t->Write("",TObject::kOverwrite);
	f->Close();*/
	fclose(fp);
	clock_t end = clock();
	int elapsed = (int)((double)(end-start) / CLOCKS_PER_SEC); //total time elapsed
	int hours = floor(elapsed / 3600);
	int minutes = floor((elapsed % 3600)/60);
	int seconds = floor((elapsed % 60));
	//char* timestamp = "%d-%d-%d",hours,minutes,seconds);
	//printf(timestamp);
	printf("Time elapsed: %d:%d:%d (%d) \n",hours,minutes,seconds,elapsed);
	//char newfilename = "../../../data/" + (str)hours + "-" + (str)minutes + "-" + (str)seconds + "_t" + (str)(abs(thrs - 8192)) + "_i" + (str)inttime + "-" + (str)pre + "-" + (str)pileup + "_h" + (str)inib + "_g" + (str)gain + "-.csv";
	//rename("../../../data/out.csv",newfilename);
	return 0;
}
