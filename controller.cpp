#include "client.h"
#include "controller.h"

#include <QCoreApplication>

Controller::Controller(qintptr descr, QString absolutePath)
{
    QThread *thread = new QThread;
    Client *client = new Client(descr, absolutePath);
    client->moveToThread(thread);

    // Start client work on thread start
    connect(thread, SIGNAL(started()), client, SLOT(handleRequest()));

    // Connect client finished signal to trigger thread quit, then delete.
    connect(client, SIGNAL(finished()), thread, SLOT(quit()));
    connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
    connect(client, SIGNAL(finished()), this, SLOT(deleteLater()));

    // Make sure the thread object is deleted after execution has finished.
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
