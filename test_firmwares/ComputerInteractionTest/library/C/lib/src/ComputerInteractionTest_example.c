#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include  "ComputerInteractionTest_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"

int main(int argc, char* argv[])
{
	//Configure phase
	NI_HANDLE handle;
	int ret;
	int run;
	int strobe;
	int reset;
	int trigger;
	int peak;
	uint32_t data;
	uint32_t counter;
	uint32_t strobecount;
	uint32_t triggercount;
	uint32_t peakval;
	uint32_t lastpeak = 0;
	R_Init();

	//If can't connect to the board, abort.
	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		printf("Unable to connect to the board!\n"); return (-1); 
	};

	//Set everything to off for configuration
	run = REG_runcfg_SET(0,&handle); 
	reset = REG_reset_SET(1,&handle);
	/*
	ret = REG_integral_SET(2, &handle);
	ret = REG_integral_GET(&data, &handle);
	printf("Data: %d\n",data);
	printf("Ret : %d\n",ret);
	*/

	int testreg;
	testreg = REG_counter_GET(&counter, &handle);
	printf("counter (reset = 1): %d\n",counter);

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
	while(1){
		ret = REG_integral_GET(&data, &handle);
		testreg = REG_counter_GET(&counter, &handle);
		strobe = REG_strobecount_GET(&strobecount, &handle);
		trigger = REG_trigcount_GET(&triggercount, &handle);
		peak = REG_peak_GET(&peakval, &handle);
		if (peakval != lastpeak){
			printf("Integral: %d\n",data);
			printf("Count: %d\n",counter);
			printf("Strobe Count: %d\n",strobecount);
			printf("Trigger Count: %d\n",triggercount);
			printf("Peak: %d\n", peakval);
			lastpeak = peakval;
		}
		
	}//*/
	return 0;
}
