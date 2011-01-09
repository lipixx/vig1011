#-------------------------------------------------
#
# Project created by QtCreator 2010-09-29T17:51:16
#
#-------------------------------------------------

QT       += opengl

TARGET = PracticaVIG
TEMPLATE = app

INCLUDEPATH += ../widget
LIBS += ../widget/libglwidgetplugin.so

SOURCES += main.cpp\
        principal.cpp \
    dialegmaterials.cpp \
    ajuda.cpp

HEADERS  += principal.h \
    dialegmaterials.h \
    ajuda.h

FORMS    += principal.ui \
    dialegmaterials.ui \
    ajuda.ui
