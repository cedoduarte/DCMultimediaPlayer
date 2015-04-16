#include <dprogressslider.h>
#include <QMouseEvent>

DProgressSlider::DProgressSlider(QWidget *parent) :
    QSlider(Qt::Horizontal, parent) {
}

void DProgressSlider::mousePressEvent(QMouseEvent *ev) {
    emit pauseMultimedia(); // Pausar multimedia
    QSlider::mousePressEvent(ev); // Continuar
}

void DProgressSlider::mouseReleaseEvent(QMouseEvent *ev) {
    emit playMultimedia(); // Reproducir multimedia
    QSlider::mousePressEvent(ev); // Continuar
}
