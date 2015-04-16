#ifndef DVIDEOSETTINGSDIALOG_H // OK
#define DVIDEOSETTINGSDIALOG_H

#include <QDialog>

class QSlider;
class DVideoWidget;

/**
 * @brief The DVideoSettingsDialog class
 */
class DVideoSettingsDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief DVideoSettingsDialog
     * @param parent
     */
    explicit DVideoSettingsDialog(QWidget *parent = 0); 

    /**
     * @brief setVideoWidget
     * @param myvideowidget
     */
    void setVideoWidget(DVideoWidget *myvideowidget);
private:
    DVideoWidget *videowidget;
    QSlider *brightness;
    QSlider *contrast;
    QSlider *hue;
    QSlider *saturation;

    void initialize();
    void configure();
    void connections();
};

#endif // DVIDEOSETTINGSDIALOG_H
