#include "pg_gestao_vendas.h"
#include "ui_pg_gestao_vendas.h"
#include <QDateTime>

pg_gestao_vendas::pg_gestao_vendas(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_gestao_vendas)
{
    ui->setupUi(this);

    if(con.conectar())
    {
        qDebug() << "Banco já conectado";
    }
    else{
        con.conectar();
    }

    QTime tempo = QTime::currentTime();
    QString tempo_atual = tempo.toString("hh:mm:ss");
    ui->data_atual->setText(tempo_atual);
    QDate data = QDate::currentDate();
    QString data_atual = data.toString("dd/MM/yyyy");
    ui->data_atual_2->setText(data_atual);

    // tabela produtos venda
    ui->tabela_produtos_venda->horizontalHeader()->setVisible(true);
    ui->tabela_produtos_venda->setColumnCount(5);
    QStringList cabecalho_prod_venda = {"ID", "Produto", "Quantidade", "Valor Uni", "Valor Total"};
    ui->tabela_produtos_venda->setHorizontalHeaderLabels(cabecalho_prod_venda);
    ui->tabela_produtos_venda->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabela_produtos_venda->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tabela_produtos_venda->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabela_produtos_venda->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // tabela vendas
    ui->tabela_vendas->horizontalHeader()->setVisible(true);
    ui->tabela_vendas->setColumnCount(6);
    QStringList cabecalho_venda = {"ID", "Data", "Hora", "Colaborador", "Valor Total", "Tipo de Pagamento"};
    ui->tabela_vendas->setHorizontalHeaderLabels(cabecalho_venda);
    ui->tabela_vendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabela_vendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tabela_vendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabela_vendas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int nlinhas = 0;
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_vendas");
    if(query.exec())
    {
        query.first();
        do
        {
            ui->tabela_vendas->insertRow(nlinhas);
            ui->tabela_vendas->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tabela_vendas->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tabela_vendas->setItem(nlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tabela_vendas->setItem(nlinhas,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tabela_vendas->setItem(nlinhas,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tabela_vendas->setItem(nlinhas,5,new QTableWidgetItem(query.value(5).toString()));

            nlinhas++;
        }while (query.next());
        con.desconectar();
    }
    else{
        QMessageBox::warning(this,"Falha na Conexão", "Não foi possível se conectar ao banco");
    }

}

pg_gestao_vendas::~pg_gestao_vendas()
{
    delete ui;
}

void pg_gestao_vendas::on_tabela_vendas_itemSelectionChanged()
{
    //ui->tabela_produtos_venda->clear();
    ui->tabela_produtos_venda->setRowCount(0);
    QString id = ui->tabela_vendas->item(ui->tabela_vendas->currentRow(),0)->text();

    if(con.conectar())
    {
        qDebug() << "Banco já conectado";
    }
    else{
        con.conectar();
    }

    int nlinhas = 0;
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_produtosVendas WHERE id_venda = "+id);
    if(query.exec())
    {
        query.first();
        do
        {
            ui->tabela_produtos_venda->insertRow(nlinhas);
            ui->tabela_produtos_venda->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tabela_produtos_venda->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tabela_produtos_venda->setItem(nlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tabela_produtos_venda->setItem(nlinhas,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tabela_produtos_venda->setItem(nlinhas,4,new QTableWidgetItem(query.value(4).toString()));

            nlinhas++;
        }while (query.next());
        con.desconectar();
    }
    else{
        qDebug() << "Falha na Query: " << query.lastError().text();
        QMessageBox::warning(this,"Falha na Operação", "Não foi possível exibir os resultados");
    }
}


void pg_gestao_vendas::on_btn_filtrar_clicked()
{
    ui->tabela_vendas->setRowCount(0);

    if(con.conectar())
    {
        qDebug() << "Banco já conectado";
    }
    else{
        con.conectar();
    }

    int nlinhas = 0;
    QSqlQuery query;
    query.prepare("SELECT * FROM tb_vendas WHERE data_venda BETWEEN '"+ui->de_inicial->text()+"' AND '"+ui->de_final->text()+"'");
    if(query.exec())
    {
        query.first();
        do
        {
            ui->tabela_vendas->insertRow(nlinhas);
            ui->tabela_vendas->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tabela_vendas->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tabela_vendas->setItem(nlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tabela_vendas->setItem(nlinhas,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tabela_vendas->setItem(nlinhas,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tabela_vendas->setItem(nlinhas,5,new QTableWidgetItem(query.value(5).toString()));

            nlinhas++;
            // qDebug() << "Data I: " << ui->de_inicial->text();
            // qDebug() << "Data F: " << ui->de_final->text();
        }while (query.next());
        con.desconectar();
    }
    else{
        qDebug() << "Falha na Query: " << query.lastError().text();
        QMessageBox::warning(this,"Falha na Operação", "Não foi possível exibir os resultados");
    }
}


void pg_gestao_vendas::on_btn_pdf_clicked()
{
    QString nome_arquivo = QDir::currentPath() + "/" + ui->tabela_vendas->item(ui->tabela_vendas->currentRow(),0)->text() + "_vendas.pdf";
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nome_arquivo);

    QPainter painter;
    if(!painter.begin(&printer))
    {
        qDebug() << "Falha na Abetura do PDF";
        return;
    }

    int linha = 200;
    int salto = 20;

    painter.drawText(25,25,"Data: " + ui->tabela_vendas->item(ui->tabela_vendas->currentRow(),1)->text());
    painter.drawText(25,50,"Hora: " + ui->tabela_vendas->item(ui->tabela_vendas->currentRow(),2)->text());
    painter.drawText(25,75,"Colaborador: " + ui->tabela_vendas->item(ui->tabela_vendas->currentRow(),3)->text());
    painter.drawText(25,100,"Valor Total: " + ui->tabela_vendas->item(ui->tabela_vendas->currentRow(),4)->text());
    painter.drawText(25,125,"Pagamento: " + ui->tabela_vendas->item(ui->tabela_vendas->currentRow(),5)->text());

    painter.end();

    QDesktopServices::openUrl(QUrl("file:///"+nome_arquivo));
}

