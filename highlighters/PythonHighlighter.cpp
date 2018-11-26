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

#include "PythonHighlighter.hpp"

PythonHighlighter::PythonHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::red);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bfinally\\b" << "\\bis\\b" << "\\breturn\\b" << "\\bcontinue\\b" << "\\blambda\\b" << "\\bdef\\b" << "\\bfrom\\b" << "\\bnonlocal\\b" << "\\bdel\\b" << "\\bglobal\\b" << "\\bwith\\b" << "\\bas\\b" << "\\byield\\b" << "\\bassert\\b" << "\\bimport\\b" << "\\bpass\\b" << "\\bbreak\\b" << "\\bexcept\\b" << "\\braise\\b" << "\\bor\\b" << "\\bin\\b" << "\\belif\\b" << "\\bif\\b" << "\\belse\\b" << "\\bnot\\b" << "\\bwhile\\b" << "\\band\\b" << "\\btry\\b" << "\\bTrue\\b" << "\\bfor\\b" << "\\bNone\\b" << "\\bFalse\\b";
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);

    }

    varFormat.setForeground(Qt::cyan);
    varFormat.setFontWeight(QFont::Bold);
    QStringList varPatterns;
    varPatterns << "\\bclass\\b" << "\\bbool\\b" << "\\bcomplex\\b" << "\\bfloat\\b" << "\\bint\\b" << "\\blong\\b" << "\\bshort\\b" << "\\bstr\\b" << "\\bvoid\\b" << "\\bunsigned\\b";
    foreach (const QString &pattern, varPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = varFormat;
        highlightingRules.append(rule);

    }

    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("\#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::yellow);
    QStringList quotationPatterns;
    quotationPatterns << "\".*\"" << "'.*'" << "'''.*'''";
    foreach (const QString &pattern, quotationPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = quotationFormat;
        highlightingRules.append(rule);

    }

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::green);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::gray);
    commentStartExpression = QRegExp("\"\"\"");
    commentEndExpression = QRegExp("\"\"\"");
}

void PythonHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0)
    {

        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else
        {
            commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
