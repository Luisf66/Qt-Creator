#ifndef PG_GESTAO_ESTOQUE_H
#define PG_GESTAO_ESTOQUE_H

#include <QDialog>
#include "Conexao.h"
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class pg_gestao_estoque;
}

class pg_gestao_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit pg_gestao_estoque(QWidget *parent = nullptr);
    ~pg_gestao_estoque();
    Conexao con;

private slots:
    void on_btn_novo_produto_clicked();

    void on_btn_salvar_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::pg_gestao_estoque *ui;
};

#endif // PG_GESTAO_ESTOQUE_H
