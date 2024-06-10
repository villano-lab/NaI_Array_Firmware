#include <stdio.h>
#include "Legacy/Def.h"
#include "Legacy/circular_buffer.h"
#include "/home/rune/packages/SCIDK-SDKLinux/libSCIDK/include/ftd2xx.h"

#include "UniversalTriggerShared.h"
//#include "Legacy/R76Replica_lib.h"

int main(){
	SciSDK* sdk = new SciSDK;
	DWORD lpdwAmountInRxQueue,lpdwAmountInTxQueue,lpdwEventStatus;

	std::cout << Devices[(NI_HANDLE*)sdk].valid << std::endl;

	int status = FT_GetStatus((NI_HANDLE*)sdk,&lpdwAmountInRxQueue,&lpdwAmountInTxQueue,&lpdwEventStatus);
	if(status!= FT_OK){
		printf("FT_GetStatus did not return FT_OK.\n");
		return(status);
	}

	return(lpdwEventStatus);
}
