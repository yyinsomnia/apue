#include <sys/select.h>
#include <sys/time.h>
#include <stddef.h>

unsigned int
sleep_us(unsigned int u_seconds)
{
	struct timeval tv;
	tv.tv_usec = u_seconds;
	return select(0, NULL, NULL, NULL, &tv);
}
