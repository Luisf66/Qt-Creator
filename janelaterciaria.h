#ifndef JANELATERCIARIA_H
#define JANELATERCIARIA_H

#include <QDialog>

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

private:
    Ui::janelaterciaria *ui;
};

#endif // JANELATERCIARIA_H
