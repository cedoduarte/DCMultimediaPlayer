#ifndef MAINWINDOW_H // OK
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class QPushButton;
class QSlider;
class DOptions;
class QLabel;
class QDockWidget;
class QLineEdit;
class DPlayListWidget;
class QProgressBar;
class DProgressSlider;
class DVideoWidget;
class QMediaPlayer;
class QMediaPlaylist;
class DVideoSettingsDialog;

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief MainWindow
     * @param myfilenames
     * @param parent
     */
    explicit MainWindow(const QStringList &myfilenames,
        QWidget *parent = 0);

    /**
      * @brief Destructor
      */
    ~MainWindow();
public slots:
    // Acciones

    /**
     * @brief onOpenFileActionTriggered
     */
    void onOpenFileActionTriggered();

    /**
     * @brief onQuitActionTriggered
     */
    void onQuitActionTriggered();

    /**
     * @brief onPlayActionTriggered
     */
    void onPlayActionTriggered();

    /**
     * @brief onPauseActionTriggered
     */
    void onPauseActionTriggered();

    /**
     * @brief onStopActionTriggered
     */
    void onStopActionTriggered();

    /**
     * @brief onNextActionTriggered
     */
    void onNextActionTriggered();

    /**
     * @brief onPrevActionTriggered
     */
    void onPrevActionTriggered();

    /**
     * @brief onVideoOptionsActionTriggered
     */
    void onVideoOptionsActionTriggered();

    /**
     * @brief onFullScreenClicked
     */
    void onFullScreenClicked(); // Botón pantalla completa
protected:
    /**
     * @brief dragEnterEvent
     * @param e
     */
    virtual void dragEnterEvent(QDragEnterEvent *e);

    /**
     * @brief dragLeaveEvent
     * @param e
     */
    virtual void dragLeaveEvent(QDragLeaveEvent *e);

    /**
     * @brief dragMoveEvent
     * @param e
     */
    virtual void dragMoveEvent(QDragMoveEvent *e);

    /**
     * @brief dropEvent
     * @param e
     */
    virtual void dropEvent(QDropEvent *e);
private slots:
    void onMuteSoundClicked(bool checked); // Botón de silencio
    void onVolumeSliderValueChanged(int val); // Deslizador de volumen
    void onPauseMultimedia(); // Pausar multimedia
    void onPlayMultimedia(); // Reproducir multimedia

    // Objetos multimedia
    void onDurationChanged(qint64 dur);
    void onPositionChanged(qint64 pos);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus s);

    void onAboutDCactionTriggered();
    void onAboutDCMPactionTriggered();

    // Lista de reproducción
    void onClearFilterClicked(); // Limpia filtro
    void onFilterTextEdited(const QString &txt); // Filtro
private:
    Ui::MainWindow *ui;
    DOptions *doptions;
    QLabel *timer;
    QStringList filenames;

    // Menús
    QMenuBar *menubar; // Barra de menús
    QMenu *filemenu; // Menú archivo
    QMenu *playmenu; // Menú reproducción
    QMenu *toolsmenu; // Menú herramientas
    QMenu *helpmenu; // Menú ayuda

    // Acciones
    QAction *options;
    QAction *openfileaction;
    QAction *openfileactionTB; // Acción abrir archivo
    QAction *quitaction;
    QAction *quitactionTB; // Acción quitar
    QAction *playaction;
    QAction *playactionTB; // Acción reproducir
    QAction *pauseaction;
    QAction *pauseactionTB; // Acción pausar
    QAction *stopaction;
    QAction *stopactionTB; // Acción detener
    QAction *nextaction;
    QAction *nextactionTB; // Acción siguiente
    QAction *prevaction;
    QAction *prevactionTB; // Accion anterior
    QAction *videooptionsaction;
    QAction *videooptionsactionTB; // Opciones de video
    QAction *aboutDCaction;
    QAction *aboutDCactionTB; // Acerca de DuarteCorp
    QAction *aboutDCMPaction;
    QAction *aboutDCMPactionTB; // Acerca de DC Media Player

    // Lista de reproducción
    QDockWidget *dockwidget; // Panel lateral
    QPushButton *clearfilter; // Limpia filtro
    QLineEdit *filter; // Filtro
    DPlayListWidget *playlistwidget; // Lista de archivos en reproducción
    QPushButton *playNextWhenFinish; // Reproduce siguiente al terminar

    // Progreso multimedia
    QPushButton *fullscreen; // Botón pantalla completa
    QProgressBar *progressbar; // Barra de progreso
    DProgressSlider *progressslider; // Deslizador de progreso
    QPushButton *mutesound; // Botón de silencio
    QSlider *volumeslider; // Deslizador de volumen

    // Objetos multimedia
    DVideoWidget *videowidget; // Salida de video
    QMediaPlayer *mediaplayer; // Reproductor multimedia
    QMediaPlaylist *mediaplaylist; // Lista de reproducción

    // Barras de herramientas
    QToolBar *filetoolbar; // Barra de herramientas de archivo
    QToolBar *playtoolbar; // Barra de herramientas de reproducción
    QToolBar *helptoolbar; // Barra de herramientas de ayuda
    QToolBar *progresstoolbar; // Barra de herramientas de progreso

    // Otros
    DVideoSettingsDialog *videooptionsd; // Diálogo de opciones de video

    // Métodos de inicialización
    void initializeMenus();
    void initializeActions();
    void initializePlayList();
    void initializeMultimediaProgress();
    void initializeMultimediaObjects();
    void initializeToolBars();
    void initializeOthers();
    void initialize(); // Inicializa todo

    // Métodos de configuración
    void configureMenus();
    void configureActions();
    void configurePlayList();
    void configureMultimediaProgress();
    void configureMultimediaObjects();
    void configureToolBars();
    void configureOthers();
    void configure(); // Inicializa todo

    // Métodos de conexión
    void connectActions();
    void connectPlayList();
    void connectMultimediaProgress();
    void connectMultimediaObjects();
    void connections();

    void lastConfigurations();
};

#endif // MAINWINDOW_H
