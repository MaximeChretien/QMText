#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

//include all highlighters
#include "highlighters/CppHighlighter.hpp"
#include "highlighters/CssHighlighter.hpp"
#include "highlighters/HtmlHighlighter.hpp"
#include "highlighters/JavaHighlighter.hpp"
#include "highlighters/PhpHighlighter.hpp"
#include "highlighters/PythonHighlighter.hpp"
#include "highlighters/ShellHighlighter.hpp"
#include "highlighters/XmlHighlighter.hpp"

class Highlighter
{
public:
    Highlighter();

public slots:
    void changeHighlighter(QString type, QTextDocument *doc);

private:
    void disableAll();
    CppHighlighter *cpp;
    CssHighlighter *css;
    HtmlHighlighter *html;
    JavaHighlighter *java;
    PhpHighlighter *php;
    PythonHighlighter *python;
    ShellHighlighter *shell;
    XmlHighlighter *xml;
};

#endif // HIGHLIGHTER_H
