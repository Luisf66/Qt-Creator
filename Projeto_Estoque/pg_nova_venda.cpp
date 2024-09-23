#include "pg_nova_venda.h"
#include "ui_pg_nova_venda.h"

QString pg_nova_venda::g_id_prod;
QString pg_nova_venda::g_prod;
QString pg_nova_venda::g_qtde;
QString pg_nova_venda::g_val_total;
QString pg_nova_venda::g_val_unitario;

bool pg_nova_venda::edição;

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

            ui->cifra->setText("R$ "+ QString::number(Calcula_Total(ui->tw_listar_produtos,4)));
        }
        else{
            QMessageBox::warning(this,"Falha na Busca", "Produto não encontrado");
        }
        Limpar_campos();
    }
}

void pg_nova_venda::Limpar_campos(){
    ui->campo_cod_produto->clear();
    ui->campo_quantidade->setText("1");
    ui->campo_cod_produto->setFocus();
}

double pg_nova_venda::Calcula_Total(QTableWidget *tw, int coluna){
    int total_linhas = 0;
    double total_venda = 0.0;

    total_linhas = ui->tw_listar_produtos->rowCount();
    for(int i = 0; i < total_linhas; i++){
        total_venda +=  tw->item(i,coluna)->text().toDouble();
    }
    return total_venda;
}

void pg_nova_venda::on_btn_excluir_produto_clicked()
{
    if(ui->tw_listar_produtos->currentColumn() != -1)
    {
        QMessageBox::StandardButton opcao = QMessageBox::question(this,"O produto selecionado será removido da venda","Prosseguir ?",QMessageBox::Yes|QMessageBox::No);
        if(opcao == QMessageBox::Yes)
        {
            ui->tw_listar_produtos->removeRow(ui->tw_listar_produtos->currentRow());
            ui->cifra->setText("R$ "+ QString::number(Calcula_Total(ui->tw_listar_produtos,4)));
            nlinhas--;
        }
    }
    else{
        QMessageBox::warning(this,"Falha na operação", "Nenhum produto foi selecionado");
    }
}


void pg_nova_venda::on_btn_editar_venda_clicked()
{
    if(ui->tw_listar_produtos->currentColumn() != -1){
        int linha = ui->tw_listar_produtos->currentRow();

        g_id_prod = ui->tw_listar_produtos->item(linha,0)->text();
        g_prod = ui->tw_listar_produtos->item(linha,1)->text();
        g_val_total = ui->tw_listar_produtos->item(linha,2)->text();
        g_qtde = ui->tw_listar_produtos->item(linha,3)->text();

        pg_editar_produto_venda editar_venda;
        editar_venda.exec();

        if(edição)
        {
            ui->tw_listar_produtos->item(linha,2)->setText(g_val_unitario);
            ui->tw_listar_produtos->item(linha,3)->setText(g_qtde);
            ui->tw_listar_produtos->item(linha,4)->setText(g_val_total);
            ui->cifra->setText("R$ "+ QString::number(Calcula_Total(ui->tw_listar_produtos,4)));
        }
    }
}

