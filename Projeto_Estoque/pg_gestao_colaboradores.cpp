#include "pg_gestao_colaboradores.h"
#include "ui_pg_gestao_colaboradores.h"

pg_gestao_colaboradores::pg_gestao_colaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_gestao_colaboradores)
{
    ui->setupUi(this);

    if(!con.verifica_conexao())
    {
        if(!con.conectar())
        {
            QMessageBox::warning(this,"Falha na Conexão","Não foi possível se conectar ao banco de dados");
        }
    }

    ui->tipo_acesso->addItem("A");
    ui->tipo_acesso->addItem("B");
    ui->campo_nome_novo->setFocus();
}

pg_gestao_colaboradores::~pg_gestao_colaboradores()
{
    delete ui;
}

void pg_gestao_colaboradores::on_btn_salvar_novo_clicked()
{
    ui->tipo_acesso->setCurrentIndex(0);
}


void pg_gestao_colaboradores::on_btn_cancelar_novo_clicked()
{

}

