#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>

class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(Editor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    Editor *codeEditor;
};

#endif // EDITOR_H
