#ifndef PG_LOGIN_H
#define PG_LOGIN_H

#include <QDialog>
#include <QMessageBox>

#include "Conexao.h"
#include "pg_principal.h"
#include "variaveis_globais.h"
namespace Ui {
class pg_login;
}

class pg_login : public QDialog
{
    Q_OBJECT

public:
    explicit pg_login(QWidget *parent = nullptr);
    ~pg_login();
    bool logado;
    Conexao con;
    QString nome, acesso;
    int id;
private slots:
    void on_btn_login_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::pg_login *ui;
};

#endif // PG_LOGIN_H
