#include "apue.h"
#include <fcntl.h>

int
main(void)
{
	int		fd;
	pid_t	pid;
	pid_t   ppid;
	pid_t 	pppid; /* f**k */

	/*
	 * Create a file and write three bytes to it.
	 */
	if ((fd = creat("templock", FILE_MODE)) < 0)
		err_sys("creat error");
	if (write(fd, "abc", 3) != 3)
		err_sys("write error");

	/* add read lock first to let the child write lock block */
	readw_lock(fd, 0, SEEK_SET, 0);
	printf("read got the lock\n");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) { /* child */
		if (writew_lock(fd, 1, SEEK_SET, 1) < 0)
			err_sys("writew_lock error");
		printf("write got the lock\n");
		sleep(1);
		un_lock(fd, 0, SEEK_SET, 0);
	} else { /* parent */
		if ((ppid = fork()) < 0) {
			err_sys("fork error");
		} else if (ppid == 0) { /* child */
			if (readw_lock(fd, 0, SEEK_SET, 0) < 0)
				err_sys("readw_lock error");
			printf("read got the lock\n");
			sleep(1);
			un_lock(fd, 0, SEEK_SET, 0);
		} else { /* parent */
			if ((pppid = fork()) < 0) {
				err_sys("fork error");
			} else if (pppid == 0) { /* child */
				if (readw_lock(fd, 0, SEEK_SET, 0) < 0)
					err_sys("readw_lock error");
				printf("read got the lock\n");
				sleep(1);
				un_lock(fd, 0, SEEK_SET, 0);
			} else { /* parent */
				sleep(1);
				un_lock(fd, 0, SEEK_SET, 0);
			}
		}
	}
	exit(0);
}
