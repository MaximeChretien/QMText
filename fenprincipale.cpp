#include "fenprincipale.h"

FenPrincipale::FenPrincipale(QString confFile, QFont font, QString lang, QString theme) //Constructeur
{
    configFile = confFile;
    QFile conf(configFile);
    QTextStream fluxConf(&conf);

    fluxConf.setCodec("UTF-8");

    conf.open(QIODevice::ReadWrite | QIODevice::Text);

    while(!fluxConf.atEnd())
    {
        confData.append(fluxConf.readLine());
    }

    filePath = "";//emplacement du fichier vide par defaut

    mainText = new Editor(this); //cretion de la zone de texte
    mainText->setLineWrapMode(QPlainTextEdit::NoWrap); //activation de la scrollbar horizontale
    mainText->setFrameStyle(QFrame::NoFrame); // desactivation des bordures

    //parametres de la fenetre
    setMinimumSize(200,45); //taille mini
    resize(700,400); // taille de base
    setCentralWidget(mainText); // positionement de la zone de texte
    setWindowIcon(QIcon(":/icones/icon.ico")); // icone
    changementTitre(); // initialise le titre de la fenetre

    mainText->setFont(font); // aplication de la police dans la zone de texte

    //creation et initialisation de la barre des menus
    mnuBar = new QMenuBar(this);
    setMenuBar(mnuBar);

    // creation des actions et des menus
    creerActions();
    creerMenus();

    if(lang == "System")
    {
        actionLangueSysteme->setChecked(true);
    }
    else if(lang == "Fr")
    {
        actionLangueFr->setChecked(true);
    }
    else if(lang == "En")
    {
        actionLangueEn->setChecked(true);
    }

    if(theme == "Light")
    {
        actionThemeLight->setChecked(true);
    }
    else if(theme == "Dark")
    {
        actionThemeDark->setChecked(true);
    }


    //diverses actions realisé en cas de changement du texte dans la zone de texte
    connect(mainText, SIGNAL(textChanged()), this, SLOT(saveTestFalse()));
    connect(mainText, SIGNAL(textChanged()), this, SLOT(emptyTest()));
    connect(mainText, SIGNAL(textChanged()), this, SLOT(changementTitre()));

    //fixs pour le drag and drop
    mainText->setAcceptDrops(false);    
    setAcceptDrops(true);

    //recuperation du fichier en cas d'ouverture directe depuis l'OS (ouvrir avec ...)
    if(QCoreApplication::arguments().size() > 1)
    {
        filePath = QCoreApplication::arguments().at(1);

        QFile fichier(filePath);
        fichier.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream flux(&fichier);

        mainText->setPlainText(flux.readAll());
    }

    //initialisation du test de sauvegarde
    saveTest = new bool(true);

    changementTitre();
}

