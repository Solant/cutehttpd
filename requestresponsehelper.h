#ifndef REQUESTRESPONSEHELPER_H
#define REQUESTRESPONSEHELPER_H

#include <QString>
#include <QMap>
#include <QFile>

class RequestResponseHelper
{
public:
    RequestResponseHelper();
    static QMap<QString, QString> *getPostParams(QString &request);
    static QString composeJsonResponse(QString path, QStringList folders, QStringList files);
    static QString createHeader(QFile &file, QString &mimeType);

    static QString MIME_TYPE_IMAGE_PNG;
    static QString MIME_TYPE_TEXT_CSS;
    static QString MIME_TYPE_TEXT_HTML;
    static QString MIME_TYPE_APPLICATION_OCTET_STREAM;
};

#endif // REQUESTRESPONSEHELPER_H
