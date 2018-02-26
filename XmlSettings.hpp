#ifndef XMLSETTINGS_HPP
#define XMLSETTINGS_HPP

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

class XmlSettings
{
public:
    XmlSettings(QString file);
    QStringList read();
    void write(QStringList configData);

private:
    QXmlStreamReader *xmlReader;
    QXmlStreamWriter *xmlWriter;
    QString fileName;
};

#endif // XMLSETTINGS_HPP
