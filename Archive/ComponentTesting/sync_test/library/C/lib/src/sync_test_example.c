#include "Def.h"
#include "niusb3_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include  "sync_test_lib.h"

#define BOARD_SERIAL_NUMBER "NI120002"




int main(int argc, char* argv[])
{
	NI_HANDLE handle;
	int ret;
	uint32_t    val;


	USB3_Init();


	if(USB3_ConnectDevice(BOARD_SERIAL_NUMBER, &handle) != 0) { printf("Unable to connect to the board!\n"); return (-1); };
#ifndef CUSTOM_EXAMPLE		
	
	

	
#else

#endif

	return 0;
}

 