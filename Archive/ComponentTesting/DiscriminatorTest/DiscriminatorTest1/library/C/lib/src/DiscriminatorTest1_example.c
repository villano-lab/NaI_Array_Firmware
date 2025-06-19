#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include  "DiscriminatorTest1_lib.h"

#define BOARD_IP_ADDRESS "10.20.103.42"




int main(int argc, char* argv[])
{
	NI_HANDLE handle;
	int ret = 11;
	uint32_t    val;


	R_Init();


	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { printf("Unable to connect to the board!\n"); return (-1); };
#ifndef CUSTOM_EXAMPLE		
	
	

	
#else

#endif

	uint32_t *data;
        //ret=REG_counts_GET(data,&handle);
        printf("%d\n",ret);

	return 0;
}

 
