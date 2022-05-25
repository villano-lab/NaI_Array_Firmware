#include <stdio.h>
#include "UniversalTrigger1A_lib.h"
#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <math.h>

//Defaults
#define BOARD_IP_ADDRESS ("134.84.150.42")

//Variables
extern int verbose;
extern int thrs;
extern uint32_t value;
extern int gate_u;
extern int gate_l;
extern int polarity;
extern int inhib;
extern int delay;
extern int polarity;
//Register-reading Variables
extern NI_HANDLE handle;
extern int thrs_q;
extern int thrs_q;
extern int top_q;
extern int delay_q;
extern int gate_uq;
extern int gate_lq;
extern int inhib_q;
extern int polarity_q;
extern char* selection;
extern int *disable_q;  // point to array of disable instead of 24 initializations
extern int *disable;
extern int disable_t[24];
//Command-line-reading Variables
extern int ind;
extern int iarg;
extern const struct option longopts[];
extern char* gtemp;
extern int gateflag;
//Other Variables
extern int top;
extern time_t tic, toc;
extern FILE *fp;
extern FILE *logfile;
//Rate Counter Variables
extern int rate_q;
extern uint32_t rateval[160]; //needs to be pre-allocated
extern uint32_t ratechan;
extern uint32_t ratetimeout; //timeout in ms
extern uint32_t rateread_data;
extern uint32_t ratevalid_data;

//Functions
//===========================================================================
//printing functions
void print_usage(FILE* stream, int exit_code);      //print usage of the program
void copyright();                                   //print copyright information
//parsing functions
int parse_detector_switch(char* selection);         //parse a string representing detector on/off
int parse_gate(char* gatestring, int verbose);      //parse a string representing multiple gate values
void print_timestamp(int elapsed, int verbose);     //parse a time elapsed value and print it in readable format.
//converting functions
int *on_to_off(int *off, int on, int verbose);      //convert a detectors on bit vector to a detectors off bit vector
//other functions
int connect_staticaddr(int verbose);                //connect to the board, with print functions.
int *disable_dets(int *disable_q, int disable[24]); //disable detectors based on input array
int kbhit(void);                                    //allow keyboard interrupt