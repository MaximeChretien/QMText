#ifndef FENPRINCIPALE
#define FENPRINCIPALE

#include <QtGui>
#include <QtWidgets>
#include "editor.h"
#include "tab.h"

class FenPrincipale : public QMainWindow //classe principale
{
    Q_OBJECT

public:
    FenPrincipale(QString confFile, QFont font, QString lang, QString theme);
    void creerMenus(); //creation des menus (fichier, edition,...)
    void creerActions(); //creations des actions
    void changeLanguage(QString langue); //methode pour changer de langue
    void changeTheme(QString theme); //methode pour changer le thème

private slots:  //differentes slots corespondant aux actions
    void aPropos();
    void nouveau(QString path = "");
    void ouvrir();
    void police();

    void changementTitre();

    void zoomIn();
    void zoomOut();

    void closeEvent(QCloseEvent * event); //pour verifier la sauvegarde avant de quitter

    void dropEvent(QDropEvent *event); // pour le drag & drop
    void dragEnterEvent(QDragEnterEvent *event);// pareil

    void changeLanguageSystem(); //methode pour ...
    void changeLanguageFr(); // ... les differentes ...
    void changeLanguageEn(); // ... langues

    void changeThemeLight(); // methode pour les ...
    void changeThemeDark(); //... differents thèmes


private:
    Tab *tabWidget;
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
    QAction *actionZoomPlus;
    QAction *actionZoomMoins;
    //langues
    QAction *actionLangueSysteme;
    QAction *actionLangueFr;
    QAction *actionLangueEn;
    //thèmes
    QAction *actionThemeLight;
    QAction *actionThemeDark;

    QString configFile;

};

#endif // FENPRINCIPALE

