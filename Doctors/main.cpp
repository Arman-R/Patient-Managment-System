#include "validationwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ValidationWin w;
    w.show();
    return a.exec();
}
