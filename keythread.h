#ifndef KEYTHREAD_H
#define KEYTHREAD_H

#include <QThread>

class KeyThread : public QThread
{
Q_OBJECT
public:
    KeyThread();
    virtual void run();

	int GetMdelay(struct input_event *evt1, struct input_event *evt2);

signals:
    void NextPic();
};

#endif // KEYTHREAD_H
