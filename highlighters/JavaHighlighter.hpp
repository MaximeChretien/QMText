#ifndef JAVAHIGHLIGHTER_H
#define JAVAHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class JavaHighlighter : public QSyntaxHighlighter
{
public:
    JavaHighlighter(QTextDocument *parent = 0);
};

#endif // JAVAHIGHLIGHTER_H
