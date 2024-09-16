#include "pg_login.h"
#include "ui_pg_login.h"

pg_login::pg_login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_login)
{
    ui->setupUi(this);
}

pg_login::~pg_login()
{
    delete ui;
}

void pg_login::on_btn_login_clicked()
{
    if(!con.conectar()){
        QMessageBox::warning(this,"Falha na Conexão","Não foi possível conectar o banco");
    }
    else{
        QString username, senha;
        username = ui->campo_username->text();
        senha = ui->campo_senha->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_colaboradores WHERE username_colab='"+username+"' AND senha_colab='"+senha+"'");
        if(query.exec()){
            qDebug() << "Query executada";
        }
    }
    con.desconectar();
}

