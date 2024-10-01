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
    QString data_atual = data.toString("dd/mm/yyyy");
    ui->data_atual_2->setText(data_atual);

    ui->tabela_vendas->horizontalHeader()->setVisible(true);
    ui->tabela_vendas->setColumnCount(6);
    QStringList cabecalho = {"ID", "Data", "Hora", "Colaborador", "Valor Total", "Tipo de Pagamento"};
    ui->tabela_vendas->setHorizontalHeaderLabels(cabecalho);
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
