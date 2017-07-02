QT += widgets printsupport

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Editor.cpp \
    Tab.cpp

HEADERS += \
    Tab.hpp \
    MainWindow.hpp \
    Editor.hpp

RESOURCES += \
    res.qrc

RC_ICONS = icon.ico
TRANSLATIONS = qmtext_en.ts qmtext_fr.ts
