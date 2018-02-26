#include "MainWindow.hpp"
#include "XmlSettings.hpp"
#include <QApplication>
#include <QStringList>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>



int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    //files paths init
    QString confFile = qApp->applicationDirPath() + "/conf.xml";
    QString tradDir = qApp->applicationDirPath() + "/res/tr/";
    QString themeDir = qApp->applicationDirPath() + "/res/qss/";

    //get system language
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;


    //config init
    QStringList configData;
    XmlSettings settings(confFile);

    QString defaultFont = "DejaVu Sans Mono";

    #ifdef WIN32 //change default font for windows
        defaultFont = "Consolas";
    #endif

    //read config file
    configData = settings.read();

    //apply config
    //font
    if(!QFont(configData[0]).exactMatch())
    {
        configData[0] = defaultFont;
    }

    //font size
    if (!configData[1].toInt())
    {
        configData[1] = "12";
    }

    //Language
    if(configData[2] == "En")
    {
        translator.load(tradDir + "qmtext_en");
    }
    else if(configData[2] == "Fr")
    {
        translator.load(tradDir + "qmtext_fr");
    }
    else
    {
        if(QFile(tradDir + "qmtext_" + locale + ".qm").exists())
            translator.load(tradDir + "qmtext_" + locale);
        else
            translator.load(tradDir + "qmtext_en");

        configData[2] = "System";
    }

    //theme
    if(configData[3] == "Dark")
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

    settings.write(configData);

    app.installTranslator(&translator);

    MainWindow win(configData, confFile);

    win.show();

    return app.exec();
}


