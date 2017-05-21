#include "Tab.h"

Tab::Tab(QWidget *parent, QFont font) : QTabWidget(parent)
{
    setTabsClosable(true);
    setMovable(true);
    textFont = font;
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

void Tab::addNewTab(QString filePath)
{
    Editor *textZone = new Editor(this, filePath);

    addTab(textZone, getTitle(true, filePath)[0]);
    textZone->setFont(textFont);
    setCurrentIndex(count()-1);
    connect(textZone, SIGNAL(textChanged()), this, SLOT(changeTitle()));
}

void Tab::closeTab(int index)
{
    if (count() > 1)
    {
        int id = currentIndex();
        int correctPosition = 0;
        if(id>index)
        {
            correctPosition = 1;
        }
        setCurrentIndex(index);
        if(!getCurrentEditor()->getSaveState())
        {
            switch (saveMessageBox())
            {
                case QMessageBox::Save:
                    save();
                    id = id - correctPosition;
                    removeTab(index);
                    break;
                case QMessageBox::No:
                    id = id - correctPosition;
                    removeTab(index);
                    break;
                case QMessageBox::Cancel:

                    break;
                default:
                     //can't go here
                     break;
            }
        }
        else
        {
            id = id - correctPosition;
            removeTab(index);
        }
        setCurrentIndex(id);
    }
    else
    {
       parentWidget()->close();
    }
}

void Tab::save()
{
    if(getCurrentEditor()->getFilePath().isEmpty())
    {
        saveAs();
    }
    else
    {
        getCurrentEditor()->save();
        changeTitle();
    }
}

void Tab::saveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), getCurrentEditor()->getFileTypes());

    if(!filePath.isEmpty()) // test if dialog cancelled
    {
        getCurrentEditor()->setFilePath(filePath);
        getCurrentEditor()->save();
        changeTitle();
    }
}

void Tab::setFont(QFont newFont)
{
    textFont = newFont;
    for(int i=0; i<count(); i++)
    {
        widget(i)->setFont(textFont);
    }
}

QFont Tab::getFont()
{
    return textFont;
}

QStringList Tab::getTitle(bool newTab, QString path)
{
    QString name = path.section("/", -1, -1); //get file name
    QString file = path;
    #ifdef WIN32 //change path format for windows
    file.replace("/", "\\"); // change "/" to "\"
    #endif

    if (name.isEmpty())
    {
        name = tr("Untitled"); // if file don't exist, set name to Untitled
        file = name;
    }

    if(!newTab)
    {
        if(!getCurrentEditor()->getSaveState())
        {
            name = "* " + name; // si non sauvegardé, ajout de "*" au debut
            file = "* " + file;
        }

    }

    QStringList list = {name, file};
    return list;
}

void Tab::changeTitle()
{
        setTabText(currentIndex(),getTitle(false, getCurrentEditor()->getFilePath())[0]);
        emit currentChanged(currentIndex());
}

Editor *Tab::getCurrentEditor()
{
    return (Editor*)currentWidget();
}

//transmit command to current editor
void Tab::copy()
{
    getCurrentEditor()->copy();
}

void Tab::paste()
{
    getCurrentEditor()->paste();
}

void Tab::cut()
{
    getCurrentEditor()->cut();
}

void Tab::undo()
{
    getCurrentEditor()->undo();
}

void Tab::redo()
{
    getCurrentEditor()->redo();
}

void Tab::printFile()
{
    getCurrentEditor()->printFile();
}

int Tab::saveMessageBox()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/icons/icon.ico"));
    msgBox.setText(tr("This document has been modified."));
    msgBox.setInformativeText(tr("Would you save changes ?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec();
}
