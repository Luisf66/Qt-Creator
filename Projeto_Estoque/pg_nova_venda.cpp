#include "pg_nova_venda.h"
#include "ui_pg_nova_venda.h"

pg_nova_venda::pg_nova_venda(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_nova_venda)
{
    ui->setupUi(this);
    // verifica se já está conectado ao banco e trata caso não esteja
    if(!con.conectar())
    {
        if(!con.conectar())
        {
            QMessageBox::warning(this,"Falha na Conexão","Não foi possível se conectar ao banco de dados");
        }
    }
    // difinição do numero de colunas
    ui->tw_listar_produtos->setColumnCount(5);
    // definição da largura de cada coluna
    ui->tw_listar_produtos->setColumnWidth(0,200);
    ui->tw_listar_produtos->setColumnWidth(1,300);
    ui->tw_listar_produtos->setColumnWidth(2,100);
    ui->tw_listar_produtos->setColumnWidth(3,100);
    ui->tw_listar_produtos->setColumnWidth(4,100);
    // titulo de cada coluna
    QStringList cabecalhos = {"Código","Produto","Valor Unitário","Quantidade","Total"};
    ui->tw_listar_produtos->setHorizontalHeaderLabels(cabecalhos);
    // estilização
    ui->tw_listar_produtos->setStyleSheet("QTableView{selection-background-color:red;}");
    ui->tw_listar_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_listar_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listar_produtos->verticalHeader()->setVisible(false);
    // apontar para codigo do produto
    ui->campo_cod_produto->setFocus();
    nlinhas = 0;
}

pg_nova_venda::~pg_nova_venda()
{
    delete ui;
}

void pg_nova_venda::on_campo_cod_produto_returnPressed()
{
    // pegar id do produto
    QString id = ui->campo_cod_produto->text();
    QSqlQuery query;
    double valor_final = 0.0;

    // buscar produto
    query.prepare("SELECT id_produto,produto,valor_venda FROM tb_produtos WHERE id_produto="+id);
    if(!query.exec())
    {
        QMessageBox::warning(this,"Falha na Busca","Não foi possivel concluir a operação");
    }
    else{
        // pegar primeiro retorno da query
        query.first();
        //
        if(query.value(0).toString() != "")
        {
            // inserir linha na tabela
            ui->tw_listar_produtos->insertRow(nlinhas);
            // inserir os campos do produto na linha da tabela (id, produto, valor venda, quantidade)
            ui->tw_listar_produtos->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listar_produtos->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listar_produtos->setItem(nlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_listar_produtos->setItem(nlinhas,3,new QTableWidgetItem(ui->campo_quantidade->text()));
            // calculo do valor total da venda
            valor_final = ui->campo_quantidade->text().toDouble() * query.value(2).toDouble();
            ui->tw_listar_produtos->setItem(nlinhas,4,new QTableWidgetItem(QString::number(valor_final)));
            ui->tw_listar_produtos->setRowHeight(nlinhas,20);
            nlinhas++;

            ui->campo_cod_produto->clear();
            ui->campo_quantidade->setText("1");
        }
        else{
            QMessageBox::warning(this,"Falha na Busca", "Produto não encontrado");
        }
    }
}

