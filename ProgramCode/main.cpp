#include "zgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    zGui w;
    w.show();

    return a.exec();
}
