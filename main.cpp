#include "cbuiltimdlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBuiltimDlg w;
    w.show();
    return a.exec();
}
