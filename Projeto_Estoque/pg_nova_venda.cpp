#include "pg_nova_venda.h"
#include "ui_pg_nova_venda.h"

pg_nova_venda::pg_nova_venda(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_nova_venda)
{
    ui->setupUi(this);
}

pg_nova_venda::~pg_nova_venda()
{
    delete ui;
}
