#ifndef PG_NOVA_VENDA_H
#define PG_NOVA_VENDA_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>


#include "Conexao.h"
#include "pg_editar_produto_venda.h"

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

    static QString g_id_prod, g_prod, g_qtde, g_val_total, g_val_unitario;
    static bool edição;

private slots:
    void on_campo_cod_produto_returnPressed();

    void on_btn_excluir_produto_clicked();

    void on_btn_editar_venda_clicked();

private:
    Ui::pg_nova_venda *ui;
};

#endif // PG_NOVA_VENDA_H
