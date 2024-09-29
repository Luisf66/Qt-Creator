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
    ui->tipo_acesso_2->addItem("A");
    ui->tipo_acesso_2->addItem("B");
    ui->campo_nome_novo->setFocus();

    ui->tabWidget->setCurrentIndex(0);

    ui->tabela_gestao_colab->setColumnCount(2);
    // definição do tamanho das linhas 0 e 1
    ui->tabela_gestao_colab->setColumnWidth(0,90);
    ui->tabela_gestao_colab->setColumnWidth(1,230);
    // cabeçalho das colunas
    QStringList cabecalho = {"ID", "Nome"};
    ui->tabela_gestao_colab->setHorizontalHeaderLabels(cabecalho);
    // estilização
    ui->tabela_gestao_colab->setStyleSheet("QTableView {selection-background-color:red}");
    ui->tabela_gestao_colab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tabela_gestao_colab->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabela_gestao_colab->verticalHeader()->setVisible(false);
}

pg_gestao_colaboradores::~pg_gestao_colaboradores()
{
    delete ui;
}

void pg_gestao_colaboradores::on_btn_salvar_novo_clicked()
{
    ui->tipo_acesso->setCurrentIndex(0);

    QString nome = ui->campo_nome_novo->text();
    QString username = ui->campo_usuario_novo->text();
    QString senha = ui->campo_senha_novo->text();
    QString telefone = ui->campo_telefone_novo->text();
    QString acesso = ui->tipo_acesso->currentText();

    QSqlQuery query;
    query.prepare("INSERT INTO tb_colaboradores (nome_colab, username_colab, senha_colab, fone_colab, acesso_colab)"
                  " VALUES ('"+nome+"', '"+username+"', '"+senha+"', '"+telefone+"', '"+acesso+"')");
    if(query.exec())
    {
        QMessageBox::information(this, "Cadastro Efetuado", "Dados dos Colaboradores foram salvos");
        // limpar os campos
        ui->campo_nome_novo->clear();
        ui->campo_usuario_novo->clear();
        ui->campo_senha_novo->clear();
        ui->campo_telefone_novo->clear();
        ui->tipo_acesso->setCurrentIndex(0);
        // apontar para o campo nome apos limpeza dos campos
        ui->campo_nome_novo->setFocus();
    }
    else{
        QMessageBox::critical(this,"Falha np Cadastro", "Os dados não foram salvos");
    }
}


void pg_gestao_colaboradores::on_btn_cancelar_novo_clicked()
{
    close();
}


void pg_gestao_colaboradores::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    {
        // Limpar a tabela caso já exista algo
        //Remover_Linhas(ui->tabela_gestao_colab);
        // guardar todas as linhas
        int nlinhas = 0;
        // query para buscar produto pelo id
        QSqlQuery query;
        query.prepare("SELECT id_colab, nome_colab FROM tb_colaboradores ORDER BY id_colab");
        if(query.exec())
        {
            // repetição enquanto houver proximo elemento
            while(query.next())
            {
                // inserção das linhas na tabela
                ui->tabela_gestao_colab->insertRow(nlinhas);
                // definição do elemento para inserção
                ui->tabela_gestao_colab->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tabela_gestao_colab->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tabela_gestao_colab->setRowHeight(nlinhas,20);
                nlinhas++;
            }
        }
        else{
            QMessageBox::warning(this,"Falha na Busca","Erro ao listar colaboradores");
        }
    }
}


void pg_gestao_colaboradores::on_tabela_gestao_colab_itemSelectionChanged()
{
    // atribuir o id de acordo com o selecionado
    int id = ui->tabela_gestao_colab->item(ui->tabela_gestao_colab->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_colaboradores WHERE id_colab="+QString::number(id));
    if(query.exec())
    {
        // preencher os campos de acordo com o retorno da busca
        query.first();
        ui->campo_nome_gestao->setText(query.value(1).toString());
        ui->campo_usuario_gestao->setText(query.value(2).toString());
        ui->campo_senha_gestao->setText(query.value(3).toString());
        ui->campo_telefone_gestao->setText(query.value(4).toString());
        ui->tipo_acesso_2->setCurrentText(query.value(5).toString());
    }
}

