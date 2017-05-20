#include "tab.h"

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
    QString name;
    if (filePath == "")
    {
        name = "Sans Titre";
    }
    else
    {
        name = filePath;
    }
    addTab(textZone, name);
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
            switch (saveMessageBox()) // boite de dialogue et actions suivant le resultat
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
                     //normalement on peut pas y acceder
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

void Tab::saveAs() // enregistrer sous
{
    //recuperation de l'emplacement via boite de dialogue
    QString filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer un fichier"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), getCurrentEditor()->getFileTypes());

    if(!filePath.isEmpty()) // verification si annulation
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

void Tab::changeTitle()
{
    QFile docu(getCurrentEditor()->getFilePath()); //recuperation du fichier

    QString titreCourt = docu.fileName(); //recuperation du nom d fichier (avec emplacement)
    #ifdef WIN32 //modification du formatage du chemin de fichier pour windows
    titreCourt.replace("/", "\\"); // changement de "/" en "\"
    #endif

        if (titreCourt.isEmpty())
        {
            titreCourt = tr("Sans Titre"); // si vide titre = "Sans Titre"
        }

        if (getCurrentEditor()->getSaveState() == false)
        {
            titreCourt = "* " + titreCourt; // si non sauvegardé, ajout de "*" au debut
        }

        setTabText(currentIndex(),titreCourt);
        emit currentChanged(currentIndex());
}

Editor *Tab::getCurrentEditor()
{
    return (Editor*)currentWidget();
}

//transfert des commandes vers l'editeur actuel
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

void Tab::imprimer()
{
    getCurrentEditor()->imprimer();
}

int Tab::saveMessageBox() // boite de dialogue pour sauvegarde
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/icones/icon.ico"));
    msgBox.setText(tr("Ce document a été modifié."));
    msgBox.setInformativeText(tr("Voulez-vous enregistrer les modifications ?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec();
}
