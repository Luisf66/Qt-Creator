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

    void on_pushButton_clicked();

    void on_btn_adicionar_clicked();

    void on_btn_marcar_clicked();

    void on_btn_desmarcar_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_btn_adicionar_tab_clicked();

    void on_btn_enviar_clicked();

private:
    Ui::JanelaSecundaria *ui;
};

#endif // JANELASECUNDARIA_H
