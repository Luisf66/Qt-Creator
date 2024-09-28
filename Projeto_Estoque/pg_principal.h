#ifndef PG_PRINCIPAL_H
#define PG_PRINCIPAL_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>

#include "pg_login.h"
#include "pg_nova_venda.h"
#include "pg_gestao_colaboradores.h"
#include "pg_gestao_estoque.h"
#include "pg_gestao_vendas.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class pg_principal;
}
QT_END_NAMESPACE

class pg_principal : public QMainWindow
{
    Q_OBJECT

public:
    pg_principal(QWidget *parent = nullptr);
    ~pg_principal();
    QIcon cadFechado;
    QIcon cadAberto;

private slots:
    void on_btn_bloquear_clicked();

    void on_btn_nova_venda_clicked();

    void on_actionEstoque_triggered();

    void on_actionColaboradores_triggered();

    void on_actionVendas_triggered();

private:
    Ui::pg_principal *ui;
};
#endif // PG_PRINCIPAL_H
