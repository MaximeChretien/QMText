#include "XmlSettings.hpp"

XmlSettings::XmlSettings(QString file)
{
    fileName = file;
    xmlReader = new QXmlStreamReader();
    xmlWriter = new QXmlStreamWriter();

    xmlWriter->setAutoFormatting(true);
}

XmlSettings::~XmlSettings()
{
    delete xmlReader;
    delete xmlWriter;
}

QStringList XmlSettings::read()
{
    QStringList configData({0,0,0,0});
    QFile file(fileName);
    file.open((QFile::ReadOnly | QIODevice::Text));
    xmlReader->setDevice(&file);

    if (xmlReader->readNextStartElement())
    {
        if (xmlReader->name() == "config")
        {
            while(xmlReader->readNextStartElement())
            {
                if(xmlReader->name() == "font")
                    configData[0] = xmlReader->readElementText();
                else if(xmlReader->name() == "size")
                    configData[1] = xmlReader->readElementText();
                else if(xmlReader->name() == "language")
                    configData[2] = xmlReader->readElementText();
                else if(xmlReader->name() == "theme")
                    configData[3] = xmlReader->readElementText();
                else
                    xmlReader->skipCurrentElement();
            }
        }
    }
    file.close();
    return configData;
}

void XmlSettings::write(QStringList configData)
{
    QStringList config({"font","size","language","theme"});
    QFile file(fileName);
    file.open((QFile::WriteOnly | QIODevice::Text));
    file.resize(0);
    xmlWriter->setDevice(&file);

    xmlWriter->writeStartDocument();
    xmlWriter->writeStartElement("config");
    for(int i=0;i<config.size();i++)
    {
        xmlWriter->writeTextElement(config[i],configData[i]);
    }
    xmlWriter->writeEndElement();
    xmlWriter->writeEndDocument();
    file.close();
}
