#include "pg_gestao_estoque.h"
#include "ui_pg_gestao_estoque.h"

pg_gestao_estoque::pg_gestao_estoque(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_gestao_estoque)
{
    ui->setupUi(this);
    if(!con.conectar())
    {
        QMessageBox::warning(this,"Falha na Conexão","Banco de Dados inacessível");
    }
    else{
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_produtos");
        if(query.exec())
        {

        }
        else{
            QMessageBox::warning(this,"Falha na Busca","Busca não realizada");
        }
    }
    ui->tw_produtos->setColumnCount(2);
    ui->tabWidget->setCurrentIndex(0);
}

pg_gestao_estoque::~pg_gestao_estoque()
{
    delete ui;
    con.desconectar();
}

void pg_gestao_estoque::on_btn_novo_produto_clicked()
{
    // limpar os campos
    ui->campo_codigo->clear();
    ui->campo_descricao->clear();
    ui->campo_fornecedor->clear();
    ui->campo_quantidade->clear();
    ui->campo_valor_compra->clear();
    ui->campo_valor_venda->clear();
    // apontar para o campo codigo apos limpeza dos campos
    ui->campo_codigo->setFocus();

}

void pg_gestao_estoque::on_btn_salvar_clicked()
{
    // declaração das variáveis para query
    QString aux_compra;
    QString aux_venda;
    QString codigo = ui->campo_codigo->text();
    QString descricao = ui->campo_descricao->text();
    QString fornecedor = ui->campo_fornecedor->text();
    QString quantidade = ui->campo_quantidade->text();

    // alteração de , por . caso seja digitado , no decimal
    aux_compra = ui->campo_valor_compra->text();
    std::replace(aux_compra.begin(),aux_compra.end(),',','.');

    aux_venda = ui->campo_valor_venda->text();
    std::replace(aux_venda.begin(),aux_venda.end(),',','.');

    QString valor_compra = aux_compra;
    QString valor_venda = aux_venda;

    // query para inserção dos dados no DB
    QSqlQuery query;
    query.prepare("INSERT INTO tb_produtos "
                  "(id_produto, produto, id_fornecedor, qtde_estoque, valor_compra, valor_venda) VALUES"
                  "("+QString::number(codigo.toInt())+", '"+descricao+"',"
                  ""+QString::number(fornecedor.toInt())+", "+QString::number(quantidade.toInt())+", "
                  ""+QString::number(valor_compra.toFloat())+", "+QString::number(valor_venda.toFloat())+")");
    if(!query.exec())
    {
        QMessageBox::warning(this,"Falha no Cadastro", "Produto não cadastrado");
    }
    else{
        QMessageBox::information(this,"Cadastro Realizado", "Produto cadastrado");
        pg_gestao_estoque::on_btn_novo_produto_clicked();
    }
}


void pg_gestao_estoque::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    {
        // Limpar a tabela caso já exista algo
        funcoes_globais::Remover_Linhas(ui->tw_produtos);
        // guardar todas as linhas
        int nlinhas = 0;
        // query para buscar produto pelo id
        QSqlQuery query;
        query.prepare("SELECT id_produto, produto FROM tb_produtos ORDER BY produto");
        if(query.exec())
        {
            // repetição enquanto houver proximo elemento
            while(query.next())
            {
                // inserção das linhas na tabela
                ui->tw_produtos->insertRow(nlinhas);
                // definição do elemento para inserção
                ui->tw_produtos->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_produtos->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_produtos->setRowHeight(nlinhas,20);
                nlinhas++;
            }
            // definição do tamanho das linhas 0 e 1
            ui->tw_produtos->setColumnWidth(0,150);
            ui->tw_produtos->setColumnWidth(1,230);
            // cabeçalho das colunas
            QStringList cabecalho = {"Código", "Produto"};
            ui->tw_produtos->setHorizontalHeaderLabels(cabecalho);
            // estilização
            ui->tw_produtos->setStyleSheet("QTableView {selection-background-color:red}");
            ui->tw_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_produtos->verticalHeader()->setVisible(false);
        }
        else{
            QMessageBox::warning(this,"Falha na Busca","Busca não realizada");
        }
    }
}

