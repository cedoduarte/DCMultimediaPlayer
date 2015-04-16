#include <doptions.h>
#include <ui_doptions.h>
#include <QSettings>
#include <global.h>

DOptions::DOptions(QWidget *parent) : QDialog(parent), ui(new Ui::DOptions) {
    ui->setupUi(this);
    loadSettings();
}

DOptions::~DOptions() {
    delete ui;
}

void DOptions::on_buttonBox_accepted() {
    QSettings settings;
    settings.beginGroup(GROUP_STYLE);
    settings.setValue(KEY_STYLE, ui->duartecorp->isChecked() ? DUARTECORP :
        FUSION);
    settings.endGroup();
    settings.beginGroup(GROUP_LANG);
    settings.setValue(KEY_LANG, ui->language->currentIndex());
    settings.endGroup();
    accept();
}

void DOptions::on_buttonBox_rejected() {
    reject();
}

void DOptions::loadSettings() {
    QSettings settings;
    settings.beginGroup(GROUP_STYLE);
    switch (settings.value(KEY_STYLE, DUARTECORP).toUInt()) {
    case DUARTECORP:
        ui->duartecorp->setChecked(true);
        break;
    case FUSION:
        ui->fusion->setChecked(true);
        break;
    }
    settings.endGroup();
    settings.beginGroup(GROUP_LANG);
    ui->language->setCurrentIndex(settings.value(KEY_LANG, SPANISH).toUInt());
    settings.endGroup();
}
