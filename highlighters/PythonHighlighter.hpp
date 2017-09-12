#ifndef PYTHONHIGHLIGHTER_H
#define PYTHONHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class PythonHighlighter : public QSyntaxHighlighter
{
public:
    PythonHighlighter(QTextDocument *parent = 0);
};

#endif // PYTHONHIGHLIGHTER_H
