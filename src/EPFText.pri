
INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/document.cpp \
    $$PWD/paragraph.cpp \
    $$PWD/textnode.cpp

HEADERS +=\
        $$PWD/epftext_global.h \
    $$PWD/document.h \
    $$PWD/paragraph.h \
    $$PWD/textnode.h \
    $$PWD/documentprivate.h \
    $$PWD/paragraphprivate.h \
    $$PWD/textnodeprivate.h

LIBS += -lpugixml
