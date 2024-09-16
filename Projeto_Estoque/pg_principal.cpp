#include "pg_principal.h"
#include "./ui_pg_principal.h"

pg_principal::pg_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pg_principal)
{
    ui->setupUi(this);

    logado = false;
    cadFechado.addFile(":/imagens/img/simbolo-bloqueado.png"); // importarção das imagens
    cadAberto.addFile(":/imagens/img/valido.png");

    ui->btn_bloquear->setText(""); // limpar texto do botão
    ui->btn_bloquear->setIcon(cadFechado); // colocar icone X no botão
    ui->statusbar->addWidget(ui->btn_bloquear); // colocar botão na barra de status
    ui->statusbar->addWidget(ui->nome_colab); // colocar nome do colaborador na barra de status
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
        logado = logar.getLogado();
        nome_colab = logar.getNome();
        acesso_colab = logar.getAcesso();
        if(logado)
        {
            ui->btn_bloquear->setIcon(cadAberto);
            ui->nome_colab->setText(nome_colab);
        }
    }
    else{
        logado = false;
        ui->btn_bloquear->setIcon(cadAberto); // colocar icone Y no botão
        ui->nome_colab->setText("Sem Colaborador");
    }
}

