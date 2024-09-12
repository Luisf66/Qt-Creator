#ifndef JANELAPESQUISA_H
#define JANELAPESQUISA_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class janelapesquisa;
}

class janelapesquisa : public QDialog
{
    Q_OBJECT

public:
    explicit janelapesquisa(QWidget *parent = nullptr);
    ~janelapesquisa();

private slots:
    void on_btn_excluir_clicked();

private:
    Ui::janelapesquisa *ui;
};

#endif // JANELAPESQUISA_H
