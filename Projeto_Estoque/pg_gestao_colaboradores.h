#ifndef PG_GESTAO_COLABORADORES_H
#define PG_GESTAO_COLABORADORES_H

#include <QDialog>

namespace Ui {
class pg_gestao_colaboradores;
}

class pg_gestao_colaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit pg_gestao_colaboradores(QWidget *parent = nullptr);
    ~pg_gestao_colaboradores();

private:
    Ui::pg_gestao_colaboradores *ui;
};

#endif // PG_GESTAO_COLABORADORES_H
