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
    }else{
        QMessageBox::warning(this,"ERRO","Falha na Consulta");
    }
}

janelapesquisa::~janelapesquisa()
{
    delete ui;
}
