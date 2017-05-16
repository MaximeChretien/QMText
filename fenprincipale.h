#ifndef FENPRINCIPALE
#define FENPRINCIPALE

#include <QtGui>
#include <QtWidgets>
#include <QPrinter>
#include <QPrintDialog>
#include "editor.h"

class FenPrincipale : public QMainWindow //classe principale
{
    Q_OBJECT

public:
    FenPrincipale(QString confFile, QFont font, QString lang, QString theme);
    void creerMenus(); //creation des menus (fichier, edition,...)
    void creerActions(); //creations des actions
    int saveMessageBox(); //boite de dialogue de sauvegarde
    void changeLanguage(QString langue); //methode pour changer de langue
    void changeTheme(QString theme); //methode pour changer le thème

private slots:  //differentes slots corespondant aux actions
    void aPropos();
    void nouveau();
    void save();
    void saveAs();
    void ouvrir();
    void police();
    void imprimer();
    void changementTitre();

    void saveTestFalse();//test de sauvegarde = faux
    void closeEvent(QCloseEvent * event); //pour verifier la sauvegarde avant de quitter
    void emptyTest();//pour pouvoir fermer le prog si le fichier n'a jamais été enregistrer et que la zone de texte est vide

    void dropEvent(QDropEvent *event); // pour le drag & drop
    void dragEnterEvent(QDragEnterEvent *event);// pareil

    void changeLanguageSystem(); //methode pour ...
    void changeLanguageFr(); // ... les differentes ...
    void changeLanguageEn(); // ... langues

    void changeThemeLight(); // methode pour les ...
    void changeThemeDark(); //... differents thèmes


private:
    Editor *mainText; //zone de texte
    QStringList confData; //tableau contenant les parametres de config
    QMenuBar *mnuBar; //barre des menus


    QAction *actionNouveau;  //differentes actions
    QAction *actionQuitter;
    QAction *actionAPropos;
    QAction *actionAProposQt;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionAnnuler;
    QAction *actionRestaurer;
    QAction *actionCopier;
    QAction *actionColler;
    QAction *actionCouper;
    QAction *actionOuvrir;
    QAction *actionPolice;
    QAction *actionImprimer;
    //langues
    QAction *actionLangueSysteme;
    QAction *actionLangueFr;
    QAction *actionLangueEn;
    //thèmes
    QAction *actionThemeLight;
    QAction *actionThemeDark;

    bool saveTest; //true = save, false = not save
    QString filePath; //emplacement du fichier
    QString fileType = "Fichiers texte (*.txt);; Fichiers C (*.c);; Fichiers C++ (*.cpp);; Fichiers Header (*.h);; Fichiers Java (*.java);; Fichiers HTML (*.html);; Fichiers CSS (*.css);; Fichiers PHP (*.php);; Fichiers Javascript (*.js);; Fichiers SQL (*.sql);; Fichiers XML (*.xml);; Scripts Python (*.py);; Scripts Batch (*.bat);; Scripts Shell (*.sh);; Tous les fichiers (*.*)"; //differents type de fichier gérés (totalement non exhaustif)
    QString configFile;
};

#endif // FENPRINCIPALE

