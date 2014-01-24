/* Show overall CPU utilization of the system 
 * This is a part of the post http://phoxis.org/2013/09/05/finding-overall-and-per-core-cpu-utilization
 */
#include <stdio.h>
#include <unistd.h>
 
#define BUF_MAX 1024
 
int read_fields (FILE *fp, unsigned long long int *fields)
{
  int retval;
  char buffer[BUF_MAX];
 
 
  if (!fgets (buffer, BUF_MAX, fp))
  { perror ("Error"); }
  retval = sscanf (buffer, "cpu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu", 
                            &fields[0], 
                            &fields[1], 
                            &fields[2], 
                            &fields[3], 
                            &fields[4], 
                            &fields[5], 
                            &fields[6], 
                            &fields[7], 
                            &fields[8], 
                            &fields[9]); 
  if (retval < 4) /* Atleast 4 fields is to be read */
  {
    fprintf (stderr, "Error reading /proc/stat cpu field\n");
    return 0;
  }
  return 1;
}
 
int main (void)
{
  FILE *fp;
  unsigned long long int fields[10], total_tick, total_tick_old, idle, idle_old, del_total_tick, del_idle;
  int update_cycle = 0, i, flag = 1;
  double percent_usage;
 
  fp = fopen ("/proc/stat", "r");
  if (fp == NULL)
  {
    perror ("Error");
  }
 
 
  if (!read_fields (fp, fields)) 
  { return 0; }
 
  for (i=0, total_tick = 0; i<10; i++)
  { total_tick += fields[i]; }
  idle = fields[3]; /* idle ticks index */
 
  while (flag)
  {
    sleep (1);
    total_tick_old = total_tick;
    idle_old = idle;
     
    fseek (fp, 0, SEEK_SET);
    fflush (fp);
    if (!read_fields (fp, fields))
    { return 0; }
 
    for (i=0, total_tick = 0; i<10; i++)
    { total_tick += fields[i]; }
    idle = fields[3];
 
    del_total_tick = total_tick - total_tick_old;
    del_idle = idle - idle_old;
 
    percent_usage = ((del_total_tick - del_idle) / (double) del_total_tick) * 100; /* 3 is index of idle time */
    printf ("%3.2lf\n", percent_usage);
    update_cycle++;
  }
 
 
  fclose (fp); /* Ctrl + C quit, therefore this will not be reached. We rely on the kernel to close this file */
 
  return 0;
} 
