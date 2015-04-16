#ifndef DOPTIONS_H
#define DOPTIONS_H

#include <QDialog>

namespace Ui {
class DOptions;
}

/**
 * @brief The DOptions class
 */
class DOptions : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief DOptions
     * @param parent
     */
    explicit DOptions(QWidget *parent = 0);

    /**
      * @brief Destructor
      */
    ~DOptions();
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::DOptions *ui;

    void loadSettings();
};

#endif // DOPTIONS_H
