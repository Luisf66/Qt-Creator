#include "janelasecundaria.h"
#include "ui_janelasecundaria.h"
#include <QPixmap>
#include "QMessageBox"

JanelaSecundaria::JanelaSecundaria(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JanelaSecundaria)
{
    ui->setupUi(this);

    QPixmap logo(":/img/imagens/Firefox_wallpaper.png");
    ui->Imagem_github->setPixmap(logo.scaled(785,568,Qt::KeepAspectRatio));
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


void JanelaSecundaria::on_pushButton_clicked()
{
    bool cb[2];
    QString mensagem = "";

    cb[0]=ui->checkBox->isChecked();
    cb[1]=ui->checkBox_2->isChecked();

    mensagem = "";
    for(int i = 0;i < 2;  i++){
        if(cb[i]){
            mensagem += "CB"+QString::number(i+1)+" marcado ";
        }
    }
    QMessageBox::about(this,"Objetos Selecionados", mensagem);
}


void JanelaSecundaria::on_btn_adicionar_clicked()
{
    ui->listWidget->addItem(ui->lineEdit->text());
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}


void JanelaSecundaria::on_btn_marcar_clicked()
{
    ui->listWidget->currentItem()->setForeground(Qt::lightGray);
    ui->listWidget->currentItem()->setBackground(Qt::darkBlue);
}


void JanelaSecundaria::on_btn_desmarcar_clicked()
{
    ui->listWidget->currentItem()->setForeground(Qt::black);
    ui->listWidget->currentItem()->setBackground(Qt::white);
}

