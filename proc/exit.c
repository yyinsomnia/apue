/*
 *  PID  PPID S TT       COMMAND
 * 6786  3177 S pts/3    bash
 * 9845  6786 S pts/3    ./proc/exit
 * 9846  9845 Z pts/3    [exit] <defunct>
 * 9848  9845 S pts/3    sh -c ps -o pid,ppid,state,tty,command
 * 9849  9848 R pts/3    ps -o pid,ppid,state,tty,command
 *23273  2494 S pts/3    git-credential-cache--daemon /home/leo/.git-credential-cache/socket
 *
 * why?
 */
#include "apue.h"

#ifdef SOLARIS
#define PSCMD	"ps -a -o pid,ppid,s,tty,comm"
#else
#define PSCMD	"ps -o pid,ppid,state,tty,command"
#endif

int
main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		exit(0);
	}

	sleep(4);
	system(PSCMD);

	exit(0);
}
