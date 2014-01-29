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
#include <sys/utsname.h> 

int main() {
  struct utsname inex_uname;

  if(uname(&inex_uname) == -1)
    printf("{\n"
	   "	\"Failed\": \"uname_call_failed\""
	   "}\n");
  else
    printf("{\n"
	   "	\"System_name\": \"%s\",\n" 	/* Operating system name (e.g., "Linux") */
	   "	\"Nodename\": \"%s\",\n"	/* Name within "some implementation-defined network" */
	   "	\"Release\": \"%s\",\n"		/* OS release (e.g., "2.6.28") */
	   "	\"Version\": \"%s\",\n"		/* OS version */
	   "	\"Machine\": \"%s\"\n"		/* Hardware identifier */
	   "}\n",
	   inex_uname.sysname, 
	   inex_uname.nodename, 
	   inex_uname.release,
	   inex_uname.version,
	   inex_uname.machine);
    
  return 0;
}