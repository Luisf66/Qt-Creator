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
        funcoes_globais::Remover_Linhas(ui->tabela_gestao_colab);
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


void pg_gestao_colaboradores::on_btn_salver_gestao_clicked()
{
    if(ui->tabela_gestao_colab->currentRow() == -1)
    {
        QMessageBox::warning(this,"Falha na Operação","Nenhum colaborador selecionado");
        return;
    }
    QString id = ui->tabela_gestao_colab->item(ui->tabela_gestao_colab->currentRow(),0)->text();
    QString nome = ui->campo_nome_gestao->text();
    QString username = ui->campo_usuario_gestao->text();
    QString senha = ui->campo_senha_gestao->text();
    QString telefone = ui->campo_telefone_gestao->text();
    QString acesso = ui->tipo_acesso_2->currentText();

    QSqlQuery query;
    query.prepare("UPDATE tb_colaboradores SET nome_colab = '"+nome+"', username_colab = '"+username+"', "
                "senha_colab = '"+senha+"', fone_colab = '"+telefone+"', acesso_colab = '"+acesso+"'"
                "  where id_colab="+id);
    if(query.exec())
    {
        int linha = ui->tabela_gestao_colab->currentRow();
        ui->tabela_gestao_colab->item(linha,1)->setText(nome);

        QMessageBox::information(this, "Atualização Realizada", "Dados do colaborador foram alterados");
    }
    else{
        QMessageBox::warning(this,"Falha na Atualização", "Os dados não foram alterados");
    }
}


void pg_gestao_colaboradores::on_btn_excluir_gestao_clicked()
{
    // verifica se há algo selecionado
    if(ui->tabela_gestao_colab->currentRow() == -1){
        QMessageBox::warning(this,"Falha na Exclusão", "Nenhum colaborador selecionado");
    }
    else{
        // confirma a exclusão do produto
        QMessageBox::StandardButton opcao = QMessageBox::question(this,"Deletar Colaborador","Você realmente deseja excluir o colaborador?",QMessageBox::Yes|QMessageBox::No);
        if(opcao == QMessageBox::Yes)
        {
            // obtem a linha do produto selecionado
            int linha = ui->tabela_gestao_colab->currentRow();
            QString id = ui->tabela_gestao_colab->item(linha,0)->text();
            QSqlQuery query;
            query.prepare("DELETE FROM tb_colaboradores WHERE id_colab="+id);
            if(query.exec())
            {
                // deleta a linha selecionada
                ui->tabela_gestao_colab->removeRow(linha);
                QMessageBox::information(this,"Colaborador Deletado","Colaborador foi deletado com sucesso");
            }
            else{
                QMessageBox::warning(this,"Falha na Exclusão", "O colaborador não foi removido");
            }

        }
    }
}

