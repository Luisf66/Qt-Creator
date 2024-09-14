#ifndef JANELAEDITA_H
#define JANELAEDITA_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class janelaedita;
}

class janelaedita : public QDialog
{
    Q_OBJECT

public:
    explicit janelaedita(QWidget *parent = nullptr, int id_contato = 0);
    ~janelaedita();

private slots:
    void on_btn_salvar_clicked();

private:
    Ui::janelaedita *ui;
};

#endif // JANELAEDITA_H
