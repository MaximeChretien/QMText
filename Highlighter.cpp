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
