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

#include "FindAndReplaceWidget.hpp"

FindAndReplaceWidget::FindAndReplaceWidget(QWidget *parent) : QWidget(parent)
{
    //lables init
    labelFind = new QLabel(tr("Find : "), this);
    labelReplace = new QLabel(tr("Replace with : "), this);

    //line edit init
    lineEditFind = new QLineEdit(this);
    lineEditReplace = new QLineEdit(this);

    //buttons init
    buttonFind = new QPushButton(tr("Find"), this);
    buttonFindAll = new QPushButton(tr("Find All"), this);
    buttonReplace = new QPushButton(tr("Replace"), this);
    buttonReplaceAll = new QPushButton(tr("Replace All"), this);
    buttonClose = new QPushButton("X", this);
    buttonClose->setMaximumSize(20,20);

    //grid init
    layout = new QGridLayout(this);
    layout->setMargin(5);
    layout->addWidget(labelFind, 0, 0);
    layout->addWidget(lineEditFind, 0, 1);
    layout->addWidget(buttonFind, 0, 2);
    layout->addWidget(buttonFindAll, 0, 3);
    layout->addWidget(buttonClose, 0, 4);
    layout->addWidget(labelReplace, 1, 0);
    layout->addWidget(lineEditReplace, 1, 1);
    layout->addWidget(buttonReplace, 1, 2);
    layout->addWidget(buttonReplaceAll, 1, 3);

    setLayout(layout);

    //emit signals when button are pushed
    connect(buttonFind, SIGNAL(clicked(bool)), this, SLOT(findClicked()));
    connect(buttonFindAll, SIGNAL(clicked(bool)), this, SLOT(findAllClicked()));
    connect(lineEditFind, SIGNAL(textChanged(QString)), this, SLOT(findAllClicked()));

    connect(buttonReplace, SIGNAL(clicked(bool)), this, SLOT(replaceClicked()));
    connect(buttonReplaceAll, SIGNAL(clicked(bool)), this, SLOT(replaceAllClicked()));

    //hide and reset widget when it is closed
    connect(buttonClose, SIGNAL(clicked(bool)), this, SLOT(hide()));
    connect(buttonClose, SIGNAL(clicked(bool)), lineEditFind, SLOT(clear()));
    connect(buttonClose, SIGNAL(clicked(bool)), lineEditReplace, SLOT(clear()));
}

void FindAndReplaceWidget::findClicked()
{
    emit findString(lineEditFind->text());
}

void FindAndReplaceWidget::findAllClicked()
{
    emit findAllStrings(lineEditFind->text());
}

void FindAndReplaceWidget::replaceClicked()
{
    emit replace(lineEditFind->text(), lineEditReplace->text());
}

void FindAndReplaceWidget::replaceAllClicked()
{
    emit replaceAll(lineEditFind->text(), lineEditReplace->text());
}
