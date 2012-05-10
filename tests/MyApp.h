#ifndef MYAPP_H
#define MYAPP_H

#include <Soca/Com/ClientLoop.h>
#include <QObject>

/**
*/
class MyApp : public QObject {
    Q_OBJECT
public:

private slots:
    virtual void onload( Model *m ) {
        qDebug() << m;
    }
};

#endif // MYAPP_H
