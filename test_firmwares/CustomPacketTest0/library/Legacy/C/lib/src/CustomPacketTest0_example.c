#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include  "CustomPacketTest0_lib.h"

int main(int argc, char* argv[])
{
	NI_HANDLE handle;
	int ret;
	uint32_t    val;


	R_Init();


	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { printf("Unable to connect to the board!\n"); return (-1); };
	printf("Connected successfully.\n");
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
	t_generic_event_collection decoded_packets;

	//Configuration flag
	int32_t FrameSync = 0;
	int32_t	FrameWait = 0;
	int32_t	FrameMask = 3;
	int32_t	FrameExternalTrigger = 0;
	int32_t	FrameOrTrigger = 1;
	
	//validation stuff
	int code;

	void *BufferDownloadHandler = NULL;
	printf("Download handler: %x\n", BufferDownloadHandler);
	code = Utility_ALLOCATE_DOWNLOAD_BUFFER(&BufferDownloadHandler, 1024*1024);
	if(code != 0){printf("Allocation failed with code %d.\n",code);}
	printf("Download handler: %x\n", BufferDownloadHandler);

	if (CPACK_CP_0_RESET(&handle) != 0) printf("Reset Error");
	if (CPACK_CP_0_START(&handle) != 0) printf("Start Error");
	if (CPACK_CP_0_STATUS(&status_frame, &handle) != 0) printf("Status Error");
	if (status_frame >0)
	{
		while (1)
		{
			//printf("looping!\n"); //debug
			valid_data_frame = 0;
			if (CPACK_CP_0_DOWNLOAD(&data_frame, N_Packet * (2), timeout_frame, &handle, &read_data_frame, &valid_data_frame) != 0) printf("Data Download Error");
			
			valid_data_enqueued = 0;
			if(Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER(BufferDownloadHandler, data_frame, valid_data_frame, &valid_data_enqueued) != 0) printf("Data enqueue failure.\n");

			code = CPACK_CP_0_RECONSTRUCT_DATA(BufferDownloadHandler, &decoded_packets, 1);
			if (code == 0)
			{
				printf(".");
				for (int i =0;i<decoded_packets.valid_packets;i++){
				    t_CP_0_struct *data = decoded_packets.packets[i].payload;
				    printf("%d\n", data->row[0]);
				}
				free_packet_collection(&decoded_packets);
			}
			else{
				printf("Data reconstruction returned %d.\n",code);
			}
			ReadDataNumber = ReadDataNumber+ N_Packet;
	}
		printf("Download completed");
	}
	else printf("Status Error");

//*/


	
#else

#endif

	return 0;
}

 