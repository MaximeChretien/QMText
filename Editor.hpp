#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QStandardPaths>

class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0, QString path = "");

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    bool getSaveState();
    QString getFilePath();
    QString getFileTypes();

public slots:
    void setSaveState(bool state = false);
    void setFilePath(QString newPath = "");
    void save();
    void printFile();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);


private:
    QWidget *lineNumberArea;
    bool saveState; //true = save, false = not save
    QString filePath;
    QString fileTypes = tr("All Files (*);; Text Files (*.txt);; C Files (*.c);; C++ Files (*.cpp);; Header Files (*.h);; Java Files (*.java);; HTML Files (*.html);; CSS Files (*.css);; PHP Files (*.php);; Javascript Files (*.js);; XML Files (*.xml);; Python Scripts (*.py);; Batch Scripts (*.bat);; Shell Scripts (*.sh)");

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