#include <dvideosettingsdialog.h>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <dvideowidget.h>
#include <QGroupBox>

DVideoSettingsDialog::DVideoSettingsDialog(QWidget *parent) : QDialog(parent) {
    initialize();
    configure();
    // No conexiones
}

void DVideoSettingsDialog::initialize() {
    videowidget = 0; // Salida de video
    brightness = new QSlider(Qt::Horizontal, this);
    contrast = new QSlider(Qt::Horizontal, this);
    hue = new QSlider(Qt::Horizontal, this);
    saturation = new QSlider(Qt::Horizontal, this);
}

void DVideoSettingsDialog::configure() {
    resize(300, 100);
    setWindowTitle(tr("Opciones de video"));
    QVBoxLayout *labels = new QVBoxLayout;
    QVBoxLayout *sliders = new QVBoxLayout;
    QHBoxLayout *mainlayout = new QHBoxLayout;
    QLabel *brightnesslbl = new QLabel(tr("Brillo:"), this);
    QLabel *contrastlbl= new QLabel(tr("Contraste:"), this);
    QLabel *huelbl = new QLabel(tr("Matiz:"), this);
    QLabel *saturationlbl = new QLabel(tr("Saturación:"), this);
    labels->addWidget(brightnesslbl);
    labels->addWidget(contrastlbl);
    labels->addWidget(huelbl);
    labels->addWidget(saturationlbl);
    sliders->addWidget(brightness);
    sliders->addWidget(contrast);
    sliders->addWidget(hue);
    sliders->addWidget(saturation);
    mainlayout->addLayout(labels);
    mainlayout->addLayout(sliders);
    QGroupBox *groupbox = new QGroupBox(tr("Opciones"), this);
    groupbox->setLayout(mainlayout);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(groupbox);
    setLayout(layout);
}

void DVideoSettingsDialog::connections() {
    connect(brightness, SIGNAL(valueChanged(int)), videowidget,
        SLOT(setBrightness(int)));
    connect(contrast, SIGNAL(valueChanged(int)), videowidget,
        SLOT(setContrast(int)));
    connect(hue, SIGNAL(valueChanged(int)), videowidget, SLOT(setHue(int)));
    connect(saturation, SIGNAL(valueChanged(int)), videowidget,
        SLOT(setSaturation(int)));
}

void DVideoSettingsDialog::setVideoWidget(DVideoWidget *myvideowidget) {
    videowidget = myvideowidget;
    connections(); // Realiza conexiones
}