void pg_gestao_estoque::on_tw_produtos_itemSelectionChanged()
{
    // atribuir o id de acordo com o selecionado
    int id = ui->tw_produtos->item(ui->tw_produtos->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_produtos WHERE id_produto="+QString::number(id));
    if(query.exec())
    {
        // preencher os campos de acordo com o retorno da busca
        query.first();
        ui->campo_codigo2->setText(query.value(0).toString());
        ui->campo_produto2->setText(query.value(1).toString());
        ui->campo_fornecedor2->setText(query.value(2).toString());
        ui->campo_quantidade2->setText(query.value(3).toString());
        ui->campo_valor_compra2->setText(query.value(4).toString());
        ui->campo_valor_venda2->setText(query.value(5).toString());
    }
}


void pg_gestao_estoque::on_btn_salvar2_clicked()
{
    if(ui->campo_codigo2->text() == ""){
        QMessageBox::warning(this,"Falha no Cadastro", "Nenhum produto selecionado");
    }
    else{
        // pegar o id pela tabela
        int id = ui->tw_produtos->item(ui->tw_produtos->currentRow(),0)->text().toInt();
        QString aux;
        QString prod = ui->campo_produto2->text();
        QString forn = ui->campo_fornecedor2->text();
        QString qtde = ui->campo_quantidade2->text();

        aux = ui->campo_valor_compra2->text();
        std::replace(aux.begin(),aux.end(),',','.');
        QString valor_compra = aux;

        aux = ui->campo_valor_venda2->text();
        std::replace(aux.begin(),aux.end(),',','.');
        QString valor_venda = aux;

        QSqlQuery query;
        query.prepare("UPDATE tb_produtos SET id_produto="+QString::number(id)+",produto='"+prod+"', "
            "id_fornecedor="+QString::number(forn.toInt())+", qtde_estoque="+QString::number(qtde.toInt())+","
            "valor_compra="+QString::number(valor_compra.toDouble())+",valor_venda="+QString::number(valor_venda.toDouble())+""
            " where id_produto="+QString::number(id));
        if(query.exec())
        {
            int linha = ui->tw_produtos->currentRow();
            ui->tw_produtos->item(linha,0)->setText(ui->campo_codigo2->text());
            ui->tw_produtos->item(linha,1)->setText(prod);

            QMessageBox::information(this, "Atualização Realizada", "Dados do produto foram alterados");
        }
        else{
            QMessageBox::warning(this,"Falha na Atualização", "Os dados não foram alterados");
        }
    }

}


void pg_gestao_estoque::on_btn_excluir_clicked()
{
    // verifica se há algo selecionado
    if(ui->campo_codigo2->text() == ""){
        QMessageBox::warning(this,"Falha na Exclusão", "Nenhum produto selecionado");
    }
    else{
        // confirma a exclusão do produto
        QMessageBox::StandardButton opcao = QMessageBox::question(this,"Deletar Produto","Você realmente deseja excluir o produto?",QMessageBox::Yes|QMessageBox::No);
        if(opcao == QMessageBox::Yes)
        {
            // obtem a linha do produto selecionado
            int linha = ui->tw_produtos->currentRow();
            int id = ui->tw_produtos->item(linha,0)->text().toInt();
            QSqlQuery query;
            query.prepare("DELETE FROM tb_produtos WHERE id_produto="+QString::number(id));
            if(query.exec())
            {
                // deleta a linha selecionada
                ui->tw_produtos->removeRow(linha);
                QMessageBox::information(this,"Produto Deletado","Produto foi deletado com sucesso");
            }
            else{
                QMessageBox::warning(this,"Falha na Exclusão", "O produto não foi removidos");
            }

        }
    }
}


void pg_gestao_estoque::on_btn_pesquisar_clicked()
{
    QString busca;
    funcoes_globais::Remover_Linhas(ui->tw_produtos);
    if(ui->campo_pesquisar->text() == ""){
        if(ui->filtro_cod_produto->isChecked())
        {
            busca = "SELECT id_produto, produto FROM tb_produtos ORDER BY id_produto";
        }
        else{
            busca = "SELECT id_produto, produto FROM tb_produtos ORDER by produto";
        }
    }
    else{
        if(ui->filtro_cod_produto->isChecked())
        {
            busca = "SELECT id_produto, produto FROM tb_produtos WHERE id_produto="+ui->campo_pesquisar->text()+" ORDER BY id_produto";
        }
        else{
            busca = "SELECT id_produto, produto FROM tb_produtos WHERE produto LIKE '%"+ui->campo_pesquisar->text()+"%' ORDER BY produto";
        }
    }
    int nlinhas = 0;
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec())
    {
        while(query.next())
        {
            // inserção das linhas na tabela
            ui->tw_produtos->insertRow(nlinhas);
            // definição do elemento para inserção
            ui->tw_produtos->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_produtos->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_produtos->setRowHeight(nlinhas,20);
            nlinhas++;
        }
    }
    else{
        QMessageBox::warning(this,"Falha na Busca", "Não foi possível filtrar os produtos");
    }
}

