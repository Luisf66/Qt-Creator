#ifndef JANELACONTATOS_H
#define JANELACONTATOS_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class janelacontatos;
}

class janelacontatos : public QDialog
{
    Q_OBJECT

public:
    explicit janelacontatos(QWidget *parent = nullptr);
    ~janelacontatos();

private slots:
    void on_btn_gravar_clicked();

private:
    Ui::janelacontatos *ui;
};

#endif // JANELACONTATOS_H
