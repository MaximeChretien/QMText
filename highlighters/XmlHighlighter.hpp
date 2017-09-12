#ifndef XMLHIGHLIGHTER_H
#define XMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class XmlHighlighter : public QSyntaxHighlighter
{
public:
    XmlHighlighter(QTextDocument *parent = 0);
};

#endif // XMLHIGHLIGHTER_H
