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

#ifndef TAB_H
#define TAB_H

#include <QTabWidget>
#include <QMessageBox>
#include "Editor.hpp"

class Tab : public QTabWidget
{
    Q_OBJECT

public:
    Tab(QWidget *parent = nullptr, QFont font = QFont("Courier"));
    void addNewTab(QString filePath = "");
    void setFont(QFont newFont);
    QFont getFont();
    Editor* getCurrentEditor();
    int saveMessageBox();
    QStringList getTitle(bool newTab = true, QString path = "");

public slots:
    void undo();
    void redo();
    void copy();
    void paste();
    void cut();
    void printFile();
    void closeTab(int index);
    void changeTitle();
    void save();
    void saveAs();
    void findString(QString text);
    void findAllStrings(QString text);
    void replace(QString findText, QString replaceText);
    void replaceAll(QString findText, QString replaceText);

private:
    QStringList filePaths;
    QFont textFont;
};

#endif // TAB_H
