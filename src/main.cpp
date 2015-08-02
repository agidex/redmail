#include <QtGui/QApplication>
#include "redmail.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RedMail w;
    w.show();

    return a.exec();
}
