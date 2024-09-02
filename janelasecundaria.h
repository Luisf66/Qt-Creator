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

private:
    Ui::JanelaSecundaria *ui;
};

#endif // JANELASECUNDARIA_H
