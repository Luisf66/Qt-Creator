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

private:
    Ui::pg_gestao_estoque *ui;
};

#endif // PG_GESTAO_ESTOQUE_H
