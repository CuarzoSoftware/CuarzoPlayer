#ifndef NETWORK_H
#define NETWORK_H
#include <QNetworkAccessManager>

class Network : public QNetworkAccessManager
{
    Q_OBJECT
public:

    QString call;

    Network(QString callback,QObject *parent){
        call = callback;
        setParent(parent);
        connect(this,SIGNAL(finished(QNetworkReply*)),this,SLOT(ready(QNetworkReply*)));
    }


signals:

    void finished(QNetworkReply*,QString);

public slots:

    void ready(QNetworkReply *res){

        finished(res,call);
    }

};

#endif // NETWORK_H
