#include "Legacy/Def.h"
#include "Legacy/circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
//#include "/home/rune/packages/SCIDK-SDKLinux/libSCIDK/include/ftd2xx.h"

//#include "Legacy/R76Firmware_lib.h"
#include "UniversalTriggerShared.h"

const char* program_name = "packettest";
int waittime=100; //default num SETS of packets.

void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage:  %s options \n", program_name);
	fprintf (stream, VERBOSE_TEXT);
	fprintf (stream, SILENT_TEXT);
	fprintf (stream, LOG_TEXT);
	fprintf (stream, VERSION_TEXT);
	fprintf (stream, HELP_TEXT);
	fprintf (stream, "-w,    --wait  <#> Set the number of packets to wait to collect before exiting. (integer. if not supplied, waits for 100 packets.)\n");
	exit (exit_code);
};

int packet_setup(NI_HANDLE handle,int verbose){
	return(1); //this function doesn't do anything so I want it to cause problems if you use it.
}

int main(int argc, char* argv[])
{
	SciSDK* sdk = new SciSDK;
	//Read options
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "l::sh?v::Vw:q", longopts, &ind);
		switch (iarg){
		case 'h':
			print_usage(stdout,0);
			return 0;
			break;
		case 'q':
			verbose = -1;
			break;
		case 's':
			verbose = -1;
			break;
		case 'v':
			if(optarg){
				verbose = atoi(optarg);
			}else{verbose = 1;};
			break;
		case '?':
			print_usage(stdout,0);
			return 0;
			break;
		case 'V':
			printf("Get Spectrum\n");
			copyright();
			return 0;
			break;
		case 'l':
			if(optarg){
				logfile = fopen(optarg,"w");
			}else{
				logfile = fopen("log.txt","w");
			};
			break;
        case 'w':
            waittime = atoi(optarg);
            break;
		}
	}

	//Verbosity message
	if(verbose > 0){
		printf("Running in verbose mode. Verbosity: %d\n",verbose);
	};

	//Connect to the board.
        int connect_q = SCIDK_ConnectUSB(BOARD_SERIAL_NUMBER,(NI_HANDLE*)sdk);
	if(connect_q != 0){
		printf("Board connection error code: %d\n",connect_q);
		return connect_q;
	}

	//Stuff to call later
	uint32_t status_frame = 0;
	uint32_t N_Packet = 2; //seems to be minimal functional amount.
	int32_t data_frame[100000];
	uint32_t read_data_frame;
	uint32_t valid_data_frame;
	uint32_t valid_data_enqueued;
	uint32_t N_Total_Events = 10000;
	uint32_t ReadDataNumber = 0;
	int32_t timeout_frame = 1000;
	t_generic_event_collection decoded_packets;
	void *BufferDownloadHandler = NULL;
	//Configuration flag
	int32_t FrameSync = 0;
	int32_t	FrameWait = 0;
	int32_t	FrameMask = 3;
	int32_t	FrameExternalTrigger = 0;
	int32_t	FrameOrTrigger = 1;
	//exit codes for sub-whatevers.
	int code;
	//run time length troubleshooting
	struct timeval start,allocate,stop;

	//Allocate the buffer.
	code = Utility_ALLOCATE_DOWNLOAD_BUFFER(&BufferDownloadHandler, 1024*1024);
	if(verbose>1) printf("BufferDownloadHandler: %p.\n",BufferDownloadHandler);
	if(code != 0){
		printf("Buffer allocation failed.\n");
		return code;
	}
	if(verbose>1) printf("Buffer allocation succeeded. Continuing to setup.\n");

	//debug mode for matching.
	int debug = 1; //i am too lazy to make another cl arg
	if(debug){
		printf("Debugging!\n");
		__abstracted_reg_write(3,SCI_REG_diag_debug,(NI_HANDLE*)sdk);
		__abstracted_reg_write(3,SCI_REG_diag_trigtype,(NI_HANDLE*)sdk);
		waittime = 1;
		N_Packet = 10;
		__abstracted_reg_write(0,SCI_REG_forcetrig,(NI_HANDLE*)sdk); //need to know where we're starting before we can proceed.
	}
	else{ //make sure it's set back to normal.
		__abstracted_reg_write(0,SCI_REG_diag_debug,(NI_HANDLE*)sdk);
	}

	//Pull the data!
	if (CPACK_All_Energies_FLUSH((NI_HANDLE*)sdk) != 0) printf("Flush Error\n");
	if (CPACK_All_Energies_RESET((NI_HANDLE*)sdk) != 0) printf("Reset Error\n");
	if (CPACK_All_Energies_START((NI_HANDLE*)sdk) != 0) printf("Start Error\n");
	if (CPACK_All_Energies_STATUS(&status_frame, (NI_HANDLE*)sdk) != 0) printf("Status Error\n");
	if(verbose>1){
		printf("Setup complete. Packet status %d (",status_frame);
		if(status_frame & (1 << 0)){printf("Data available, ");
		}else{printf("No data available, ");}
		if(status_frame & (1 << 1)){printf("Running, ");
		}else{printf("Not running, ");}
		if(status_frame & (1 << 2)){printf("Full.)\n");
		}else{printf("Not full.)\n");}
	}
	if (status_frame >0)
	{
		if(verbose>1) printf("Logging to %s.\n",logfile);
        if(logfile != NULL){
            fprintf(logfile,"trigger code,timestamp,CH00,CH01\n");
        }

	/*DWORD lpdwAmountInRxQueue,lpdwAmountInTxQueue,lpdwEventStatus;
	FT_GetStatus((NI_HANDLE*)sdk, &lpdwAmountInRxQueue,&lpdwAmountInTxQueue,
                          &lpdwEventStatus);*/

	//if debugging matching, generate 10 values
	if(debug){
		int k = 0;
		while(k<5){
			std::cout << "Generating manual triggers... " << k << std::endl;
			if(__abstracted_reg_write(1,SCI_REG_forcetrig,(NI_HANDLE*)sdk)) return -1;
			sleep(1);
			if(__abstracted_reg_write(0,SCI_REG_forcetrig,(NI_HANDLE*)sdk)) return -1;
			k++;
		}
	}
        int j = 0;
        while(j<waittime){
		//REG_reset_SET(0,(NI_HANDLE*)sdk);REG_reset_SET(1,(NI_HANDLE*)sdk);*/
		gettimeofday(&start,NULL);
		valid_data_frame = 0;
		if(verbose > 0){printf("Downloading new dataset.\n");}
		if(CPACK_All_Energies_DOWNLOAD((uint32_t *)data_frame, N_Packet * (4), timeout_frame, (NI_HANDLE*)sdk, &read_data_frame, &valid_data_frame) != 0) printf("Data Download Error\n");
		if(verbose>0) std::cout << "Valid data: " << valid_data_frame << ", " << (valid_data_frame == 0) << std::endl;//printf("Valid data: %d.\n",valid_data_frame);
		if(valid_data_frame == 0){
			printf("No data available; nothing to do. Exiting.");
			return -1;
		}

		valid_data_enqueued = 0;
		if(verbose > 1){printf("Enqueuing data.\n");}
		code = Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER(BufferDownloadHandler, data_frame, valid_data_frame, &valid_data_enqueued);
		if(code != 0){
			printf("Enqueue failed with code %d.\n",code);
			return code;
		}

            if(verbose > 1){printf("Reconstructing data.\n");}
            if (CPACK_All_Energies_RECONSTRUCT_DATA(BufferDownloadHandler, &decoded_packets) == 0)
//, verbose, handle) == 0) //these args were added in, not ready to include yet.
            {
                if(verbose>=0) printf(".");
                if(verbose>=0) printf("\n");
                if(verbose>2) printf("i: %d\n",i);
		if(verbose>2) printf("BufferDownloadHandler: %p\n",BufferDownloadHandler);
		if(decoded_packets.valid_packets == 0){
			printf("No more valid packets; done.\n");
			return 0;
		}
                if(verbose>1) printf("Valid Packets: %d \n",decoded_packets.valid_packets);
                for (int i = 0;i<decoded_packets.valid_packets;i++){
                    if(verbose>2){printf("Reading out decoded packet...\n");}
                    t_All_Energies_struct *data = (t_All_Energies_struct *)decoded_packets.packets[i].payload;
		    //Gate width debugging
                    for(int n=0;n<3;n++){
                        //For now I'm abusing my log function in order to print to file.
                        if(logfile != NULL){
                            if(n==0){ //trigger code
                                fprintf(logfile,"%08X,",data->row[n]);
                            }else if(n==1){ //timestamp
                                fprintf(logfile,"%04X,",data->row[n]>>16);
                            }else{ //data
                                uint16_t lower_word = (uint16_t) (data->row[n] & 0xFFFFUL);
                                uint16_t upper_word = (uint16_t) ((data->row[n] >> 16) & 0xFFFFUL);
                                fprintf(logfile,"%04X,%04X\n",(uint32_t)lower_word,(uint32_t)upper_word); //1.5 lines off.
                            }
                        }
                        if(verbose > -1){printf("Row #%02d",n+1);}
                        if(verbose > -1 && n > 13){printf(" (No input)");} //append a note that these channels are unused.
                        if(verbose > -1){printf(": %08x\n", data->row[n]);}
                    }
                if(verbose > 1){
                    uint32_t trig_value;
                    if(verbose > 2){printf("%p\n",(NI_HANDLE*)sdk);}
                    /*code = REG_trigger_code_GET(&trig_value,(NI_HANDLE*)sdk);
                    if(code != 0){
                        printf("Retrieving trigger_code failed!\n");
                    }else{
                        printf("Trigger code (NOT retrieved at same time as packet!): %06x\n",trig_value);
                    }*/ //trigger code issues resolved and register deprecated.
                }
                if(verbose > -1){printf("=====\n");}
                }
                if(verbose>2){printf("Freeing packets... (Is that what this line even does?)\n");}
                //free_packet_collection(&decoded_packets); //this is broken, that's not good.
            }else{
                printf("Reconstruction failed.\n");
                return -1;
            }
            if(verbose > 2){printf("Incrementing ReadDataNumber.\n");}
            ReadDataNumber = ReadDataNumber + N_Packet;
            j++;
			gettimeofday(&stop,NULL);
			printf ("Elapsed this iteration: %f\n",stop.tv_sec-start.tv_sec
	          + 0.000001*(stop.tv_usec-start.tv_usec));
        }
		if(verbose >-1){printf("Download completed\n");}
	}
	else printf("Status Error");
    return 0;
}

/* STATUS:
Right now if I run `./packettest -q -w1` it takes about 1 second. I need it to be faster.
- flag `-Ofast` did not have a noticeable impact.

Something I am wondering: Am I getting the integration values at the right time?
I think that I should be waiting until the energy data from the charge integrator
is valid/ready, but this will exacerbate the issues with the trigger information,
so I want to troubleshoot that first.
*/
