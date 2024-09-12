#include "janelacontatos.h"
#include "ui_janelacontatos.h"

janelacontatos::janelacontatos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janelacontatos)
{
    ui->setupUi(this);
}

janelacontatos::~janelacontatos()
{
    delete ui;
}

void janelacontatos::on_btn_gravar_clicked()
{
    QString nome = ui->campo_nome->text();
    QString telefone = ui->campo_telefone->text();
    QString email = ui->campo_email->text();

    QSqlQuery query;
    query.prepare("INSERT INTO tb_contatos (nome_contato,telefone_contato,email_contato)"
                  " VALUES ('"+nome+"','"+telefone+"','"+email+"')");
    if(query.exec())
    {
        QMessageBox::information(this,"Operação Realizada com Sucesso","Dados Salvos");
        ui->campo_nome->clear();
        ui->campo_telefone->clear();
        ui->campo_email->clear();
        ui->campo_nome->setFocus();
    }
    else{
        QMessageBox::warning(this,"Falha na Operação","Dados informados não foram salvos");
    }
}

void janelacontatos::on_btn_cancelar_clicked()
{
    close();
}

