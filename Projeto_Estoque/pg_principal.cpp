#include "pg_principal.h"
#include "./ui_pg_principal.h"

pg_principal::pg_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pg_principal)
{
    ui->setupUi(this);
    bloqueado = false;
    cadFechado.addFile(":/imagens/img/simbolo-bloqueado.png");
    cadAberto.addFile(":/imagens/img/valido.png");

    ui->btn_bloquear->setText("");
    ui->btn_bloquear->setIcon(cadAberto);
    ui->statusbar->addWidget(ui->btn_bloquear);
}

pg_principal::~pg_principal()
{
    delete ui;
}

void pg_principal::on_btn_bloquear_clicked()
{
    if(bloqueado)
    {
        //nova tela
    }
    else{
        bloqueado = true;
        ui->btn_bloquear->setIcon(cadFechado);
    }
}

