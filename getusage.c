#include <sys/sysinfo.h>
#include <stdio.h>

int main() {
  int days, hours, mins;
  struct sysinfo sys_info;
  if(sysinfo(&sys_info) != 0)
    perror("sysinfo");

  days = sys_info.uptime / 86400;
  hours = (sys_info.uptime / 3600) - (days * 24);
  mins = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);
	
	printf("{\n");														//
	printf("	\"UPTIME_DAYS\": %d ,\n", days);									//
	printf("	\"UPTIME_HOURS\": %d ,\n", hours);									//
	printf("	\"UPTIME_MINUTES\": %d ,\n", mins);									//
	printf("	\"UPTIME_SECONDS\": %ld ,\n", sys_info.uptime % 60);							//
	printf("	\"LOAD_AVG_1MIN\": %ld ,\n", sys_info.loads[0]);							//
	printf("	\"LOAD_AVG_5MIN\": %ld ,\n", sys_info.loads[1]);							//
	printf("	\"LOAD_AVG_15MIN\": %ld ,\n", sys_info.loads[2]);							//
	printf("	\"TOTAL_RAM\": %ld ,\n", sys_info.totalram / 1024);							//
	printf("	\"FREE_RAM\": %ld ,\n", sys_info.freeram / 1024);							//
	printf("	\"SHARED_RAM\": %ld ,\n", sys_info.sharedram / 1024);							//
	printf("	\"BUFFERED_RAM\": %ld ,\n", sys_info.bufferram / 1024);							//
	printf("	\"TOTAL_RAM_UNIT\": %llu ,\n", sys_info.totalram *(unsigned long long)sys_info.mem_unit / 1024);	//
	printf("	\"FREE_RAM_UNIT\": %llu ,\n", sys_info.freeram *(unsigned long long)sys_info.mem_unit/ 1024);		//
	printf("	\"TOTAL_SWAP\": %ld ,\n", sys_info.totalswap / 1024);							//
	printf("	\"FREE_SWAP\": %ld ,\n", sys_info.freeswap / 1024);          						//
	printf("	\"TOTAL_HIGH\": %ld ,\n", sys_info.totalhigh / 1024);							//
	printf("	\"NUMBER_OF_PROCESSES\": %d \n", sys_info.procs);							//
	printf("}\n");														//
	
  return 0;
}