#ifndef PHPHIGHLIGHTER_H
#define PHPHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class PhpHighlighter : public QSyntaxHighlighter
{
public:
    PhpHighlighter(QTextDocument *parent = 0);
};

#endif // PHPHIGHLIGHTER_H
