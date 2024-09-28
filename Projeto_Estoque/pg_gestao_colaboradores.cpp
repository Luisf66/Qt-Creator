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
}


void pg_gestao_colaboradores::on_btn_cancelar_novo_clicked()
{

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