void FenPrincipale::creerActions() //creation des actions
{

    /* creations des actions:
     * - initialisation de l'action
     * - ajout d'un racourci clavier (facultatif)
     * - liaison au slot corespondant
     */

    actionNouveau = new QAction(tr("Nouveau"), this);
    actionNouveau->setShortcut(QKeySequence::New);
    connect(actionNouveau, SIGNAL(triggered(bool)), this, SLOT(nouveau()));

    actionAPropos = new QAction(tr("A Propos..."), this);
    actionAPropos->setShortcut(QKeySequence::HelpContents);
    connect(actionAPropos, SIGNAL(triggered(bool)), this, SLOT(aPropos()));

    actionAProposQt = new QAction(tr("A propos de Qt..."), this);
    connect(actionAProposQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    actionSave = new QAction(tr("Enregistrer"), this);
    actionSave->setShortcut(QKeySequence::Save);
    connect(actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));

    actionSaveAs = new QAction(tr("Enregistrer sous..."), this);
    actionSaveAs->setShortcut(QKeySequence("Ctrl+Maj+S"));
    connect(actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveAs()));

    actionAnnuler = new QAction(tr("Annuler"), this);
    actionAnnuler->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    connect(actionAnnuler, SIGNAL(triggered(bool)), mainText , SLOT(undo()));

    actionRestaurer = new QAction(tr("Restaurer"), this);
    actionRestaurer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    connect(actionRestaurer, SIGNAL(triggered(bool)), mainText, SLOT(redo()));

    actionCopier = new QAction(tr("Copier"), this);
    actionCopier->setShortcut(QKeySequence::Copy);
    connect(actionCopier, SIGNAL(triggered(bool)), mainText, SLOT(copy()));

    actionColler = new QAction(tr("Coller"), this);
    actionColler->setShortcut(QKeySequence::Paste);
    connect(actionColler, SIGNAL(triggered(bool)), mainText, SLOT(paste()));

    actionCouper = new QAction(tr("Couper"), this);
    actionCouper->setShortcut(QKeySequence::Cut);
    connect(actionCouper, SIGNAL(triggered(bool)), mainText, SLOT(cut()));

    actionOuvrir = new QAction(tr("Ouvrir..."), this);
    actionOuvrir->setShortcut(QKeySequence::Open);
    connect(actionOuvrir, SIGNAL(triggered(bool)), this, SLOT(ouvrir()));

    actionPolice = new QAction(tr("Police..."), this);
    connect(actionPolice, SIGNAL(triggered(bool)), this, SLOT(police()));

    actionImprimer = new QAction(tr("Imprimer..."), this);
    actionImprimer->setShortcut(QKeySequence::Print);
    connect(actionImprimer, SIGNAL(triggered(bool)), this, SLOT(imprimer()));

    actionZoomPlus = new QAction(tr("Zoom Plus"),this);
    actionZoomPlus->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
    connect(actionZoomPlus, SIGNAL(triggered(bool)), this, SLOT(zoomIn()));

    actionZoomMoins = new QAction(tr("Zoom Moins"),this);
    actionZoomMoins->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    connect(actionZoomMoins, SIGNAL(triggered(bool)), this, SLOT(zoomOut()));

    actionLangueSysteme = new QAction(tr("Langue du Système"), this);
    actionLangueSysteme->setCheckable(true);
    connect(actionLangueSysteme, SIGNAL(triggered(bool)), this, SLOT(changeLanguageSystem()));

    actionLangueFr = new QAction(tr("Français"), this);
    actionLangueFr->setCheckable(true);
    connect(actionLangueFr, SIGNAL(triggered(bool)), this, SLOT(changeLanguageFr()));

    actionLangueEn = new QAction(tr("Anglais"), this);
    actionLangueEn->setCheckable(true);
    connect(actionLangueEn, SIGNAL(triggered(bool)), this, SLOT(changeLanguageEn()));

    actionThemeLight = new QAction(tr("Clair"), this);
    actionThemeLight->setCheckable(true);
    connect(actionThemeLight, SIGNAL(triggered(bool)), this, SLOT(changeThemeLight()));

    actionThemeDark = new QAction(tr("Sombre"), this);
    actionThemeDark->setCheckable(true);
    connect(actionThemeDark, SIGNAL(triggered(bool)), this, SLOT(changeThemeDark()));

}

void FenPrincipale::creerMenus() //creation des menus
{
    mnuBar->setCursor(Qt::PointingHandCursor); //changement de curseur


    QMenu *fichier = mnuBar->addMenu(tr("&Fichier")); //creation du menu Fichier
    fichier->setCursor(Qt::PointingHandCursor); //changement de curseur
    fichier->addAction(actionNouveau); //ajout des differentes actions
    fichier->addAction(actionOuvrir);
    fichier->addAction(actionSave);
    fichier->addAction(actionSaveAs);
    fichier->addSeparator(); //ajout d'un separateur
    fichier->addAction(actionImprimer);

    QMenu *edition = mnuBar->addMenu(tr("&Edition")); //creation du menu Edition
    edition->setCursor(Qt::PointingHandCursor); //changement de curseur
    edition->addAction(actionAnnuler); //ajout des differentes actions
    edition->addAction(actionRestaurer);
    edition->addSeparator();//ajout d'un separateur
    edition->addAction(actionCouper);
    edition->addAction(actionCopier);
    edition->addAction(actionColler);
    edition->addSeparator();//ajout d'un separateur
    edition->addAction(actionPolice);
    edition->addSeparator();//ajout d'un separateur
    edition->addAction(actionZoomPlus);
    edition->addAction(actionZoomMoins);

    QMenu *langues = mnuBar->addMenu(tr("&Langues"));//creation du menu Langues
    langues->setCursor(Qt::PointingHandCursor); //changement de curseur
    langues->addAction(actionLangueSysteme); //ajout des differentes actions
    langues->addAction(actionLangueFr);
    langues->addAction(actionLangueEn);

    QMenu *theme = mnuBar->addMenu(tr("&Thème"));//creation du menu Thème
    theme->setCursor((Qt::PointingHandCursor)); //changement de curseur
    theme->addAction(actionThemeLight); //ajout des differentes actions
    theme->addAction(actionThemeDark);

    QMenu *aide = mnuBar->addMenu(tr("&?"));//creation du menu ?
    aide->setCursor(Qt::PointingHandCursor); //changement de curseur
    aide->addAction(actionAPropos); //ajout des differentes actions
    aide->addAction(actionAProposQt);
}

