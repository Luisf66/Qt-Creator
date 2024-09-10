#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *telainicial = new QSplashScreen;
    telainicial->setPixmap(QPixmap(":/img/imagens/ElectronicArts(8).png"));
    telainicial->show();

    MainWindow w;

    QTimer::singleShot(4000,telainicial,SLOT(close()));
    QTimer::singleShot(4000,&w,SLOT(show()));

    //w.show();
    return a.exec();
}
