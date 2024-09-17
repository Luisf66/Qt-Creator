#include "pg_gestao_estoque.h"
#include "ui_pg_gestao_estoque.h"

pg_gestao_estoque::pg_gestao_estoque(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_gestao_estoque)
{
    ui->setupUi(this);
}

pg_gestao_estoque::~pg_gestao_estoque()
{
    delete ui;
}

void pg_gestao_estoque::on_btn_novo_produto_clicked()
{
    // limpar os campos
    ui->campo_codigo->clear();
    ui->campo_descricao->clear();
    ui->campo_fornecedor->clear();
    ui->campo_quantidade->clear();
    ui->campo_valor_compra->clear();
    ui->campo_valor_venda->clear();
    // apontar para o campo codigo apos limpeza dos campos
    ui->campo_codigo->setFocus();

}


void pg_gestao_estoque::on_btn_salvar_clicked()
{
    //QString ;
    QDebug() << "Botão de Salvar";
}

