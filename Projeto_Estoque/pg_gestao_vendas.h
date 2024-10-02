#ifndef PG_GESTAO_VENDAS_H
#define PG_GESTAO_VENDAS_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include "Conexao.h"

namespace Ui {
class pg_gestao_vendas;
}

class pg_gestao_vendas : public QDialog
{
    Q_OBJECT

public:
    explicit pg_gestao_vendas(QWidget *parent = nullptr);
    ~pg_gestao_vendas();
    Conexao con;

private slots:
    void on_tabela_vendas_itemSelectionChanged();

    void on_btn_filtrar_clicked();

private:
    Ui::pg_gestao_vendas *ui;
};

#endif // PG_GESTAO_VENDAS_H
