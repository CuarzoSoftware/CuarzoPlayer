#ifndef REPLY_H
#define REPLY_H

#include <QNetworkReply>

class Reply : public QObject
{
    Q_OBJECT

public:

    int _id;

    Reply(int id, QNetworkReply *net){
        _id = id;
        connect(net,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(progress(qint64,qint64)));
    }


signals:

    void percentReady(int percent,int id);

public slots:

    void progress(qint64 up,qint64 to){
        float per = (float)100/(float)to*(float)up;
        percentReady((int)per,_id);
    }

};

#endif
