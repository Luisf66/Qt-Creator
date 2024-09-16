#ifndef CONEXAO_H
#define CONEXAO_H

#include <QtSql>
#include <QMessageBox>
#include <QDebug>

class Conexao {
public:
    QSqlDatabase banco_db;
    Conexao(){
        banco_db = QSqlDatabase::addDatabase("QSQLITE");
    }
    bool conectar(){
        QString local = qApp->applicationDirPath();
        QString banco = local + "/DataBase/banco_de_dados.db";
        banco_db.setDatabaseName(banco); // definição do banco de dados

        if(!banco_db.open())
        {
            return false;

        }
        else{
            return true;
        }
    }
    void desconectar(){
        banco_db.close();
    }
};

#endif // CONEXAO_H
