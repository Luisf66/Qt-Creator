#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QtDebug>
#include "janelasecundaria.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->addPermanentWidget(ui->pushButton_3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("Obrigado Por Contribuir");  // botão para mudança no texto
}


void MainWindow::on_pushButton_2_clicked()
{
    QString estilo = "background-color: #0000FF;color: #FFFF00;";

    ui->label->setText("https://github.com/Luisf66/Qt-Creator.git");  // botão para mudança no texto
    ui->label->setStyleSheet(estilo); // botão para mudança no estilo do texto
}


void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::StandardButton resposta = QMessageBox::question(this,"","Deseja Encerrar a Aplicação?",QMessageBox::Yes | QMessageBox::No);
    if(resposta == QMessageBox::Yes)
    {
        close();
    }
    else {
        qDebug() << "Aplicação não Finalizada";
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    JanelaSecundaria guia2;
    guia2.exec();
}


void MainWindow::on_btn_exibir_clicked()
{
    QString nome = ui->campo_nome->text(); //  salvar campo nome
    QString email = ui->campo_email->text(); //  salvar campo email
    QString telefone = ui->campo_telefone->text();  //  salvar campo telefone

    QMessageBox::information(this,"Dados Preenchidos","Nome:"+nome+"\nE-mail:"+email+"\nTelefone:"+telefone); // exibir os dados salvos
}


void MainWindow::on_btn_limpar_clicked()
{
    ui->campo_nome->clear();
    ui->campo_email->clear();
    ui->campo_telefone->clear();

    ui->campo_nome->setFocus();
}
