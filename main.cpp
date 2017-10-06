#include "MainWindow.hpp"
#include <QApplication>
#include <QList>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>



int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    //files paths init
    QString confFile = qApp->applicationDirPath() + "/QMText.conf";
    QString tradDir = qApp->applicationDirPath() + "/res/tr/";
    QString themeDir = qApp->applicationDirPath() + "/res/qss/";

    //get system language
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;


    //config init
    QFile config(confFile);
    QStringList configData;
    QTextStream fluxConfig(&config);
    QFont font;
    fluxConfig.setCodec("UTF-8");

    QString defaultFont = "DejaVu Sans Mono";

    #ifdef WIN32 //change default font for windows
        defaultFont = "Consolas";
    #endif

    //if config file don't exist
    if(!config.exists())
    {
        //create it with default settings
        config.open(QIODevice::WriteOnly | QIODevice::Text);
        fluxConfig << "Font = \"" + defaultFont + "\"" << endl << "FontSize = \"12\"" << endl << "Language = \"System\"" << endl << "Theme = \"Light\"" ;
        config.close();
    }
    config.open(QIODevice::ReadWrite | QIODevice::Text);
    //read config file
    while(!fluxConfig.atEnd())
    {
        configData.append(fluxConfig.readLine());
    }

    //apply config
        //font
        configData[0].replace("Font = \"", "");
        configData[0].replace("\"", "");
        font.setFamily(configData[0]);
        if(!font.exactMatch())
        {
            font.setFamily(defaultFont);
            configData[0] = defaultFont;
        }
        configData[0] = "Font = \"" + configData[0] + "\"";

        //font size
        configData[1].replace("FontSize = \"", "");
        configData[1].replace("\"", "");
        if (configData[1].toInt())
        {
            font.setPointSize(configData[1].toInt());
        }
        else
        {
            font.setPointSize(12);
            configData[1] = "12";
        }
        configData[1] = "FontSize = \"" + configData[1] + "\"";


        //Language
        configData[2].replace("Language = \"", "");
        configData[2].replace("\"", "");


        if(configData[2] == "System")
        {
            if(QFile(tradDir + "qmtext_" + locale + ".qm").exists())
                translator.load(tradDir + "qmtext_" + locale);
           else
                translator.load(tradDir + "qmtext_en");
        }
        else if(configData[2] == "En")
        {
            translator.load(tradDir + "qmtext_en");
        }
        else if(configData[2] == "Fr")
        {
            translator.load(tradDir + "qmtext_fr");
        }
        else
        {
            translator.load(tradDir + "qmtext_" + locale);
            configData[2] = "System";
        }
        QString lang = configData[2];
        configData[2] = "Language = \"" + configData[2] + "\"";

        //theme
        configData[3].replace("Theme = \"", "");
        configData[3].replace("\"", "");

        if(configData[3] == "Light")
        {
            QFile file(themeDir + "Light.qss");
            file.open(QFile::ReadOnly);
            app.setStyleSheet(QLatin1String(file.readAll()));
            file.close();
        }
        else if(configData[3] == "Dark")
        {
            QFile file(themeDir + "Dark.qss");
            file.open(QFile::ReadOnly);
            app.setStyleSheet(QLatin1String(file.readAll()));
            file.close();
        }
        else
        {
            QFile file(themeDir + "Light.qss");
            file.open(QFile::ReadOnly);
            app.setStyleSheet(QLatin1String(file.readAll()));
            file.close();

            configData[3] = "Light";
        }
        QString theme = configData[3];
        configData[3] = "Theme = \"" + configData[3] + "\"";

        //rewrite config file to correct error
        config.resize(0);
        fluxConfig << configData[0] << endl << configData[1] << endl << configData[2] << endl << configData[3];
        config.close();


    app.installTranslator(&translator);

    MainWindow win(confFile,font, lang, theme);

    win.show();

    return app.exec();
}


