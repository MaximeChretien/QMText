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
    ~Highlighter();

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
