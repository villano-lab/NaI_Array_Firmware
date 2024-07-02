//standard includes -- these should be fine.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <getopt.h>
//non-standard includes
#include "UT1AReplica_lib.h"
#include "../../../../../SCIDK-SDKLinux/libSCIDK/include/SCIDK_API_C.h"
#include "SCIDK_Lib.h"
//defines
#define BOARD_SERIAL_NUMBER "13251"

// Variables
// ======================================================================
int ret;
uint32_t    val;
int verbose = 0;
//Registers
NI_HANDLE handle;
int thrs_q;
int top_q;
int delay_q;
int gate_uq;
int gate_lq;
int inhib_q;
int polarity_q;
char* selection;
uint32_t value;
int disable_q[2]; // array of disable_q instead of 24 initializations
int disable[2];
time_t tic, toc;
const char* program_name = "scanwindow";
FILE *fp;
FILE *logfile;

// Functions
// ======================================================================
const struct option longopts[] =
{
	{"gate",	required_argument,	0,	'g'},
	{"help",	no_argument,		0,	'h'},
	{"log",		optional_argument,	0,	'l'},
	{"quiet",	no_argument,		0,	'q'},
	{"silent",	no_argument,		0,	's'},
	{"verbose",	optional_argument,	0,	'v'},
	{"version",	no_argument,		0,	'V'},
	{"det",		required_argument,	0,	'd'},
	{"thresh",	required_argument,	0,	't'},
	{0,		0,			0,	0},
};

void print_usage(FILE* stream, int exit_code){ //This looks unaligned but lines up correctly in the terminal output
	fprintf (stream, "Usage:  %s options \n", program_name);
  	fprintf (stream,
	" -d,	--det	<# or source name>	Choose which detectors to trigger on (default: all).\n"
	"					Number values are bitwise from 0 to all 1s in 2-bit (3).\n"
	" -t,	--thresh	<threshold>		Set the value of the threshold (default: 4192). \n"
	" -g,	--gate	'<lower #> <upper #>'	Set the gate times for the upper and lower triggers in arbitrary(?) time units (integer. defaults: 1-100)\n"
	"					The two entries are delimited by spaces, commas, or dashes. Both must be provided.\n"
	" -v,	--verbose	<level>		Print verbose messages at the specified level (1 if unspecified).\n"
	" -s,-q,	--silent,--quiet,		Print nothing.\n"
	" -l,	--log		<file>		Log terminal output.\n"
	" -V, 	--version			Print version and exit.\n"
	" -h,-?,	--help				Print this help function.\n"
);
  exit (exit_code);
};

int kbhit(void)
        {
          struct termios oldt, newt;
          int ch;
          int oldf;

          tcgetattr(STDIN_FILENO, &oldt);
          newt = oldt;
          newt.c_lflag &= ~(ICANON | ECHO);
          tcsetattr(STDIN_FILENO, TCSANOW, &newt);
          oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
          fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

          ch = getchar();

          tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
          fcntl(STDIN_FILENO, F_SETFL, oldf);

          if(ch != EOF)
          {
            ungetc(ch, stdin);
            return 1;
          }

          return 0;
        }

//dummy main func
int main(){
	printf("Got to main function.\n");
}