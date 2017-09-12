#ifndef HTMLHIGHLIGHTER_H
#define HTMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class HtmlHighlighter : public QSyntaxHighlighter
{
public:
    HtmlHighlighter(QTextDocument *parent = 0);
};

#endif // HTMLHIGHLIGHTER_H
