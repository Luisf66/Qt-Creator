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
}

pg_nova_venda::~pg_nova_venda()
{
    delete ui;
}
