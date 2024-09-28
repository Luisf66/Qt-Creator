#include "pg_login.h"
#include "ui_pg_login.h"

pg_login::pg_login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_login)
{
    ui->setupUi(this);
    logado = false;
}

pg_login::~pg_login()
{
    delete ui;
}

void pg_login::on_btn_login_clicked()
{
    if(!con.conectar()){
        QMessageBox::warning(this,"Falha na Conexão","Não foi possível conectar o banco"); // verificação da conexão
    }
    else{
        // Pegar os dados inseridos e buscar no DB para logar
        QString username, senha;
        username = ui->campo_username->text();
        senha = ui->campo_senha->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_colaboradores WHERE username_colab='"+username+"' AND senha_colab='"+senha+"'");
        if(query.exec()){
            query.first();
            if(query.value(1).toString() != "")
            {
                variaveis_globais::logado = true;
                variaveis_globais::nome_colab = query.value(1).toString();
                variaveis_globais::id_colab = query.value(0).toInt();
                variaveis_globais::acesso_colab = query.value(5).toString();

                con.desconectar();
                close();
            }
            else{
                QMessageBox::warning(this,"Falha no Login","Dados inseridos não encontrados");
            }
        }
        else{
            QMessageBox::warning(this,"Falha no Login","Não foi possível realizar a busca");
        }
    }
    con.desconectar();
}


void pg_login::on_btn_cancelar_clicked()
{
    logado = false;
    close();
}
