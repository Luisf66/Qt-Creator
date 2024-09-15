#ifndef PG_PRINCIPAL_H
#define PG_PRINCIPAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class pg_principal;
}
QT_END_NAMESPACE

class pg_principal : public QMainWindow
{
    Q_OBJECT

public:
    pg_principal(QWidget *parent = nullptr);
    ~pg_principal();
    QIcon cadFechado;
    QIcon cadAberto;
    bool bloqueado;


private slots:
    void on_btn_bloquear_clicked();

private:
    Ui::pg_principal *ui;
};
#endif // PG_PRINCIPAL_H
