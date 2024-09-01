#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


void MainWindow::on_pushButton_3_clicked()
{
    close();
}

