#include "janelapesquisa.h"
#include "ui_janelapesquisa.h"

janelapesquisa::janelapesquisa(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janelapesquisa)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_contatos");
    if(query.exec())
    {
        int resultados = 0;
        ui->tabela->setColumnCount(4);
        while(query.next())
        {
            ui->tabela->insertRow(resultados);
            ui->tabela->setItem(resultados,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tabela->setItem(resultados,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tabela->setItem(resultados,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tabela->setItem(resultados,3,new QTableWidgetItem(query.value(3).toString()));

            ui->tabela->setRowHeight(resultados,20);
            resultados++;
        }
        ui->tabela->setColumnWidth(0,30);
        ui->tabela->setColumnWidth(1,150);
        ui->tabela->setColumnWidth(2,150);
        ui->tabela->setColumnWidth(3,230);

        QStringList cabecalho = {"ID","Nome","Telefone","E-mail"};
        ui->tabela->setHorizontalHeaderLabels(cabecalho);
        ui->tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tabela->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tabela->verticalHeader()->setVisible(false);
    }else{
        QMessageBox::warning(this,"ERRO","Falha na Consulta");
    }
}

janelapesquisa::~janelapesquisa()
{
    delete ui;
}

void janelapesquisa::on_btn_excluir_clicked()
{
    int linha = ui->tabela->currentRow();
    int id = ui->tabela->item(linha,0)->text().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM tb_contatos WHERE id_contato="+QString::number(id));
    if(query.exec())
    {
        ui->tabela->removeRow(linha);
        QMessageBox::information(this,"Operação Finalizada","Contato removido");
    }
    else{
        QMessageBox::warning(this,"Erro","Contato não removido");
    }

}


void janelapesquisa::on_btn_editar_clicked()
{
    int linha = ui->tabela->currentRow();
    int id = ui->tabela->item(linha,0)->text().toInt();
    janelaedita edita_contato(this,id);
    edita_contato.exec();
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_contatos WHERE id_contato="+QString::number(id));
    if(query.exec())
    {
        query.first();
        ui->tabela->setItem(linha,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tabela->setItem(linha,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tabela->setItem(linha,3,new QTableWidgetItem(query.value(3).toString()));
    }
}

