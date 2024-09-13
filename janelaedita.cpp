#include "janelaedita.h"
#include "ui_janelaedita.h"

int id;

janelaedita::janelaedita(QWidget *parent, int id_contato)
    : QDialog(parent)
    , ui(new Ui::janelaedita)
{
    ui->setupUi(this);
    id = id_contato;
    QSqlQuery  query;
    query.prepare("SELECT * FROM tb_contatos WHERE id_contato="+QString::number(id_contato));
    if(query.exec())
    {
        query.first();
        ui->label_2->setText(query.value(0).toString());
        ui->campo_nome->setText(query.value(1).toString());
        ui->campo_telefone->setText(query.value(2).toString());
        ui->campo_email->setText(query.value(3).toString());
    }
    else{
        QMessageBox::warning(this,"Erro","Falha na Edição");
    }
}

janelaedita::~janelaedita()
{
    delete ui;
}

void janelaedita::on_btn_salvar_clicked()
{
    QString nome = ui->campo_nome->text();
    QString telefone = ui->campo_telefone->text();
    QString email = ui->campo_email->text();

    QSqlQuery query;
    query.prepare("UPDATE tb_contatos SET nome_contato='"+nome+"', telefone_contato='"+telefone+"', email_contato='"+email+"' where id_contato="+QString::number(id));
    if(query.exec())
    {
        QMessageBox::information(this,"Operação Concluida","Contato Alterado");
        close();
    }
    else{
        QMessageBox::warning(this,"Operação Não Finalizada","Contato não foi Alterado");
    }
}

