#ifndef CONEXAO_H
#define CONEXAO_H

#include <QtSql>
#include <QMessageBox>
#include <QDebug>

class Conexao {
public:
    QSqlDatabase banco_db;
    QString local;
    QString banco;
    Conexao(){
        local = qApp->applicationDirPath();
        banco = local + "/DataBase/banco_de_dados.db";
        banco_db = QSqlDatabase::addDatabase("QSQLITE");
    }

    bool conectar(){
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

    bool verifica_conexao(){
        if(banco_db.isOpen())
        {
            return true;
        }
        else{
            return false;
        }
    }
};

#endif // CONEXAO_H
