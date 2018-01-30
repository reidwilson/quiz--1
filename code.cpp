#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
using namespace std;
int
main (int argc, char *argv[])
{
  // assume argc  is 2 with second arg being the number

  int exitStatus;		// status returned by the child
  int pid;			// ID of created process
  char pid_argument[32];	// used to create command line
  if (argc != 2)
    {
      std::cout << "usage: " << argv[0] << " <positive number>" << endl;
      return -1;
    }
  int num = atoi (argv[1]);
  int temp = num;		// temp value
  printf ("number %d\n",temp);
  int sum = num;		// start with ourselves as the sum value
  while (temp > 0)
    {
      // assume no errors in any system call
      pid = fork ();
      if (pid == 0)
	{
	  // create an argument
	  sprintf (pid_argument, "%d", temp - 1);
	  execl ("./silly",	// path of the program to load
		 "silly",	// will show up in argv[0]
		 pid_argument,	// will show up in argv[1] 
		 NULL);		// terminate the arg list
          exit(0);
	}
      else
	{
	  // don't forget to decrement temp we will be in an infinite loop
	  temp = temp - 1;
	  wait (&exitStatus);
	  sum += WEXITSTATUS (exitStatus);
	}			// if condition
    }				// end of while
  cout << "Process: " << getpid () << " with num = " << num
    << ", computed sum = " << sum << endl;
  exit (sum);
  return 0;
}
