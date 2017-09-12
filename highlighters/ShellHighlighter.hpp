#ifndef SHELLHIGHLIGHTER_H
#define SHELLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class ShellHighlighter : public QSyntaxHighlighter
{
public:
    ShellHighlighter(QTextDocument *parent = 0);
};

#endif // SHELLHIGHLIGHTER_H
