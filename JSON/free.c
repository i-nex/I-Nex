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

#include <proc/sysinfo.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/sysinfo.h>
#include <stdio.h>

int main() {
	
		meminfo();
		struct sysinfo sys_info;
    
		long long physMemUsed = sys_info.totalram - sys_info.freeram;
		long long totalVirtualMem = sys_info.totalram;
		unsigned long total_bytes; 
		unsigned int sleepfor = 5000;
		int days, hours, mins;
  
		if(sysinfo(&sys_info) != 0)
		    perror("sysinfo");
    
		physMemUsed *= sys_info.mem_unit;
		totalVirtualMem += sys_info.totalswap;
		totalVirtualMem *= sys_info.mem_unit;
		total_bytes = sys_info.mem_unit * sys_info.totalram; 
  
		days = sys_info.uptime / 86400;
		hours = (sys_info.uptime / 3600) - (days * 24);
		mins = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);
		/* Translation Hint: You can use 9 character words in
		 * the header, and the words need to be right align to
		 * beginning of a number. */
		//printf("%s\n", _("             total       used       free     shared    buffers     cached"));
		//printf("%-7s", _("Mem:"));
		unsigned KLONG buffers_plus_cached = kb_main_buffers + kb_main_cached;
		printf("{\n");
		printf("	\"MEMORY_TOTAL\": %ld ,\n", kb_main_total/1024);
		printf("	\"MEMORY_USED\": %ld ,\n", kb_main_used/1024);
		printf("	\"MEMORY_FREE\": %ld ,\n", kb_main_free/1024);
		printf("	\"MEMORY_SHARED\": %ld ,\n", kb_main_shared/1024);
		printf("	\"MEMORY_BUFFERS\": %ld ,\n", kb_main_buffers/1024);
		printf("	\"MEMORY_CACHED\": %ld ,\n", kb_main_cached/1024);
		printf("			\"OTH\": {\n");			
		printf("			\"LOW\": {\n");
		printf("				\"TOTAL\": %ld ,\n", kb_low_total/1024);
		printf("				\"USED\": %ld ,\n", (kb_low_total - kb_low_free)/1024);
		printf("				\"FREE\": %ld \n", kb_low_free/1024);
		printf("			},\n");
		printf("			\"HIGH\": {\n");
		printf("				\"TOTAL\": %ld ,\n", kb_high_total/1024);
		printf("				\"USED\": %ld ,\n", (kb_high_total - kb_high_free)/1024);
		printf("				\"FREE\": %ld \n", kb_high_free/1024);
		printf("			}\n");
		printf("	},\n");
		printf("	\"USED_PLUS_CACHED\": %ld ,\n", (kb_main_used - buffers_plus_cached)/1024);
		printf("	\"FREE_PLUS_CACHED\": %ld ,\n", (kb_main_free + buffers_plus_cached)/1024);
		printf("			\"TOTAL\": {\n");			
		printf("			\"TOTAL\": {\n");
		printf("				\"TOTAL\": %ld ,\n", (kb_main_total + kb_swap_total)/1024);
		printf("				\"USED\": %ld ,\n", (kb_main_used + kb_swap_used)/1024);
		printf("				\"FREE\": %ld \n", (kb_main_free + kb_swap_free)/1024);
		printf("			}\n");
		printf("	},\n");
		printf("	\"SWAP_TOTAL\": %ld ,\n", kb_swap_total/1024);
		printf("	\"SWAP_USED\": %ld ,\n", kb_swap_used/1024);
		printf("	\"SWAP_FREE\": %ld ,\n", kb_swap_free/1024);
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

	return 0;
}
