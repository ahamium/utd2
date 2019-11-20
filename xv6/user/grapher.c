/* pxc180001
 *
 * this file monitors two prcesses and records their number of ticks every so and so intervals
 *
 * */
#include "types.h"
#include "fcntl.h"
#include "user.h"
#include "pstat.h"

const int SAMP_PERIOD = 75;
const int SAMP_WINDOW = 2000;

const int GRAPHER_PRIORITY = 1000;
const char*const OUTPUT_FILE = "graph.csv";

int main(int argc, char** argv){
	settickets(GRAPHER_PRIORITY);
	const int PROCESS_QUANTITY = argc - 1;

	int processes[PROCESS_QUANTITY];
	for(int i=0;i<PROCESS_QUANTITY;i++)
		processes[i] = atoi(argv[i+1]);
	
	struct pstat pinfo = {0};
	if(0 > getpinfo(&pinfo)){
		printf(stderr, "getpinfo() failed\n");
		exit();
	}

	int fp = stdout;

	printf(fp, "time, ");
	for(int i=0;i<PROCESS_QUANTITY;i++){
		printf(fp, "%d, ", processes[i]);
	}
	write(fp, "\n", 1);

	int pindices[PROCESS_QUANTITY];
	for(int index = 0;index<NPROC;index++){
		for(int i=0;i<PROCESS_QUANTITY;i++){
			if(pinfo.pid[index] == processes[i]){
				pindices[i] = index;
			}
		}
	}
	
	int time_passed = 0;
	while(1){
	
		getpinfo(&pinfo);
		printf(fp, "%d, ", uptime());

		for(int i=0;i<PROCESS_QUANTITY;i++){
			printf(fp, "%d, ", pinfo.ticks[pindices[i]]);
		}
		write(fp, "\n", 1);

		if(time_passed >= SAMP_WINDOW)	
			break;
		
		sleep(SAMP_PERIOD);
		time_passed+=SAMP_PERIOD;
	}

	close(fp);
	exit();
}
