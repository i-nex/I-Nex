/* Copyright(C) 2014, Michał Głowienka aka eloaders <eloaders@linux.pl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <glibtop.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>
#include <glibtop/proclist.h>
#include <glibtop/swap.h>
get_cpu(glibtop_cpu *cpustruct) {
    glibtop_get_cpu(cpustruct);
    return 100 - (float)cpustruct->idle / (float)cpustruct->total * 100;
}
int main() {
    glibtop_init();
    glibtop_cpu cpu;
    glibtop_mem memory;
    glibtop_swap swap;
    glibtop_proclist proclist;
    glibtop_get_cpu (&cpu);
    glibtop_get_mem(&memory);
    glibtop_cpu cpustruct;
    
    struct sysinfo sys_info;
    
    long long physMemUsed = sys_info.totalram - sys_info.freeram;
    long long totalVirtualMem = sys_info.totalram;
    unsigned long total_bytes; 
    unsigned int sleepfor = 5000;
    int days, hours, mins;
    float usagess; 

        usagess = get_cpu(&cpustruct);
  
    if(sysinfo(&sys_info) != 0)
	perror("sysinfo");
    
    physMemUsed *= sys_info.mem_unit;
    totalVirtualMem += sys_info.totalswap;
    totalVirtualMem *= sys_info.mem_unit;
    total_bytes = sys_info.mem_unit * sys_info.totalram; 
  
    days = sys_info.uptime / 86400;
    hours = (sys_info.uptime / 3600) - (days * 24);
    mins = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);

	printf("{\n");
	printf("	\"CPU_TOTAL\": %ld ,\n", (unsigned long)cpu.total);
	printf("	\"CPU_USER\": %ld ,\n", (unsigned long)cpu.user);
	printf("	\"CPU_NICE\": %ld ,\n", (unsigned long)cpu.nice);
	printf("	\"CPU_SYS\": %ld ,\n", (unsigned long)cpu.sys);
	printf("	\"CPU_IDLE\": %ld ,\n", (unsigned long)cpu.idle);
	printf("	\"CPU_FREQUENCES\": %ld ,\n", (unsigned long)cpu.frequency);
	printf("	\"CPU_USEGE\": %.2f ,\n", usagess);
	printf("	\"MEMORY_TOTAL\": %ld ,\n", (unsigned long)memory.total/(1024*1024));
	printf("	\"MEMORY_USED\": %ld ,\n", (unsigned long)memory.used/(1024*1024));
	printf("	\"MEMORY_FREE\": %ld ,\n", (unsigned long)memory.free/(1024*1024));
	printf("	\"MEMORY_SHARED\": %ld ,\n", (unsigned long)memory.shared/(1024*1024));
	printf("	\"MEMORY_BUFFERED\": %ld ,\n", (unsigned long)memory.buffer/(1024*1024));
	printf("	\"MEMORY_CACHED\": %ld ,\n", (unsigned long)memory.cached/(1024*1024));
	printf("	\"MEMORY_USER\": %ld ,\n", (unsigned long)memory.user/(1024*1024));
	printf("	\"MEMORY_LOCKED\": %ld ,\n", (unsigned long)memory.locked/(1024*1024));
	printf("	\"SWAP_TOTAL\": %ld ,\n", (unsigned long)swap.total);		/* GLIBTOP_SWAP_TOTAL   */
	printf("	\"SWAP_USED\": %ld ,\n", (unsigned long)swap.used);		/* GLIBTOP_SWAP_USED    */
	printf("	\"SWAP_FREE\": %ld ,\n", (unsigned long)swap.free);		/* GLIBTOP_SWAP_FREE    */
	printf("	\"SWAP_PAGEIN\": %ld ,\n", (unsigned long)swap.pagein);		/* GLIBTOP_SWAP_PAGEIN  */
	printf("	\"SWAP_PAGEOUT\": %ld ,\n", (unsigned long)swap.pageout);	/* GLIBTOP_SWAP_PAGEOUT */
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
  glibtop_close();
  return 0;
}
