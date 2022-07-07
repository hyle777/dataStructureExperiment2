#include "widget.h"

#include <QApplication>

#include"bintree.h"
#include"bintree.cpp"
#include"StudentMes.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
