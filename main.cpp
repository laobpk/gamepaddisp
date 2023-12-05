#include <QApplication>
#include "gamepaddraw.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<XINPUT_STATE>("XINPUT_STATE");
    gamepaddraw w;
    w.show();

    return a.exec();
}
