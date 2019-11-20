/*
 *pxc180001
 *for running unit tests
 *
 * */

#include "types.h"
#include "pstat.h"
#include "user.h"

int ps(){

struct pstat pinfo = {0};
if(-1 == getpinfo(&pinfo)){
return 0;
printf(1, "\n\t FAILURE\n");
}
const int current_pid = getpid();
	
	int total_ticks = 0;
		
		int current_entry = 0;
		for(int i=0;i<NPROC;i++)
		{
		if(pinfo.pid[i] == current_pid)
		{
		current_entry = i;
		}else if(pinfo.state[i] != SLEEPING)
		{
		total_ticks += pinfo.ticks[i];
		}
		}

	        printf(stdout,"This process: %d\n",
		getpid());
		printf(stdout,"Total tickets: %d\n\n",
		pinfo.total_tickets);
		printf(stdout,
		"PID\tTicks\tTickets\tState\tE%\tA%\n");
		for(int i=0;i<NPROC;i++){
		if(pinfo.pid[i]==0)continue;
		_Bool skip_yield = 0;
		float expected_yield =100*(float)pinfo.tickets[i]/((float)pinfo.total_tickets - pinfo.tickets[current_entry]);
		float actual_yield =100*(float)pinfo.ticks[i]/(float)total_ticks;

		if(pinfo.state[i] == 2 || pinfo.pid[i] == current_pid)
		{
		skip_yield = 1;
		}
		int ey_left =
		(int)expected_yield;
		int ey_right =
		(int)((expected_yield-ey_left)*10);
		int ay_left =
		(int)actual_yield;
		int ay_right =
		(int)((actual_yield-ay_left)*10);

		if(pinfo.inuse[i])
		putchar('>');
		else
		putchar('|');

		printf(stdout, 
		skip_yield?
		"%d\t%d\t%d\t%d\t-\t-\n":
		"%d\t%d\t%d\t%d\t%d.%d\t%d.%d\n", 
		pinfo.pid[i],
		pinfo.ticks[i],
		pinfo.tickets[i],
		pinfo.state[i],
		ey_left,
		ey_right,
		ay_left,
		ay_right
		);
		}
		return 1;
		}

		int main(int argc, char *argv[])
		{
		ps();
		exit();
		}
