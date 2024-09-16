#include "pg_gestao_colaboradores.h"
#include "ui_pg_gestao_colaboradores.h"

pg_gestao_colaboradores::pg_gestao_colaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_gestao_colaboradores)
{
    ui->setupUi(this);
}

pg_gestao_colaboradores::~pg_gestao_colaboradores()
{
    delete ui;
}
