#ifndef PG_GESTAO_ESTOQUE_H
#define PG_GESTAO_ESTOQUE_H

#include <QDialog>

namespace Ui {
class pg_gestao_estoque;
}

class pg_gestao_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit pg_gestao_estoque(QWidget *parent = nullptr);
    ~pg_gestao_estoque();

private slots:
    void on_btn_novo_produto_clicked();

    void on_btn_salvar_clicked();

private:
    Ui::pg_gestao_estoque *ui;
};

#endif // PG_GESTAO_ESTOQUE_H
