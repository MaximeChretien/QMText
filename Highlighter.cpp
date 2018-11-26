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

#include "Highlighter.hpp"

Highlighter::Highlighter()
{
    cpp = new CppHighlighter(0);
    /*css = new CssHighlighter(0);
    html = new HtmlHighlighter(0);
    java = new JavaHighlighter(0);
    php = new PhpHighlighter(0);*/
    python = new PythonHighlighter(0);
    /*shell = new ShellHighlighter(0);
    xml = new XmlHighlighter(0);*/
}

Highlighter::~Highlighter()
{
    delete cpp;
    /*delete css;
    delete html;
    delete java;
    delete php;*/
    delete python;
    /*delete shell;
    delete xml;*/
}

void Highlighter::changeHighlighter(QString type, QTextDocument *doc)
{
    disableAll();

    if(type == "cpp")
        cpp->setDocument(doc);
    /*else if(type == "css")
        css->setDocument(doc);
    else if(type == "html")
        html->setDocument(doc);
    else if(type == "java")
        java->setDocument(doc);
    else if(type == "php")
        php->setDocument(doc);*/
    else if(type == "python")
        python->setDocument(doc);
    /*else if(type == "shell")
        shell->setDocument(doc);
    else if(type == "xml")
        xml->setDocument(doc);*/
}

void Highlighter::disableAll()
{
    cpp->setDocument(0);
    /*css->setDocument(0);
    html->setDocument(0);
    java->setDocument(0);
    php->setDocument(0);*/
    python->setDocument(0);
    /*shell->setDocument(0);
    xml->setDocument(0);*/
}
