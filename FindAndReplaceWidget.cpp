#include "FindAndReplaceWidget.hpp"

FindAndReplaceWidget::FindAndReplaceWidget(QWidget *parent) : QWidget(parent)
{
    labelFind = new QLabel(tr("Find : "), this);
    labelReplace = new QLabel(tr("Replace with : "), this);

    lineEditFind = new QLineEdit(this);
    lineEditReplace = new QLineEdit(this);

    buttonFind = new QPushButton(tr("Find"), this);
    buttonFindAll = new QPushButton(tr("FindAll"), this);
    buttonReplace = new QPushButton(tr("Replace"), this);
    buttonReplaceAll = new QPushButton(tr("ReplaceAll"), this);
    buttonClose = new QPushButton(tr("X"), this);
    buttonClose->setMaximumSize(20,20);

    layout = new QGridLayout(this);
    layout->addWidget(labelFind, 0, 0);
    layout->addWidget(lineEditFind, 0, 1);
    layout->addWidget(buttonFind, 0, 2);
    layout->addWidget(buttonFindAll, 0, 3);
    layout->addWidget(buttonClose, 0, 4);
    layout->addWidget(labelReplace, 1, 0);
    layout->addWidget(lineEditReplace, 1, 1);
    layout->addWidget(buttonReplace, 1, 2);
    layout->addWidget(buttonReplaceAll, 1, 3);

    layout->setMargin(5);

    setLayout(layout);

    connect(buttonFind, SIGNAL(clicked(bool)), this, SLOT(findClicked()));
    connect(buttonFindAll, SIGNAL(clicked(bool)), this, SLOT(findAllClicked()));
    connect(buttonReplace, SIGNAL(clicked(bool)), this, SLOT(replaceClicked()));
    connect(buttonReplaceAll, SIGNAL(clicked(bool)), this, SLOT(replaceAllClicked()));
    connect(buttonClose, SIGNAL(clicked(bool)), this, SLOT(hide()));
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
