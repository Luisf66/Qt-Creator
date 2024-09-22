#ifndef PG_NOVA_VENDA_H
#define PG_NOVA_VENDA_H

#include <QDialog>
#include <QMessageBox>
#include "Conexao.h"
#include <QTableWidget>

namespace Ui {
class pg_nova_venda;
}

class pg_nova_venda : public QDialog
{
    Q_OBJECT

public:
    explicit pg_nova_venda(QWidget *parent = nullptr);
    ~pg_nova_venda();
    void Limpar_campos();
    double Calcula_Total(QTableWidget *tw, int coluna);

    Conexao con;
    int nlinhas;

private slots:
    void on_campo_cod_produto_returnPressed();

    void on_btn_excluir_produto_clicked();

private:
    Ui::pg_nova_venda *ui;
};

#endif // PG_NOVA_VENDA_H
