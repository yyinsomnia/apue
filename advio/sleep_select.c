#include <sys/select.h>
#include <sys/time.h>
#include <stddef.h>

void
sleep_us(unsigned int u_seconds)
{
	struct timeval tv;
	tv.tv_sec = u_seconds / 1000000;
	tv.tv_usec = u_seconds % 1000000;
	select(0, NULL, NULL, NULL, &tv);
}
