QT += widgets printsupport

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Editor.cpp \
    Tab.cpp \
    FindAndReplaceWidget.cpp \
    XmlSettings.cpp \
    Highlighter.cpp \
    highlighters/CppHighlighter.cpp \
    highlighters/CssHighlighter.cpp \
    highlighters/HtmlHighlighter.cpp \
    highlighters/JavaHighlighter.cpp \
    highlighters/PhpHighlighter.cpp \
    highlighters/PythonHighlighter.cpp \
    highlighters/ShellHighlighter.cpp \
    highlighters/XmlHighlighter.cpp

HEADERS += \
    Tab.hpp \
    MainWindow.hpp \
    Editor.hpp \
    FindAndReplaceWidget.hpp \
    XmlSettings.hpp \
    Highlighter.hpp \
    highlighters/CppHighlighter.hpp \
    highlighters/CssHighlighter.hpp \
    highlighters/HtmlHighlighter.hpp \
    highlighters/JavaHighlighter.hpp \
    highlighters/PhpHighlighter.hpp \
    highlighters/PythonHighlighter.hpp \
    highlighters/ShellHighlighter.hpp \
    highlighters/XmlHighlighter.hpp

RESOURCES += \
    res.qrc

RC_ICONS = icon.ico

TRANSLATIONS += \
    translations/qmtext_en.ts \
    translations/qmtext_fr.ts

DISTFILES += \
    COPYING \
    translations/qmtext_en.ts \
    translations/qmtext_fr.ts \
    res/qss/Dark.qss \
    res/qss/Light.qss \
    res/tr/qmtext_en.qm \
    res/tr/qmtext_fr.qm
