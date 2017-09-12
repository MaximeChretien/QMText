#ifndef CSSHIGHLIGHTER_H
#define CSSHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class CssHighlighter : public QSyntaxHighlighter
{
public:
    CssHighlighter(QTextDocument *parent = 0);
};

#endif // CSSHIGHLIGHTER_H
