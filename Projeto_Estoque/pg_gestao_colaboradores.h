#ifndef PG_GESTAO_COLABORADORES_H
#define PG_GESTAO_COLABORADORES_H

#include <QDialog>
#include <QtSql>

#include "Conexao.h"

namespace Ui {
class pg_gestao_colaboradores;
}

class pg_gestao_colaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit pg_gestao_colaboradores(QWidget *parent = nullptr);
    ~pg_gestao_colaboradores();
    Conexao con;

private slots:
    void on_btn_salvar_novo_clicked();

    void on_btn_cancelar_novo_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tabela_gestao_colab_itemSelectionChanged();

private:
    Ui::pg_gestao_colaboradores *ui;
};

#endif // PG_GESTAO_COLABORADORES_H
