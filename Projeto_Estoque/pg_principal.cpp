#include "pg_principal.h"
#include "./ui_pg_principal.h"

pg_principal::pg_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pg_principal)
{
    ui->setupUi(this);
    QString local = qApp->applicationDirPath();
    QString banco = local + "/DataBase/banco_de_dados.db";
    banco_db.setDatabaseName(banco); // definição do banco de dados

    logado = false;
    cadFechado.addFile(":/imagens/img/simbolo-bloqueado.png"); // importarção das imagens
    cadAberto.addFile(":/imagens/img/valido.png");

    ui->btn_bloquear->setText(""); // limpar texto do botão
    ui->btn_bloquear->setIcon(cadFechado); // colocar icone X no botão
    ui->statusbar->addWidget(ui->btn_bloquear); // colocar botão na barra de status

    if(!banco_db.open())
    {
        QMessageBox::warning(this,"Falha no Banco","O banco de dados não foi acessado corretamente");
        qDebug() << "caminho: " + banco;
        // qDebug() << banco_db.lastError().text(); // Debug do erro exato
        // qDebug() << "Drivers disponíveis: " << QSqlDatabase::drivers();

    }
    // else{
    //     qDebug() << "Banco aberto";
    // }
}

pg_principal::~pg_principal()
{
    delete ui;
}

void pg_principal::on_btn_bloquear_clicked()
{
    if(!logado)
    {
        pg_login logar;
        logar.exec(); // abertura da pagina de login
    }
    else{
        logado = true;
        ui->btn_bloquear->setIcon(cadAberto); // colocar icone Y no botão
    }
}

