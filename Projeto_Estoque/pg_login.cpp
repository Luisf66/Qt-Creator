#include "pg_login.h"
#include "ui_pg_login.h"

pg_login::pg_login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pg_login)
{
    ui->setupUi(this);
}

pg_login::~pg_login()
{
    delete ui;
}
