#include "pg_gestao_vendas.h"
#include "ui_pg_gestao_vendas.h"

pg_gestao_vendas::pg_gestao_vendas(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_gestao_vendas)
{
    ui->setupUi(this);
}

pg_gestao_vendas::~pg_gestao_vendas()
{
    delete ui;
}
