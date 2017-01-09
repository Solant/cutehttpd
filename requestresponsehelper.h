#ifndef REQUESTRESPONSEHELPER_H
#define REQUESTRESPONSEHELPER_H

#include <QFile>
#include <QMap>
#include <QMimeDatabase>
#include <QString>

class RequestResponseHelper
{
private:
    static QMimeDatabase m_database;

public:
    static QByteArray composeJsonResponse(QString path, QStringList folders,
                                          QStringList files);
    static QString createHeader(QFile &file, QString mimeType,
                                bool addContentDisposition = false,
                                bool addAcceptRanges = false);
    static QString detectMimeType(QString fileName);
    static QMap<QString, QString> *getParameters(QString &url);

    static QString MIME_TYPE_TEXT_HTML;
    static QString MIME_TYPE_APPLICATION_OCTET_STREAM;
    static QString getMimeType(QString path);
    static QByteArray createJsonHeader(int contentLength);
};

#endif // REQUESTRESPONSEHELPER_H
