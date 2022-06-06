#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "SCIDK_Lib.h"

#include  "compile_sw_lib.h"

#define BOARD_SERIAL_NUMBER "10500"




int main(int argc, char* argv[])
{
	NI_HANDLE handle;
	int ret;
	uint32_t    val;

	if(USB2_ConnectDevice(BOARD_SERIAL_NUMBER, &handle) != 0) { printf("Unable to connect to the board!\n"); return (-1); };
#ifndef CUSTOM_EXAMPLE		
	
	while (1) {
		uint32_t r1, r2;
		r1 = 0;
		r2 = 0;
		REG_AN_IN_GET(&r1, &handle);
		REG_CNTR_GET(&r2, &handle);
		printf("Analog value: %8d    Timer: %16x\n", r1, r2);
		sleep(1000);
	}

	
#else

#endif

	return 0;
}

 
