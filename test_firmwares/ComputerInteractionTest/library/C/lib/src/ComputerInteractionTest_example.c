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
	uint32_t    val;


	R_Init();


	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { 
		printf("Unable to connect to the board!\n"); return (-1); 
	};

	int run;
	uint32_t data = 2;
	run = REG_runcfg_SET(0,&handle); 

	ret = REG_integral_GET(&data, &handle);
	printf("Data (config): %d\n",data);
	printf("Ret          : %d\n",ret);
	
	/*
	ret = REG_integral_SET(2, &handle);
	ret = REG_integral_GET(&data, &handle);
	printf("Data: %d\n",data);
	printf("Ret : %d\n",ret);
	*/

	//Run phase
	run = REG_runcfg_SET(1,&handle); 
	printf("Run       :%d\n",run);
	ret = REG_integral_GET(&data, &handle);
	printf("Data (run): %d\n",data);
	printf("Ret       : %d\n",ret);

	/*//While loop for checking for flukes
	while(1){
		ret = REG_integral_GET(&data, &handle);
		printf("%d ",ret);
		printf("%d\n",data);
	}//*/
	return 0;
}
