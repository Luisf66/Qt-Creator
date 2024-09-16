#ifndef PG_NOVA_VENDA_H
#define PG_NOVA_VENDA_H

#include <QDialog>

namespace Ui {
class pg_nova_venda;
}

class pg_nova_venda : public QDialog
{
    Q_OBJECT

public:
    explicit pg_nova_venda(QWidget *parent = nullptr);
    ~pg_nova_venda();

private:
    Ui::pg_nova_venda *ui;
};

#endif // PG_NOVA_VENDA_H
