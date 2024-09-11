#include "janelaterciaria.h"
#include "ui_janelaterciaria.h"
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QMessageBox>

janelaterciaria::janelaterciaria(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janelaterciaria)
{
    ui->setupUi(this);
    QSqlDatabase banco = QSqlDatabase::addDatabase("QSQLITE");
    banco.setDatabaseName("/home/luis/Qt-curso/Aula_01/Banco/teste.db");

    if(!banco.open())
    {
        ui->label->setText("Conexão não estabelecida");
    }
    else{
        ui->label->setText("Banco De Dados Conectado");
    }
}

janelaterciaria::~janelaterciaria()
{
    delete ui;
}


void janelaterciaria::on_pushButton_clicked()
{
    QProcess process;
    process.startDetached("/usr/bin/git");  // Caminho do vim no sistema
}


void janelaterciaria::on_btn_link_clicked()
{
    QString link = "https://github.com/Luisf66/Qt-Creator";
    QDesktopServices::openUrl(link);
}



void janelaterciaria::on_btn_login_clicked()
{
    QSqlDatabase banco = QSqlDatabase::database();
    QString nome = ui->campo_nome->text();
    QString senha = ui->campo_senha->text();

    qDebug() << "Nome: " << nome;
    qDebug() << "Senha: " << senha;

    if(!banco.isOpen())
    {
        QMessageBox::warning(this,"Usuário Não Encontrado","O usuário inserido não foi listado no Banco de Dados");
    }
    QSqlQuery query;
    if(query.exec("SELECT * FROM tb_colaboradores WHERE username='"+nome+"' AND senha='"+senha+"'"))
    {
        qDebug() << "Query executada";
        int retornos = 0;
        while(query.next())
        {
            retornos++;
            qDebug() << "retornos: " << retornos;
        }
        if(retornos > 0)
        {
            QMessageBox::about(this,"Login Completo","Dados Logados com Sucesso");
        }
        else{
            ui->label->setText("Login não efetuado");
            ui->campo_nome->clear();
            ui->campo_senha->clear();
            ui->campo_nome->setFocus();
        }
    }
}


void janelaterciaria::on_btn_add_contato_clicked()
{
    janelacontatos novo_contato;
    novo_contato.exec();
}

