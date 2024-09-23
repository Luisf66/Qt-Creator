#ifndef PG_EDITAR_PRODUTO_VENDA_H
#define PG_EDITAR_PRODUTO_VENDA_H

#include <QDialog>

#include "pg_nova_venda.h"
namespace Ui {
class pg_editar_produto_venda;
}

class pg_editar_produto_venda : public QDialog
{
    Q_OBJECT

public:
    explicit pg_editar_produto_venda(QWidget *parent = nullptr);
    ~pg_editar_produto_venda();

private slots:
    void on_btn_confirmar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::pg_editar_produto_venda *ui;
};

#endif // PG_EDITAR_PRODUTO_VENDA_H
