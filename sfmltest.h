#ifndef SFMLTEST_H
#define SFMLTEST_H

#include <SFML/Window.hpp>
#include <iostream>
#include <QThread>
#include <Windows.h>
#include <Xinput.h>

class sfmltest : public QThread
{
    Q_OBJECT
public:
    sfmltest();

signals:
    void sig_joystickex(XINPUT_STATE);

protected:
    void run();
};

#endif // SFMLTEST_H
