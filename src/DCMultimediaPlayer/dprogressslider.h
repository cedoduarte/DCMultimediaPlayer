#ifndef DPROGRESSSLIDER_H // OK
#define DPROGRESSSLIDER_H

#include <QSlider>

/**
 * @brief The DProgressSlider class
 */
class DProgressSlider : public QSlider {
    Q_OBJECT
public:
    /**
     * @brief DProgressSlider
     * @param parent
     */
    explicit DProgressSlider(QWidget *parent = 0);
protected:
    /**
     * @brief mousePressEvent
     * @param ev
     */
    virtual void mousePressEvent(QMouseEvent *ev); // Presión

    /**
     * @brief mouseReleaseEvent
     * @param ev
     */
    virtual void mouseReleaseEvent(QMouseEvent *ev); // Liberación
signals:
    /**
     * @brief pauseMultimedia
     */
    void pauseMultimedia(); // Pausar multimedia

    /**
     * @brief playMultimedia
     */
    void playMultimedia(); // Reproducir multimedia
};

#endif // DPROGRESSSLIDER_H
