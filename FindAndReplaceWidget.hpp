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

#ifndef FINDANDREPLACEWIDGET_HPP
#define FINDANDREPLACEWIDGET_HPP

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class FindAndReplaceWidget : public QWidget
{
    Q_OBJECT

public:
    FindAndReplaceWidget(QWidget *parent = 0);

private slots:
    void findClicked();
    void findAllClicked();
    void replaceClicked();
    void replaceAllClicked();

signals:
    void findString(QString text);
    void findAllStrings(QString text);
    void replace(QString findText, QString replaceText);
    void replaceAll(QString findText, QString replaceText);

private:
    QGridLayout *layout;
    QPushButton *buttonFind, *buttonReplace, *buttonFindAll, *buttonReplaceAll, *buttonClose;
    QLineEdit *lineEditFind, *lineEditReplace;
    QLabel *labelFind, *labelReplace;
};

#endif // FINDANDREPLACEWIDGET_HPP
