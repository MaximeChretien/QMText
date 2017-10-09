#include "CppHighlighter.hpp"

CppHighlighter::CppHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::red);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bclass\\b" << "\\bconst\\b" << "\\benum\\b" << "\\bexplicit\\b" << "\\bfriend\\b" << "\\binline\\b" << "\\bnamespace\\b" << "\\boperator\\b" << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b" << "\\bsignals\\b" << "\\bsigned\\b" << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b" << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b" << "\\bunion\\b" << "\\busing\\b" << "\\bvirtual\\b" << "\\bvolatile\\b";
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);

    }

    varFormat.setForeground(Qt::cyan);
    varFormat.setFontWeight(QFont::Bold);
    QStringList varPatterns;
    varPatterns << "\\bbool\\b" << "\\bchar\\b" << "\\bdouble\\b" << "\\bfloat\\b" << "\\bint\\b" << "\\blong\\b" << "\\bshort\\b" << "\\bstring\\b" << "\\bvoid\\b" << "\\bunsigned\\b";
    foreach (const QString &pattern, varPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = varFormat;
        highlightingRules.append(rule);

    }

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    quotationFormat.setForeground(Qt::yellow);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::green);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    hashFormat.setFontItalic(true);
    hashFormat.setFontWeight(QFont::Bold);
    hashFormat.setForeground(Qt::magenta);
    rule.pattern = QRegExp("\#\\binclude");
    rule.format = hashFormat;
    highlightingRules.append(rule);

    includeFormat.setForeground(Qt::yellow);
    rule.pattern = QRegExp("<.*>");
    rule.format = includeFormat;
    highlightingRules.append(rule);

    testFormat.setForeground(Qt::red);
    QStringList testPatterns;
    testPatterns << "\\bif\\b" << "\\belse\\b" << "\\bwhile\\b" << "\\bdo\\b" << "\\bswitch\\b" << "\\bcase\\b" << "\\bbreak\\b" << "\\breturn\\b" << "\\bdefault\\b" << "\\bfor\\b";
    foreach (const QString &pattern, testPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = testFormat;
        highlightingRules.append(rule);

    }

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void CppHighlighter::highlightBlock(const QString &text)
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

