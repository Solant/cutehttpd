#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    Controller(qintptr descr, QString absolutePath);
    ~Controller();
signals:
    void handle();

public slots:
};

#endif // CONTROLLER_H
