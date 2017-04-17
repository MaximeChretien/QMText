#include "fenprincipale.h"
#include <QApplication>
#include <QList>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QtPlugin>



int main(int argc, char *argv[])
{
    //Q_IMPORT_PLUGIN(platforms);
    //Q_IMPORT_PLUGIN(qprintsupport);

    //inutilisé par le programme, necessaire juste pour creer le fichier de traduction
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "Cancel"));
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "Apply"));
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "&Yes"));
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "&No"));
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "OK"));
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "Save"));

    QApplication app(argc, argv); // initialisation du programme

    //recuperation de la langue du systeme
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;

    //initialisation des element de config
    QFile config("./QMText.conf");
    QStringList configData;
    QTextStream fluxConfig(&config);
    QFont font;
    fluxConfig.setCodec("UTF-8");

    //verification de l'existence du fichier de config
    if(!config.exists())
    {
        //si inexistant : creation et remplissage du fichier avec les valeurs par defaut
        config.open(QIODevice::WriteOnly | QIODevice::Text);
        fluxConfig << "Font = \"Courier\"" << endl << "FontSize = \"10\"" << endl << "Language = \"System\"" << endl << "Theme = \"Light\"" ;
        config.close();
    }
    config.open(QIODevice::ReadWrite | QIODevice::Text);
    //lecture du fichier de config
    while(!fluxConfig.atEnd())
    {
        configData.append(fluxConfig.readLine());
    }

    //aplication des paramètres
        //style de la police
        configData[0].replace("Font = \"", "");
        configData[0].replace("\"", "");
        font.setFamily(configData[0]);
        if(!font.exactMatch())
        {
            font.setFamily("Courier");
            configData[0] = "Courier";
        }
        configData[0] = "Font = \"" + configData[0] + "\"";

        //taille de la police
        configData[1].replace("FontSize = \"", "");
        configData[1].replace("\"", "");
        if (configData[1].toInt())
        {
            font.setPointSize(configData[1].toInt());
        }
        else
        {
            font.setPointSize(10);
            configData[1] = "10";
        }
        configData[1] = "FontSize = \"" + configData[1] + "\"";


        //Language
        configData[2].replace("Language = \"", "");
        configData[2].replace("\"", "");


        if(configData[2] == "System")
        {
            if(QFile("./res/tr/qmtext_" + locale + ".qm").exists())
                translator.load("./res/tr/qmtext_" + locale);
           else
                translator.load("./res/tr/qmtext_en");
        }
        else if(configData[2] == "En")
        {
            translator.load("./res/tr/qmtext_en");
        }
        else if(configData[2] == "Fr")
        {
            translator.load("./res/tr/qmtext_fr");
        }
        else
        {
            translator.load("./res/tr/qmtext_" + locale);
            configData[2] = "System";
        }
        QString lang = configData[2];
        configData[2] = "Language = \"" + configData[2] + "\"";

        //theme
        configData[3].replace("Theme = \"", "");
        configData[3].replace("\"", "");

        if(configData[3] == "Light")
        {
            QFile file("./res/qss/Light.qss");
            file.open(QFile::ReadOnly);
            app.setStyleSheet(QLatin1String(file.readAll()));
            file.close();
        }
        else if(configData[3] == "Dark")
        {
            QFile file("./res/qss/Dark.qss");
            file.open(QFile::ReadOnly);
            app.setStyleSheet(QLatin1String(file.readAll()));
            file.close();
        }
        else
        {
            QFile file("./res/qss/Light.qss");
            file.open(QFile::ReadOnly);
            app.setStyleSheet(QLatin1String(file.readAll()));
            file.close();

            configData[3] = "Light";
        }
        QString theme = configData[3];
        configData[3] = "Theme = \"" + configData[3] + "\"";

        //réécriture du fihier pour corriger les erreurs potentielles
        config.resize(0);
        fluxConfig << configData[0] << endl << configData[1] << endl << configData[2] << endl << configData[3];
        config.close();


    app.installTranslator(&translator);

    FenPrincipale win(font, lang, theme);

    win.show();

    return app.exec();
}


