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

        }
        else{
            QMessageBox::warning(this,"Falha na Busca","Busca não realizada");
        }
    }
    ui->tw_produtos->setColumnCount(2);
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


void pg_gestao_estoque::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    {
        // guardar todas as linhas
        int nlinhas = 0;
        // query para buscar produto pelo id
        QSqlQuery query;
        query.prepare("SELECT id_produto, produto FROM tb_produtos ORDER BY produto");
        if(query.exec())
        {
            // repetição enquanto houver proximo elemento
            while(query.next())
            {
                // inserção das linhas na tabela
                ui->tw_produtos->insertRow(nlinhas);
                // definição do elemento para inserção
                ui->tw_produtos->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_produtos->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_produtos->setRowHeight(nlinhas,20);
                nlinhas++;
            }
            // definição do tamanho das linhas 0 e 1
            ui->tw_produtos->setColumnWidth(0,150);
            ui->tw_produtos->setColumnWidth(1,230);
            // cabeçalho das colunas
            QStringList cabecalho = {"Código", "Produto"};
            ui->tw_produtos->setHorizontalHeaderLabels(cabecalho);
            // estilização
            ui->tw_produtos->setStyleSheet("QTableView {selection-background-color: green}");
            ui->tw_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_produtos->verticalHeader()->setVisible(false);
        }
        else{
            QMessageBox::warning(this,"Falha na Busca","Busca não realizada");
        }
    }
}
