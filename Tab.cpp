/*
**  Copyright 2018 - Maxime Chretien (MixLeNain)
**
**  This file is part of QMText.
**
**  QMText is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  any later version.
**
**  QMText is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with QMText.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Tab.hpp"

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
    connect(textZone->document(), SIGNAL(modificationChanged(bool)), this, SLOT(changeTitle()));
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
        if(getCurrentEditor()->document()->isModified())
        {
            switch (saveMessageBox())
            {
                case QMessageBox::Save:
                    save();
                    id = id - correctPosition;
                    removeTab(index);
                    break;
                case QMessageBox::Discard:
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
       parentWidget()->parentWidget()->close(); //parentWidget of the parentWidget because there is a widget for the layout
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
    #ifdef WIN32 //change name format for windows
    name = name.section("\\", -1, -1);
    #endif
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
        if(getCurrentEditor()->document()->isModified())
        {
            name = "* " + name; // if it's not saved, add "*" a the beginning
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

//transmit signals to current editor slots
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

void Tab::findString(QString text)
{
    getCurrentEditor()->findString(text);
}

void Tab::findAllStrings(QString text)
{
    getCurrentEditor()->findAllStrings(text);
}

void Tab::replace(QString findText, QString replaceText)
{
    getCurrentEditor()->replace(findText, replaceText);
}

void Tab::replaceAll(QString findText, QString replaceText)
{
    getCurrentEditor()->replaceAll(findText, replaceText);
}

//Save Message Box
int Tab::saveMessageBox()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/icons/icon.ico"));
    msgBox.setText(tr("This document has been modified."));
    msgBox.setInformativeText(tr("Would you save changes ?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setButtonText(QMessageBox::Save, tr("Save"));
    msgBox.setButtonText(QMessageBox::Discard, tr("Don't save"));
    msgBox.setButtonText(QMessageBox::Cancel, tr("Cancel"));
    return msgBox.exec();
}
