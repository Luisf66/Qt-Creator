#ifndef PG_LOGIN_H
#define PG_LOGIN_H

#include <QDialog>
#include <QMessageBox>

#include "Conexao.h"

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


private slots:
    void on_btn_login_clicked();

private:
    Ui::pg_login *ui;
};

#endif // PG_LOGIN_H
