#include "pg_gestao_estoque.h"
#include "ui_pg_gestao_estoque.h"

pg_gestao_estoque::pg_gestao_estoque(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_gestao_estoque)
{
    ui->setupUi(this);
    if(!con.conectar())
    {
        QMessageBox::warning(this,"Falha na Conexão","Banco de Dados inacessível");
    }
    else{
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_produtos");
        if(query.exec())
        {
            qDebug() << "Busca realizada";
        }
        else{
            QMessageBox::warning(this,"Falha na Busca","Busca não realizada");
        }
    }
}

pg_gestao_estoque::~pg_gestao_estoque()
{
    delete ui;
    con.desconectar();
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
    // declaração das variáveis para query
    QString aux_compra;
    QString aux_venda;
    QString codigo = ui->campo_codigo->text();
    QString descricao = ui->campo_descricao->text();
    QString fornecedor = ui->campo_fornecedor->text();
    QString quantidade = ui->campo_quantidade->text();

    // alteração de , por . caso seja digitado , no decimal
    aux_compra = ui->campo_valor_compra->text();
    std::replace(aux_compra.begin(),aux_compra.end(),',','.');

    aux_venda = ui->campo_valor_venda->text();
    std::replace(aux_venda.begin(),aux_venda.end(),',','.');

    QString valor_compra = aux_compra;
    QString valor_venda = aux_venda;

    // query para inserção dos dados no DB
    QSqlQuery query;
    query.prepare("INSERT INTO tb_produtos "
                  "(id_produto, produto, id_fornecedor, qtde_estoque, valor_compra, valor_venda) VALUES"
                  "("+QString::number(codigo.toInt())+", '"+descricao+"',"
                  ""+QString::number(fornecedor.toInt())+", "+QString::number(quantidade.toInt())+", "
                  ""+QString::number(valor_compra.toFloat())+", "+QString::number(valor_venda.toFloat())+")");
    if(!query.exec())
    {
        QMessageBox::warning(this,"Falha no Cadastro", "Produto não cadastrado");
    }
    else{
        QMessageBox::information(this,"Cadastro Realizado", "Produto cadastrado");
        pg_gestao_estoque::on_btn_novo_produto_clicked();
    }
}

