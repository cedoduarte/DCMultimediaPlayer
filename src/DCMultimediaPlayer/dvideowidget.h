#ifndef DVIDEOWIDGET_H // OK
#define DVIDEOWIDGET_H

#include <QVideoWidget>
// usar parent para mostrar la ventana principal

class QAction;
class MainWindow;
class QMenu;

/**
 * @brief The DVideoWidget class
 */
class DVideoWidget : public QVideoWidget {
    Q_OBJECT
public:
    /**
     * @brief DVideoWidget
     * @param parent
     */
    explicit DVideoWidget(QWidget *parent = 0);
protected:
    /**
     * @brief contextMenuEvent
     * @param e
     */
    virtual void contextMenuEvent(QContextMenuEvent *e);

    /**
     * @brief mouseDoubleClickEvent
     * @param e
     */
    virtual void mouseDoubleClickEvent(QMouseEvent *e);

    /**
     * @brief keyPressEvent
     * @param e
     */
    virtual void keyPressEvent(QKeyEvent *e);
private slots:
    void onPlayTriggered();
    void onPauseTriggered();
    void onStopTriggered();
    void onNextTriggered();
    void onPrevTriggered();
    void onOpenFileTriggered();
    void onFullScreenTriggered();
    void onVideoOptionsTriggered();
    void onShowMainWindowTriggered();
    void onQuitTriggered();
private:
    MainWindow *myparent; // Ventana principal
    QMenu *menu; // Menú contextual
    QAction *play; // Reproducir
    QAction *pause; // Pausar
    QAction *stop; // Detener
    QAction *next; // Siguiente
    QAction *prev; // Anterior
    QAction *openfile; // Abrir archivo
    QAction *fullscreen; // Pantalla completa
    QAction *videooptions; // Opciones de video
    QAction *showmainwindow; // Muestra ventana principal
    QAction *quit; // Quita programa
};

#endif // DVIDEOWIDGET_H
