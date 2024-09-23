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

void pg_editar_produto_venda::on_btn_confirmar_clicked()
{
    QString aux;

    pg_nova_venda::edição = true;
    pg_nova_venda::g_qtde = ui->campo_quantidade->text();

    aux = ui->campo_preco_unitario->text();
    std::replace(aux.begin(),aux.end(),',','.');
    pg_nova_venda::g_val_unitario = aux;

    pg_nova_venda::g_val_total = QString::number(ui->campo_quantidade->text().toDouble() * aux.toDouble());
    close();
}


void pg_editar_produto_venda::on_btn_cancelar_clicked()
{
    pg_nova_venda::edição = false;
    close();
}

