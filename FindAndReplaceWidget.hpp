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
