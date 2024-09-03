#ifndef JANELASECUNDARIA_H
#define JANELASECUNDARIA_H

#include <QDialog>

namespace Ui {
class JanelaSecundaria;
}

class JanelaSecundaria : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaSecundaria(QWidget *parent = nullptr);
    ~JanelaSecundaria();

private slots:
    void on_Mudar_Imagem_clicked();

private:
    Ui::JanelaSecundaria *ui;
};

#endif // JANELASECUNDARIA_H
