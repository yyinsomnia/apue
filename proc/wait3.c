#include "apue.h"
#include <sys/wait.h>

void pro_exit(siginfo_t *infop);

int
main(void)
{
	pid_t	pid, c_pid;
	int		status;
	siginfo_t info;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {
		exit(7);
	}

	if (waitid(P_PID, pid, &info, WEXITED) != 0) {
		err_sys("wait error");
	}

	pro_exit(&info);				/* and print its status */

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)				/* child */
		abort();					/* generates SIGABRT */

	if (waitid(P_PID, pid, &info, WEXITED) != 0)		/* wait for child */
		err_sys("wait error");

	pro_exit(&info);				/* and print its status */

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)				/* child */
		status /= 0;				/* divide by 0 generates SIGFPE */

	if (waitid(P_PID, pid, &info, WEXITED) != 0)		/* wait for child */
		err_sys("wait error");

	pro_exit(&info);				/* and print its status */

	exit(0);
}

void
pro_exit(siginfo_t *infop)
{
	if (infop->si_code == 1) { /* loop the siginof_t... find the diff*/
		printf("normal termination, exit status = %d\n", infop->si_status);
	} else {
		printf("abnormal termination, signal number = %d\n", infop->si_signo);
	}

}
