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
    void imprimer();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);


private:
    QWidget *lineNumberArea;
    bool saveState; //true = save, false = not save
    QString filePath;
    QString fileTypes = "Tous les fichiers (*);; Fichiers texte (*.txt);; Fichiers C (*.c);; Fichiers C++ (*.cpp);; Fichiers Header (*.h);; Fichiers Java (*.java);; Fichiers HTML (*.html);; Fichiers CSS (*.css);; Fichiers PHP (*.php);; Fichiers Javascript (*.js);; Fichiers SQL (*.sql);; Fichiers XML (*.xml);; Scripts Python (*.py);; Scripts Batch (*.bat);; Scripts Shell (*.sh)"; //differents type de fichier gérés (totalement non exhaustif)

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
