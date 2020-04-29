/*Here is a method to avoid the process from becoming Zombie. The cleanup is done by using signal handler */


#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

sig_atomic_t child_exit_status;
void clean_up_child_process (int signal_number)
{
  /* Clean up the child process. */
  int status;
  wait (&status);

  /* Store its exit status in a global variable. */
  child_exit_status = status;
}

int main ()
{
  pid_t child_pid;

  /* Handle SIGCHLD by calling clean_up_child_process. */
  struct sigaction sigchld_action;
  memset (&sigchld_action, 0, sizeof (sigchld_action));
  sigchld_action.sa_handler = &clean_up_child_process;
  sigaction (SIGCHLD, &sigchld_action, NULL);

   /* Create child*/
  child_pid = fork ();
  if (child_pid > 0) {

    /* Parent process */
    sleep (60);
  }
  else {

    /*Child process. Exit immediately. */
    exit (0);
  }
  return 0;
}