void FenPrincipale::aPropos() // menu a propos...
{
    QMessageBox::information(this, tr("A propos..."), tr("Editeur de texte réalisé par Mix<br /><strong>Version x</strong>")); //le x est modifié par la trad (plus simple a refaire en cas d'oubli de modif ...)
}

void FenPrincipale::save() // sauvegarde
{
    if(filePath.isEmpty()) // verifie si le fichier existe
    {
        saveAs(); // si il n'existe pas alors renvoie vers enregistrer sous...
    }
    else //sinon sauvegarde la fichier
    {
        QFile saveFile(filePath);
        saveFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream flux(&saveFile);

        flux.setCodec("UTF-8");

        flux << mainText->toPlainText();
        saveTest = true;
        changementTitre();
    }


}

void FenPrincipale::saveAs() // enregistrer sous
{

    QString filePathSave(filePath); // sauvegarde de l'emplacement actuel (en cas d'annulation)

    //recuperation de l'emplacement via boite de dialogue
    filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer un fichier"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), fileType);

    if(filePath.isEmpty()) // verification si annulation
    {
        filePath = filePathSave; // restauration de l'ancien emplacement
    }
    else //sinon sauvegarde
    {
    QFile saveAsFile(filePath);
    saveAsFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&saveAsFile);

    flux.setCodec("UTF-8");

    flux << mainText->toPlainText();
    saveTest = true;
    changementTitre();
    }
}

void FenPrincipale::ouvrir() // ouvrir un fichier
{
    //verification de sauvegarde du fichier actuel
    if(saveTest == false)
    {
        switch (saveMessageBox()) //boite de dialogue de sauvegarde et aplication des differentes actions suivant le resultat
        {
          case QMessageBox::Save:
              save();
              saveTest = true;
              break;
          case QMessageBox::No:
                //ici on ne fait rien
              break;
          case QMessageBox::Cancel:
              return;
              break;
          default:
              //normalement on peut pas y acceder
              break;
        }


    }


    QString filePathSave = filePath; // sauvegarde de l'emplacement actuel en cas d'annulation

    // recuperation du fichier via boite de dialogue
    filePath = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), fileType);


    if(filePath.isEmpty()) // verification si annulé
    {
        filePath = filePathSave; // restauration de l'ancien emplacement
    }
    else // sinon ouverture du fichier
    {
    QFile fichier(filePath);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    mainText->setPlainText(flux.readAll());
    saveTest = true;
    changementTitre();
    }

}

void FenPrincipale::police() // changement de police
{
    bool ok = false;


        QFont police = QFontDialog::getFont(&ok, mainText->font(), this, tr("Choisissez une police")); // recuperation de la police via boite de dialogue

        if (ok) //si ok aplication de la police
        {
            mainText->setFont(police);
        }
        // ecriture du resultat dans le fichier de config
        confData[0] = "Font = \"" + police.family() + "\"";
        confData[1] = "FontSize = \"" + QString::number(police.pointSize()) + "\"";

}

void FenPrincipale::imprimer() //impression
{
    //initialisation de l'imprimante et ouverture de la boite de dialogue
    QPrinter * imprimante = new QPrinter;
    QPrintDialog * dialogue = new QPrintDialog(imprimante, this);

    if(dialogue->exec() == QDialog::Accepted)//si ok, impression du fichier
        mainText->print(imprimante);

}

void FenPrincipale::changementTitre() // changement du titre de la fenetre
{

    QFile docu(filePath); //recuperation du fichier

    QString titreCourt = docu.fileName(); //recuperation du nom d fichier (avec emplacement)
    titreCourt.replace("/", "\\"); // changement de "/" en "\"

        if (titreCourt.isEmpty())
        {
            titreCourt = tr("Sans Titre"); // si vide titre = "Sans Titre"
        }

        if (saveTest == false)
        {
            titreCourt = "* " + titreCourt; // si non sauvegardé, ajout de "*" au debut
        }

        setWindowTitle(titreCourt + " - " + tr("QMText")); // ajout de " - QMText" a la fin du titre
}

void FenPrincipale::saveTestFalse() // passe le test de sauvegarde en false et change le titre de la fenetre
{
    saveTest = false;
    changementTitre();
}

void FenPrincipale::closeEvent(QCloseEvent * event) //en cas de fermeture du programme
{
    //ouverture du fichier de config
    QFile conf(configFile);
    QTextStream fluxConf(&conf);

    fluxConf.setCodec("UTF-8");

    conf.open(QIODevice::ReadWrite | QIODevice::Text);

    if(saveTest == false) // verifie si sauvegarder
    {

    switch (saveMessageBox()) // boite de dialogue et actions suivant le resultat
    {
      case QMessageBox::Save:
          save();
          QWidget::closeEvent(event);
          break;
      case QMessageBox::No:
          QWidget::closeEvent(event);
          break;
      case QMessageBox::Cancel:
          event->ignore();//on ignore la demande d'arret
          break;
      default:
          //normalement on peut pas y acceder
          break;
    }
    }
    conf.resize(0); // effacement du fichier de config
    fluxConf << confData[0] << endl << confData[1] << endl << confData[2] << endl << confData[3]; // ecriture de la nouvelle config
    conf.close(); // fermeture du fichier
}

