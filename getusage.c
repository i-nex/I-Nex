//#include <sys/sysinfo.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/sysinfo.h>
int main() {
  int days, hours, mins;
  struct sysinfo sys_info;
  struct mallinfo sys_infoggg;
  if(sysinfo(&sys_info) != 0)
    perror("sysinfo");
  long long physMemUsed = sys_info.totalram - sys_info.freeram;
  //Multiply in next statement to avoid int overflow on right hand side...
  physMemUsed *= sys_info.mem_unit;
  long long totalVirtualMem = sys_info.totalram;
    //Add other values in next statement to avoid int overflow on right hand side...
    totalVirtualMem += sys_info.totalswap;
    totalVirtualMem *= sys_info.mem_unit;
  unsigned long total_bytes; 
  total_bytes = sys_info.mem_unit * sys_info.totalram; 
  days = sys_info.uptime / 86400;
  hours = (sys_info.uptime / 3600) - (days * 24);
  mins = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);
	
	printf("{\n");
	printf("	\"UPTIME_DAYS\": %d ,\n", days);
	printf("	\"UPTIME_HOURS\": %d ,\n", hours);
	printf("	\"UPTIME_MINUTES\": %d ,\n", mins);
	printf("	\"UPTIME_SECONDS\": %ld ,\n", sys_info.uptime % 60);
	printf("	\"LOAD_AVG_1MIN\": %ld ,\n", sys_info.loads[0]/1000);
	printf("	\"LOAD_AVG_5MIN\": %ld ,\n", sys_info.loads[1]/1000);
	printf("	\"LOAD_AVG_15MIN\": %ld ,\n", sys_info.loads[2]/1000);
	printf("	\"TOTAL_RAM\": %ld ,\n", sys_info.totalram /1024/1024);
	printf("	\"FREE_RAM\": %ld ,\n", sys_info.freeram /1024/1024);
	printf("	\"SHARED_RAM\": %ld ,\n", sys_info.sharedram /1024/1024);
	printf("	\"BUFFERED_RAM\": %ld ,\n", sys_info.bufferram /1024/1024);
	printf("	\"TOTAL_RAM_UNIT\": %llu ,\n", sys_info.totalram *(unsigned long long)sys_info.mem_unit/1024/1024);
	printf("	\"FREE_RAM_UNIT\": %llu ,\n", sys_info.freeram *(unsigned long long)sys_info.mem_unit/1024/1024);
	printf("	\"TOTAL_SWAP\": %ld ,\n", sys_info.totalswap /1024/1024);
	printf("	\"FREE_SWAP\": %ld ,\n", sys_info.freeswap /1024/1024);
	printf("	\"TOTAL_HIGH\": %ld ,\n", sys_info.totalhigh /1024/1024);
	printf("	\"FREE_HIGH\": %ld ,\n", sys_info.freehigh /1024/1024);
	printf("	\"PHYS_MEM_USED\": %llu ,\n", physMemUsed /1024/1024);
	printf("	\"TOTAL_VIRTUAL_MEM\": %llu ,\n", totalVirtualMem /1024/1024);
	printf("	\"NUMBER_OF_PROCESSES\": %d \n", sys_info.procs);
	printf("}\n");
	
	/*printf("total usable main memory is %lu B, %lu MB\n", total_bytes/1024/1024, total_bytes/1024/1024);
	printf("The number of pages of physical memory: %ld bytes\n", sysconf(_SC_PAGESIZE));
	printf("The maximum number of simultaneous processes per user ID: %ld\n", sysconf(_SC_CHILD_MAX));
	printf("The number of clock ticks per second: %ld\n", sysconf(_SC_CLK_TCK));
	printf("The number of processors currently online (available): %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
	printf("The number of processors configured: %ld\n", sysconf(_SC_NPROCESSORS_CONF));*/
  return 0;
}
