#include <mainwindow.h>
#include <QApplication>
#include <QLatin1String>
#include <QFileInfo>
#include <QStringList>
#include <QSettings>
#include <global.h>
#include <QTranslator>

#define DUARTECORP_STYLE "background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 235, 235, 206), stop:0.35 rgba(255, 188, 188, 80), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));\ncolor: white;"
#define APPLICATION_NAME "DCMultimediaPlayer"
#define APPLICATION_VERSION "2013"
#define ORGANIZATION_DOMAIN "www.duartecorp.org"
#define ORGANIZATION_NAME "DuarteCorporation"

static ushort getStyle() {
    QSettings settings;
    settings.beginGroup(GROUP_STYLE);
    const ushort style = settings.value(KEY_STYLE, DUARTECORP).toUInt();
    settings.endGroup();
    return style;
}

static QString getLanguage() {
    QSettings settings;
    settings.beginGroup(GROUP_LANG);
    const ushort lang = settings.value(KEY_LANG, SPANISH).toUInt();
    settings.endGroup();
    switch (lang) {
    case SPANISH: return "";
    case ENGLISH: return ":english";
    case FRENCH: return ":french";
    }
    return "";
}

static QStringList getFilenames(int argc, char **argv) {
    QStringList filenames;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            const QString filename =
                QFileInfo(QLatin1String(argv[i])).
                    absoluteFilePath();
            filenames.append(filename);
        }
    }
    return filenames;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(APPLICATION_NAME);
    a.setApplicationVersion(APPLICATION_VERSION);
    a.setOrganizationDomain(ORGANIZATION_DOMAIN);
    a.setOrganizationName(ORGANIZATION_NAME);
    QTranslator trans;
    trans.load(getLanguage());
    a.installTranslator(&trans);
    a.setStyle("fusion");
    MainWindow w(getFilenames(argc, argv));
    if (getStyle() == DUARTECORP)
        w.setStyleSheet(DUARTECORP_STYLE);
    w.show();
    return a.exec();
}