void FenPrincipale::nouveau() // nouveau
{
    if(saveTest == false) // verifie si sauvegarder
    {


    switch (saveMessageBox()) // boite de dialogue et action en fonction du resultat
    {
      case QMessageBox::Save: // sauvegarde puis effacement de la zone de texte
          save();
          mainText->clear();
          filePath = "";
          saveTest = true;
          break;
      case QMessageBox::No: // effacement de la zone de texte sans sauvegarde
          mainText->clear();
          filePath = "";
          saveTest = true;
          break;
      case QMessageBox::Cancel:
          //on fait rien
          break;
      default:
          //normalement on peut pas y acceder
          break;
    }
    }
    else if(saveTest == true) // si sauvegarder, effacement de la zone de texte
    {
        mainText->clear();
        filePath = "";
        saveTest = true;
    }
    changementTitre();
}

void FenPrincipale::emptyTest() // test si aucun fichier et aucun texte
{
    if(filePath.isEmpty() && mainText->toPlainText().isEmpty())
    {
        saveTest = true;
    }
}

void FenPrincipale::dropEvent(QDropEvent *event) // drop (assez obscur, j'ai pas encore tout compris, faut dire aussi que j'ai pas essayer ^^)
{
    nouveau();
    filePath = event->mimeData()->urls().at(0).toString().right(event->mimeData()->urls().at(0).toString().size()-8);
        event->accept();
        QFile fichier(filePath);
        fichier.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream flux(&fichier);

        mainText->setPlainText(flux.readAll());
        saveTest = true;
        changementTitre();
}

void FenPrincipale::dragEnterEvent(QDragEnterEvent *event) // drag (assez obscur, j'ai pas encore tout compris, faut dire aussi que j'ai pas essayer ^^)
{
    if(event->mimeData()->hasUrls())
            event->acceptProposedAction();
}

int FenPrincipale::saveMessageBox() // boite de dialogue pour sauvegarde
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/icones/icon.ico"));
    msgBox.setText(tr("Ce document a été modifié."));
    msgBox.setInformativeText(tr("Voulez-vous enregistrer les modifications ?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec();
}

void FenPrincipale::changeLanguage(QString langue) // ecriture du tableau de config pour la langue et info
{
    confData[2] = "Language = \"" + langue + "\"";

    QMessageBox::information(this, tr("Redémarage nécessaire"), tr("Le changement de langue prendra effet au prochain démarage de QMText."));
}

void FenPrincipale::changeLanguageSystem() //actions pour definir langue
{
    changeLanguage("System");
    actionLangueEn->setChecked(false);
    actionLangueFr->setChecked(false);
    actionLangueSysteme->setChecked(true);
}

void FenPrincipale::changeLanguageFr()
{
    changeLanguage("Fr");
    actionLangueEn->setChecked(false);
    actionLangueFr->setChecked(true);
    actionLangueSysteme->setChecked(false);
}

void FenPrincipale::changeLanguageEn()
{
    changeLanguage("En");
    actionLangueEn->setChecked(true);
    actionLangueFr->setChecked(false);
    actionLangueSysteme->setChecked(false);
}

void FenPrincipale::changeTheme(QString theme) // ecriture du tableau de config pour le theme et info
{
    confData[3] = "Theme = \"" + theme + "\"";

    QMessageBox::information(this, tr("Redémarage nécessaire"), tr("Le changement de thème prendra effet au prochain démarage de QMText."));
}

void FenPrincipale::changeThemeLight() //actions pour definior le thème
{
    changeTheme("Light");
    actionThemeDark->setChecked(false);
    actionThemeLight->setChecked(true);
}

void FenPrincipale::changeThemeDark()
{
    changeTheme("Dark");
    actionThemeDark->setChecked(true);
    actionThemeLight->setChecked(false);
}

void FenPrincipale::zoomIn()
{
    QFont font = mainText->font();
    font.setPointSize(font.pointSize()+1);
    mainText->setFont(font);
    confData[1] = "FontSize = \"" + QString::number(mainText->font().pointSize()) + "\"";
}

void FenPrincipale::zoomOut()
{
    QFont font = mainText->font();
    font.setPointSize(font.pointSize()-1);
    mainText->setFont(font);
    confData[1] = "FontSize = \"" + QString::number(mainText->font().pointSize()) + "\"";
}
