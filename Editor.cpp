#include "Editor.h"

Editor::Editor(QWidget *parent, QString path) : QPlainTextEdit(parent)
{
    filePath = path;

    setLineWrapMode(QPlainTextEdit::NoWrap);
    setFrameStyle(QFrame::NoFrame);
    setAcceptDrops(false);

    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

    connect(this, SIGNAL(textChanged()), this, SLOT(setSaveState()));

    updateLineNumberAreaWidth(0);

    if(!filePath.isEmpty())
    {
        QFile fichier(filePath);
        fichier.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream flux(&fichier);

        setPlainText(flux.readAll());
    }
    setSaveState(true);
}

int Editor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void Editor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void Editor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= event->rect().bottom())
    {
            if (block.isVisible() && bottom >= event->rect().top())
            {
                QString number = QString::number(blockNumber + 1);
                painter.setPen(Qt::black);
                painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignCenter, number);
            }

            block = block.next();
            top = bottom;
            bottom = top + (int) blockBoundingRect(block).height();
            ++blockNumber;
    }
}

void Editor::setSaveState(bool state)
{
    if(filePath.isEmpty() && this->toPlainText().isEmpty())
    {
        saveState = true;
    }
    else
    {
        saveState = state;
    }
}

bool Editor::getSaveState()
{
    return saveState;
}

void Editor::setFilePath(QString newPath)
{
    filePath = newPath;
}

QString Editor::getFilePath()
{
    return filePath;
}

void Editor::save()
{
        QFile saveFile(filePath);
        saveFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream flux(&saveFile);

        flux.setCodec("UTF-8");

        flux << toPlainText();
        setSaveState(true);
}

void Editor::printFile()
{
    QPrinter * printer = new QPrinter;
    QPrintDialog * dialog = new QPrintDialog(printer, this);

    if(dialog->exec() == QDialog::Accepted)//if ok, print file
        print(printer);

}

QString Editor::getFileTypes()
{
    return fileTypes;
}
