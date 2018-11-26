/*
**  Copyright 2018 - Maxime Chretien (MixLeNain)
**
**  This file is part of QMText.
**
**  QMText is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  any later version.
**
**  QMText is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with QMText.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef XMLSETTINGS_HPP
#define XMLSETTINGS_HPP

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

class XmlSettings
{
public:
    XmlSettings(QString file);
    ~XmlSettings();
    QStringList read();
    void write(QStringList configData);

private:
    QXmlStreamReader *xmlReader;
    QXmlStreamWriter *xmlWriter;
    QString fileName;
};

#endif // XMLSETTINGS_HPP
