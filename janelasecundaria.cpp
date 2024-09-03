#include "janelasecundaria.h"
#include "ui_janelasecundaria.h"
#include <QPixmap>

JanelaSecundaria::JanelaSecundaria(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JanelaSecundaria)
{
    ui->setupUi(this);

    QPixmap logo(":/img/imagens/Firefox_wallpaper.png");
    ui->Imagem_github->setPixmap(logo.scaled(585,368,Qt::KeepAspectRatio));
}

JanelaSecundaria::~JanelaSecundaria()
{
    delete ui;
}

void JanelaSecundaria::on_Mudar_Imagem_clicked()
{
    QPixmap imagem(":/img/imagens/github-logo.webp");
    ui->Imagem_github->setPixmap(imagem.scaled(690,388,Qt::KeepAspectRatio));
}

