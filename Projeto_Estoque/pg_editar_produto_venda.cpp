#include "pg_editar_produto_venda.h"
#include "ui_pg_editar_produto_venda.h"

pg_editar_produto_venda::pg_editar_produto_venda(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_editar_produto_venda)
{
    ui->setupUi(this);
    ui->campo_produto->setText(pg_nova_venda::g_prod);
    ui->campo_quantidade->setText(pg_nova_venda::g_qtde);
    ui->campo_preco_unitario->setText(pg_nova_venda::g_val_total);
}

pg_editar_produto_venda::~pg_editar_produto_venda()
{
    delete ui;
}
