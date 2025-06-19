#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include  "FifoDemo_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"




int main(int argc, char* argv[])
{
	NI_HANDLE handle;
	int ret;
	uint32_t    val;


	R_Init();


	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { printf("Unable to connect to the board!\n"); return (-1); };
	printf("Connection successful.\n");
#ifndef CUSTOM_EXAMPLE		
	
	 //REMOVE THIS COMMENT TO ENABLE THE EXAMPLE CODE

	uint32_t status_frame = 0;
	uint32_t N_Packet = 100;
	uint32_t data_frame[100000];
	uint32_t read_data_frame;
	uint32_t valid_data_frame;
	uint32_t valid_data_enqueued;

	uint32_t N_Total_Events = 10000;
	uint32_t ReadDataNumber = 0;
	int32_t timeout_frame = 1000;
	t_FRAME_packet_collection decoded_packets;

	//Configuration flag
	int32_t FrameSync = 0;
	int32_t	FrameWait = 0;
	int32_t	FrameMask = 3;
	int32_t	FrameExternalTrigger = 0;
	int32_t	FrameOrTrigger = 1;
	//exit codes for sub-whatevers.
	int code;

	void *BufferDownloadHandler = NULL;

	//Create the circular buffer where download raw data
	//printf("Should be null: %x\n",BufferDownloadHandler);
	code = Utility_ALLOCATE_DOWNLOAD_BUFFER(&BufferDownloadHandler, 1024*1024);
	printf("BufferDownloadHandler: %x.\n",BufferDownloadHandler);
	if(code != 0){printf("Buffer allocation failed.\n");}
	/*printf("Buffer allocation exited with code %d\n",code);
	printf("Should no longer be null: %x\n",BufferDownloadHandler);//*/

	//Startup the Custom Packet acquisition
	if (CPACK_CP_0_RESET(&handle) != 0) printf("Reset Error");
	if (CPACK_CP_0_START(&handle) != 0) printf("Start Error");

	//chec if is ready
	if (CPACK_CP_0_STATUS(&status_frame, &handle) != 0) printf("Status Error");
	if (status_frame >0)
	{
		//Forever download
		while (1)
		{
			valid_data_frame = 0;

			//Download N_packet raw data. There is no guarantee that the data 
			//are packet aligned. The circular buffer make continuty 
			//between consecutive acquisition 
			if (CPACK_CP_0_DOWNLOAD(&data_frame, 
				N_Packet * 3, 
				timeout_frame, 
				&handle, 
				&read_data_frame, 
				&valid_data_frame) != 0) printf("Data Download Error");
			
			//Push data in the circular buffer
			valid_data_enqueued = 0;
			//printf("BufferDownloadHandler: %x\n",BufferDownloadHandler);
			Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER(BufferDownloadHandler, 
				data_frame, 
				valid_data_frame, 
				&valid_data_enqueued);

			//Pull data from circular buffer and recostruct events
			if (CPACK_CP_0_RECONSTRUCT_DATA(BufferDownloadHandler,
				&decoded_packets) == 0)
			{
				//There are new events in the buffer and they are
				//successfully decoded
				//printf(".");
				// .... do stuff with your data
				printf("Allocated:\t %d\n",decoded_packets.allocated_packets);
				printf("Valid_Packets:\t %d\n",decoded_packets.valid_packets);
				printf("Valid:\t\t %u\n",decoded_packets.packets->Valid);
				printf("Timecode:\t %u\n",decoded_packets.packets->Time_Code);
				for(int i=0;i<10;i++){
					printf("Data.channel[%d]: %u\n",i,(unsigned int)decoded_packets.packets[i].data->ch);
					printf("Data.analog[%d]:\t %u\n",i,(unsigned int)decoded_packets.packets[i].data->analog);
				}
				printf("=============\n");
				sleep(2);
				//Free data. //Call now!
				free_FRAME_packet_collection(&decoded_packets);
			}else{printf("CPACK_CP_0_RECONSTRUCT_DATA failed.\n");} 

			ReadDataNumber = ReadDataNumber+ N_Packet;
	}
		printf("Download completed");
	}
	else printf("Status Error");




	
#else

#endif

	return 0;
}

 
