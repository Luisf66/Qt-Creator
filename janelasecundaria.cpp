#include "janelasecundaria.h"
#include "ui_janelasecundaria.h"

JanelaSecundaria::JanelaSecundaria(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JanelaSecundaria)
{
    ui->setupUi(this);
}

JanelaSecundaria::~JanelaSecundaria()
{
    delete ui;
}
