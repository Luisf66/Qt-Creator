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


void pg_principal::on_btn_nova_venda_clicked()
{
    if(logado)
    {
        pg_nova_venda nova_venda;
        nova_venda.exec();
    }
    else{
        QMessageBox::information(this,"Operação Inválida","Realize o Login para prosseguir");
    }
}


void pg_principal::on_actionEstoque_triggered()
{
    // logica de acesso para estoque
    if(logado)
    {
        if(acesso_colab == "A")
        {
            pg_gestao_estoque gestao_estoque;
            gestao_estoque.exec();
        }
        else{
            QMessageBox::information(this,"Operação Inválida","Nível de Acesso Insuficiente");
        }
    }
    else{
        QMessageBox::information(this,"Operação Inválida","Realize o Login para prosseguir");
    }
}


void pg_principal::on_actionColaboradores_triggered()
{
    // logica de acesso para colaboradores
    if(logado)
    {
        if(acesso_colab == "A")
        {
            pg_gestao_colaboradores gestao_colaboradores;
            gestao_colaboradores.exec();
        }
        else{
            QMessageBox::information(this,"Operação Inválida","Nível de Acesso Insuficiente");
        }
    }
    else{
        QMessageBox::information(this,"Operação Inválida","Realize o Login para prosseguir");
    }
}


void pg_principal::on_actionVendas_triggered()
{
    // logica de acesso para vendas
    if(logado)
    {
        if(acesso_colab == "A")
        {
            pg_gestao_vendas gestao_vendas;
            gestao_vendas.exec();
        }
        else{
            QMessageBox::information(this,"Operação Inválida","Nível de Acesso Insuficiente");
        }
    }
    else{
        QMessageBox::information(this,"Operação Inválida","Realize o Login para prosseguir");
    }
}

