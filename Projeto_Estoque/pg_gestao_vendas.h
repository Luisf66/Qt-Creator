#ifndef PG_GESTAO_VENDAS_H
#define PG_GESTAO_VENDAS_H

#include <QDialog>

namespace Ui {
class pg_gestao_vendas;
}

class pg_gestao_vendas : public QDialog
{
    Q_OBJECT

public:
    explicit pg_gestao_vendas(QWidget *parent = nullptr);
    ~pg_gestao_vendas();

private:
    Ui::pg_gestao_vendas *ui;
};

#endif // PG_GESTAO_VENDAS_H
