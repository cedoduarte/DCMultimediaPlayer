#-------------------------------------------------
#
# Project created by QtCreator DuarteCorporation
#
#-------------------------------------------------

lessThan(QT_MAJOR_VERSION, 5) {
    error("The Qt version is not capable for this project")
}

QT += core gui widgets multimedia multimediawidgets

TARGET = DCMultimediaPlayer
TEMPLATE = app

SOURCES += main.cpp\
    dplaylistwidget.cpp \
    dprogressslider.cpp \
    dvideowidget.cpp \
    dvideosettingsdialog.cpp \
    utilities.cpp \
    doptions.cpp \
    mainwindow.cpp

HEADERS  += mainwindow.h \
    dplaylistwidget.h \
    dprogressslider.h \
    dvideowidget.h \
    dvideosettingsdialog.h \
    utilities.h \
    doptions.h \
    global.h

FORMS    += mainwindow.ui \
    doptions.ui

RESOURCES += \
    icons.qrc \
    translations.qrc

OTHER_FILES += \
    iconfile.rc

RC_FILE += iconfile.rc
