#ifndef TAB_H
#define TAB_H

#include <QTabWidget>
#include <QMessageBox>
#include "editor.h"

#include <QDebug>

class Tab : public QTabWidget
{
    Q_OBJECT

public:
    Tab(QWidget *parent = 0, QFont font = QFont("Courier"));
    void addNewTab(QString filePath = "");
    void setFont(QFont newFont);
    QFont getFont();
    Editor* getCurrentEditor();
    int saveMessageBox(); //boite de dialogue de sauvegarde
    QStringList getTitle(bool newTab = true, QString path = "");

public slots:
    void undo();
    void redo();
    void copy();
    void paste();
    void cut();
    void imprimer();
    void closeTab(int index);
    void changeTitle();
    void save();
    void saveAs();

private:
    QStringList filePaths;
    QFont textFont;
};

#endif // TAB_H
