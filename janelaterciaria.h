#ifndef JANELATERCIARIA_H
#define JANELATERCIARIA_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

#include "janelacontatos.h"
#include "janelapesquisa.h"

namespace Ui {
class janelaterciaria;
}

class janelaterciaria : public QDialog
{
    Q_OBJECT

public:
    explicit janelaterciaria(QWidget *parent = nullptr);
    ~janelaterciaria();

private slots:
    void on_pushButton_clicked();

    void on_btn_link_clicked();
    void on_btn_login_clicked();

    void on_btn_add_contato_clicked();

    void on_btn_ler_contato_clicked();

private:
    Ui::janelaterciaria *ui;
};

#endif // JANELATERCIARIA_H
