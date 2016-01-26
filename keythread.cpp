#include "keythread.h"

#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

KeyThread::KeyThread()
{
}

int KeyThread::GetMdelay(struct input_event *evt1, struct input_event *evt2)
{
	unsigned int usec1, usec2;
	usec1 = evt1->time.tv_sec * 1000000 + evt1->time.tv_usec;
	usec2 = evt2->time.tv_sec * 1000000 + evt2->time.tv_usec;
	return (usec1 > usec2 ? usec1 - usec2 : usec2 - usec1)/1000;
}

void KeyThread::run()
{
	int ts_fd;
	struct input_event ie[2];

	memset(ie, 0, sizeof(ie));

	ts_fd = open("/dev/input/touchscreen0", O_RDONLY);
	if (!ts_fd) {
		qDebug("Failed to open ts device");
		return;
	}

    while (1) {
		if (read(ts_fd, &ie[0], sizeof(struct input_event)) < 1) {
			qDebug("Getting touch event failed");
			sleep(1);
			continue;
		}

		if (ie[0].type == EV_KEY && ie[0].value == 0 && GetMdelay(&ie[0], &ie[1]) > 500) {
			emit NextPic();
			memcpy(&ie[1], &ie[0], sizeof(struct input_event));
		}		
    }
}
