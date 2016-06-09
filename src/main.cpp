#include <mainwindow.h>
#include <image.h>
#include <imageloader.h>
#include <resultset.h>

#include <iostream>
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
