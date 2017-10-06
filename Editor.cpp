#include "Editor.hpp"

Editor::Editor(QWidget *parent, QString path) : QPlainTextEdit(parent)
{
    filePath = path;
    syntax = "plain";

    //Editor properties
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setFrameStyle(QFrame::NoFrame);
    setAcceptDrops(false);
    setTabStopWidth(40);

    lineNumberArea = new LineNumberArea(this);

    //Update and scroll line counter
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

    connect(this->document(), SIGNAL(modificationChanged(bool)), this->document(), SLOT(setModified(bool)));
    connect(this->document(), SIGNAL(contentsChanged()), this, SLOT(ifEmpty()));

    //update highlight when it's needed
    connect(this->document(), SIGNAL(modificationChanged(bool)), this, SLOT(updateHighlight()));
    connect(this, SIGNAL(updateRequest(const QRect&, int)), this, SLOT(updateHighlight(const QRect&, int)));

    updateLineNumberAreaWidth(0);

    if(!filePath.isEmpty())
    {
        QFile fichier(filePath);
        fichier.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream flux(&fichier);

        setPlainText(flux.readAll());
    }
    document()->setModified(false);
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

void Editor::ifEmpty()
{
    if(filePath.isEmpty() && this->document()->isEmpty())
            document()->setModified(false);
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
        document()->setModified(false);
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

QString Editor::getSyntax()
{
    return syntax;
}

void Editor::setSyntax(QString type)
{
    syntax = type;
}

void Editor::findString(QString text)
{   
    findAllStrings(text); //highlight all matching strings

    //if nothing find, go to the beginning of the file and try to find the string
    if(!find(text, QTextDocument::FindFlags()))
    {
        QTextCursor cursor(textCursor());
        cursor.movePosition(QTextCursor::Start);
        setTextCursor(cursor);
        find(text, QTextDocument::FindFlags());
    }
}

void Editor::findAllStrings(QString text)
{
    if(text != findAllText)
    {
        extraSelections = QList<QTextEdit::ExtraSelection>();
    }
    findAllText = text;
    updateHighlight(QRect(), 1);
}

void Editor::replace(QString findText, QString replaceText)
{
    QTextCursor cursorReplace(textCursor());
    if (cursorReplace.hasSelection())
        cursorReplace.insertText(replaceText);

    findAllStrings(findText); //highlight all matching strings

    //if nothing find, go to the beginning of the file and try to find the string
    if(!find(findText, QTextDocument::FindFlags()))
    {
        QTextCursor cursor(textCursor());
        cursor.movePosition(QTextCursor::Start);
        setTextCursor(cursor);
        find(findText, QTextDocument::FindFlags());
    }
}

void Editor::replaceAll(QString findText, QString replaceText)
{
    QTextDocument::FindFlags flags;
    if (document())
    {
        QTextCursor cursor(document());
        cursor.movePosition(QTextCursor::Start);

        while (! cursor.isNull())
        {
            cursor = document() -> find(findText, cursor, flags);
            if(cursor.hasSelection())
                cursor.insertText(replaceText);
        }
    }
}

void Editor::highlight(const QString &txt, int start, int end) //Highlight for FindAllStrings function
{
    QTextDocument::FindFlags flags;
    if (document())
    {
        QColor color(Qt::lightGray);

        QTextCursor cursor(document());
        cursor.setPosition(start);
        cursor = document() -> find(txt, cursor, flags);

        while (! cursor.isNull())
        {
            if (cursor.position() > end)
            {
                break;
            }
            QTextEdit::ExtraSelection extra;
            extra.format.setBackground(color);
            extra.cursor = cursor;
            extraSelections.append(extra);

            cursor = document() -> find(txt, cursor, flags);
        }
        setExtraSelections(extraSelections);
    }

}


void Editor::updateHighlight(const QRect& rect, int dy) //update highlight only on the text we see
{
    if (dy != 0)
    {
         QTextCursor cursor = cursorForPosition(QPoint(0, 0));
         QPoint pageY = viewport() ? QPoint(viewport() -> width() - 1, viewport() -> height() - 1) : QPoint(0, 0);
         highlight(findAllText, cursor.position(), cursorForPosition(pageY).position());
    }
}

void Editor::updateHighlight()
{
    extraSelections = QList<QTextEdit::ExtraSelection>();
    updateHighlight(QRect(), 1);
}
