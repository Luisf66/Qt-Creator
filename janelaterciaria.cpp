#include "janelaterciaria.h"
#include "ui_janelaterciaria.h"
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>

janelaterciaria::janelaterciaria(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janelaterciaria)
{
    ui->setupUi(this);
}

janelaterciaria::~janelaterciaria()
{
    delete ui;
}


void janelaterciaria::on_pushButton_clicked()
{
    QProcess process;
    process.startDetached("/usr/bin/git");  // Caminho do vim no sistema
}


void janelaterciaria::on_btn_link_clicked()
{
    QString link = "https://github.com/Luisf66/Qt-Creator";
    QDesktopServices::openUrl(link);
}

