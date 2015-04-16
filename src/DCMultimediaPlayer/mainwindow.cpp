#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QMenu>
#include <QAction>
#include <QDockWidget>
#include <QPushButton>
#include <QLineEdit>
#include <dplaylistwidget.h>
#include <QProgressBar>
#include <dprogressslider.h>
#include <dvideowidget.h>
#include <QMediaPlaylist>
#include <QToolBar>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <dvideosettingsdialog.h>
#include <QFileDialog>
#include <QFileInfo>
#include <utilities.h>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QLabel>
#include <doptions.h>

MainWindow::MainWindow(const QStringList &myfilenames, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    timer = new QLabel(this);
    ui->statusBar->addPermanentWidget(timer);
    filenames = myfilenames;
    initialize();
    configure();
    connections();
    lastConfigurations();
    doptions = new DOptions(this);
    options = new QAction(tr("Opciones"), this);
    toolsmenu->addAction(options);
    connect(options, SIGNAL(triggered()), doptions, SLOT(exec()));
}

MainWindow::~MainWindow() {
    delete ui;
}

// Métodos de inicialización
void MainWindow::initializeMenus() {
    // Menús
    menubar = new QMenuBar(this); // Barra de menú
    filemenu = new QMenu(tr("Archivo"), this); // Menú archivo
    playmenu = new QMenu(tr("Reproducción"), this); // Menú reproducción
    toolsmenu = new QMenu(tr("Herramientas"), this); // Menú herramientas
    helpmenu = new QMenu(tr("Ayuda"), this); // Menú ayuda
    // Fin menús
}

void MainWindow::initializeActions() {
    // Acciones
    // Acción abrir archivo
    openfileaction = new QAction(QIcon(":openfile.png"),
        tr("Abrir archivo"), this);
    openfileactionTB = new QAction(QIcon(":openfile.png"),
        tr("Abrir archivo"), this);
    // Acción quitar
    quitaction = new QAction(QIcon(":quit.png"), tr("Quitar"), this);
    quitactionTB = new QAction(QIcon(":quit.png"), tr("Quitar"), this);
    // Acción reproducir
    playaction = new QAction(QIcon(":play.png"), tr("Reproducir"), this);
    playactionTB = new QAction(QIcon(":play.png"), tr("Reproducir"), this);
    // Acción pausar
    pauseaction = new QAction(QIcon(":pause.png"), tr("Pausar"), this);
    pauseactionTB = new QAction(QIcon(":pause.png"), tr("Pausar"), this);
    // Acción detener
    stopaction = new QAction(QIcon(":stop.png"), tr("Detener"), this);
    stopactionTB = new QAction(QIcon(":stop.png"), tr("Detener"), this);
    // Acción siguiente
    nextaction = new QAction(QIcon(":next.png"), tr("Siguiente"), this);
    nextactionTB = new QAction(QIcon(":next.png"), tr("Siguiente"), this);
    // Accion anterior
    prevaction = new QAction(QIcon(":prev.png"), tr("Anterior"), this);
    prevactionTB = new QAction(QIcon(":prev.png"), tr("Anterior"), this);
    // Opciones de video
    videooptionsaction = new QAction(QIcon(":videooptions.png"),
        tr("Opciones de video"), this);
    videooptionsactionTB = new QAction(QIcon(":videooptions.png"),
        tr("Opciones de video"), this);
    // Acerca de DuarteCorp
    aboutDCaction = new QAction(QIcon(":aboutDC.png"),
        tr("Acerca de DuarteCorporation"), this);
    aboutDCactionTB = new QAction(QIcon(":aboutDC.png"),
        tr("Acerca de DuarteCorporation"), this);
    // Acerca de DC Media Player
    aboutDCMPaction = new QAction(QIcon(":mainicon.png"),
        tr("Acerca de DC Multimedia Player"), this);
    aboutDCMPactionTB = new QAction(QIcon(":mainicon.png"),
        tr("Acerca de DC Multimedia Player"), this);
    // Fin acciones
}

void MainWindow::initializePlayList() {
    // Lista de reproducción
    dockwidget = new QDockWidget(tr("Lista de reproducción"), this);// Panel lateral
    clearfilter = new QPushButton(QIcon(":clearfilter.png"), "", this); //Filtro
    filter = new QLineEdit(this); // Filtro
    playlistwidget = new DPlayListWidget(this);//Lista archivos en reproducción
    playNextWhenFinish = new QPushButton(QIcon(":playnextwhenfinish.png"),
        tr("Reproduce siguiente al terminar"), this);
    // Fin lista de reproducción
}

void MainWindow::initializeMultimediaProgress() {
    // Progreso multimedia
    fullscreen = new QPushButton(QIcon(":fullscreen.png"),
        tr("Pantalla completa"), this); // Botón pantalla completa
    progressbar = new QProgressBar(this); // Barra de progreso
    progressslider = new DProgressSlider(this); // Deslizador de progreso
    mutesound = new QPushButton(QIcon(":normalsound.png"), "", this);// Silencio
    volumeslider = new QSlider(Qt::Horizontal, this); // Deslizador de volumen
    // Fin progreso multimedia
}

void MainWindow::initializeMultimediaObjects() {
    // Objetos multimedia
    videowidget = new DVideoWidget(this); // Salida de video
    mediaplayer = new QMediaPlayer(this); // Reproductor multimedia
    mediaplaylist = new QMediaPlaylist(this); // Lista de reproducción
    // Fin objetos multimedia
}

void MainWindow::initializeToolBars() {
    // Barras de herramientas
    // Barra de herramientas de archivo
    filetoolbar = new QToolBar(tr("Barra de herramientas de archivo"), this);
    // Barra de herramientas de reproducción
    playtoolbar = new QToolBar(tr("Barra de herramientas de reproducción"),
        this);
    // Barra de herramientas de ayuda
    helptoolbar = new QToolBar(tr("Barra de herramientas de ayuda"), this);
    // Barra de herramientas de progreso
    progresstoolbar = new QToolBar(tr("Barra de herramientas de progreso"),
        this);
    // Fin barras de herramientas
}

void MainWindow::initializeOthers() {
    // Otros
    videooptionsd = new DVideoSettingsDialog(this); // Diálogo opciones de video
    // Fin otros
}

void MainWindow::initialize() { // Inicializa todo
    initializeMenus(); // ok
    initializeActions(); // ok
    initializePlayList(); // ok
    initializeMultimediaProgress(); // ok
    initializeMultimediaObjects(); // ok
    initializeToolBars(); // ok
    initializeOthers(); // ok
}
// Fin métodos de inicialización

// Métodos de configuración
void MainWindow::configureMenus() {
    menubar->addMenu(filemenu); // Menú archivo
    menubar->addMenu(playmenu); // Menú reproducción
    menubar->addMenu(toolsmenu); // Menú herramientas
    menubar->addMenu(helpmenu); // Menú ayuda
    setMenuBar(menubar);
}

void MainWindow::configureActions() {
    // Secuencias de teclas
    openfileaction->setShortcut(QKeySequence("Ctrl+O"));
    quitaction->setShortcut(QKeySequence("Ctrl+Q"));
    playaction->setShortcut(QKeySequence("Ctrl+W"));
    pauseaction->setShortcut(QKeySequence("Ctrl+R"));
    stopaction->setShortcut(QKeySequence("Ctrl+T"));
    nextaction->setShortcut(QKeySequence("Ctrl+Y"));
    prevaction->setShortcut(QKeySequence("Ctrl+U"));
    // Fin de secuencias de teclas
    // Agregado de acciones
    filemenu->addAction(openfileaction); // Acción abrir archivo
    filemenu->addSeparator();
    filemenu->addAction(quitaction); // Acción quitar
    playmenu->addAction(playaction); // Acción reproducir
    playmenu->addAction(pauseaction); // Acción pausar
    playmenu->addAction(stopaction); // Acción detener
    playmenu->addSeparator();
    playmenu->addAction(prevaction); // Accion anterior
    playmenu->addAction(nextaction); // Acción siguiente
    toolsmenu->addAction(videooptionsaction); // Opciones de video
    helpmenu->addAction(aboutDCaction); // Acerca de DuarteCorp
    helpmenu->addAction(aboutDCMPaction); // Acerca de DC Media Player
    // Fin de agregados de acciones
}

void MainWindow::configurePlayList() {
    // Lista de reproducción
    // Panel lateral
    QHBoxLayout *filterlayout = new QHBoxLayout;
    // Limpia filtro
    clearfilter->setToolTip(tr("Limpia filtro de búsqueda"));
    filterlayout->addWidget(clearfilter);
    // Filtro
    filter->setToolTip(tr("Filtro de búsqueda"));
    filterlayout->addWidget(filter);
    QVBoxLayout *docklayout = new QVBoxLayout;
    docklayout->addLayout(filterlayout);
    docklayout->addWidget(playlistwidget); // Lista de archivos en reproducción
    playNextWhenFinish->setCheckable(true);
    // Reproduce siguiente al terminar
    docklayout->addWidget(playNextWhenFinish);
    QWidget *widget = new QWidget(this);
    widget->setLayout(docklayout);
    dockwidget->setWidget(widget);
    dockwidget->setFeatures(0x00);
    addDockWidget(Qt::LeftDockWidgetArea, dockwidget);
    playlistwidget->setPlaylist(mediaplaylist);
    playlistwidget->setMediaPlayer(mediaplayer);
    // Fin lista de reproducción
}

void MainWindow::configureMultimediaProgress() {
    // Progreso multimedia
    mutesound->setCheckable(true); // Botón de silencio
    progresstoolbar->addWidget(fullscreen); // Botón pantalla completa
    progresstoolbar->addSeparator();
    // Barra de progreso
    progressbar->setToolTip(tr("Barra de progreso porcentual"));
    progresstoolbar->addWidget(progressbar);
    progresstoolbar->addSeparator();
    // Deslizador de progreso
    progressslider->setToolTip(tr("Posicionador multimedia"));
    progresstoolbar->addWidget(progressslider);
    progresstoolbar->addSeparator();
    // Botón de silencio
    mutesound->setToolTip(tr("Silenciador de volumen"));
    progresstoolbar->addWidget(mutesound);
    // Deslizador de volumen
    volumeslider->setToolTip(tr("Control de volumen de audio"));
    volumeslider->setMaximumWidth(100);
    volumeslider->setValue(100);
    progresstoolbar->addWidget(volumeslider);
    // Fin progreso multimedia
}

void MainWindow::configureMultimediaObjects() {
    mediaplayer->setVideoOutput(videowidget); // Salida de video
    mediaplayer->setPlaylist(mediaplaylist); // Lista de reproducción
    mediaplayer->setVolume(volumeslider->value()); // Volumen
    setCentralWidget(videowidget);
}

void MainWindow::configureToolBars() {
    // Barra de herramientas de archivo
    filetoolbar->addAction(openfileactionTB); // Acción abrir archivo
    filetoolbar->addAction(quitactionTB); // Acción quitar
    playtoolbar->addAction(playactionTB); // Acción reproducir
    playtoolbar->addAction(pauseactionTB); // Acción pausar
    playtoolbar->addAction(stopactionTB); // Acción detener
    playtoolbar->addSeparator();
    playtoolbar->addAction(prevactionTB); // Accion anterior
    playtoolbar->addAction(nextactionTB); // Acción siguiente
    playtoolbar->addAction(videooptionsactionTB); // Opciones de video
    helptoolbar->addAction(aboutDCactionTB); // Acerca de DuarteCorp
    helptoolbar->addAction(aboutDCMPactionTB); // Acerca de DC Media Player
    addToolBar(Qt::TopToolBarArea, filetoolbar);
    // Barra de herramientas de progreso
    addToolBar(Qt::BottomToolBarArea, progresstoolbar);
    // Barra de herramientas de reproducción
    addToolBar(Qt::TopToolBarArea, playtoolbar);
    // Barra de herramientas de ayuda
    addToolBar(Qt::TopToolBarArea, helptoolbar);
    filetoolbar->setFloatable(false);
    progresstoolbar->setFloatable(false);
    playtoolbar->setFloatable(false);
    helptoolbar->setFloatable(false);
}

void MainWindow::configureOthers() {
    videooptionsd->setVideoWidget(videowidget);
}

void MainWindow::configure() { // Inicializa todo
    setAcceptDrops(true);
    setWindowTitle("DuarteCorp Multimedia Player");
    setWindowIcon(QIcon(":mainicon.png"));
    configureMenus(); // ok
    configureActions(); // ok
    configurePlayList(); // ok
    configureMultimediaProgress(); // ok
    configureMultimediaObjects(); // ok
    configureOthers(); // ok
    configureToolBars(); // ok
}
// Fin métodos de configuración

// Métodos de conexión
void MainWindow::connectActions() {
    // Acción abrir archivo
    connect(openfileaction, SIGNAL(triggered()), this,
        SLOT(onOpenFileActionTriggered()));
    connect(openfileactionTB, SIGNAL(triggered()),
        this, SLOT(onOpenFileActionTriggered()));
    // Acción quitar
    connect(quitaction, SIGNAL(triggered()), this,
        SLOT(onQuitActionTriggered()));
    connect(quitactionTB, SIGNAL(triggered()), this,
        SLOT(onQuitActionTriggered()));
    // Acción reproducir
    connect(playaction, SIGNAL(triggered()), this,
        SLOT(onPlayActionTriggered()));
    connect(playactionTB, SIGNAL(triggered()), this,
        SLOT(onPlayActionTriggered()));
    // Acción pausar
    connect(pauseaction, SIGNAL(triggered()), this,
        SLOT(onPauseActionTriggered()));
    connect(pauseactionTB, SIGNAL(triggered()), this,
        SLOT(onPauseActionTriggered()));
    // Acción detener
    connect(stopaction, SIGNAL(triggered()), this,
        SLOT(onStopActionTriggered()));
    connect(stopactionTB, SIGNAL(triggered()), this,
        SLOT(onStopActionTriggered()));
    // Acción siguiente
    connect(nextaction, SIGNAL(triggered()), this,
        SLOT(onNextActionTriggered()));
    connect(nextactionTB, SIGNAL(triggered()), this,
        SLOT(onNextActionTriggered()));
    // Accion anterior
    connect(prevaction, SIGNAL(triggered()), this,
        SLOT(onPrevActionTriggered()));
    connect(prevactionTB, SIGNAL(triggered()), this,
        SLOT(onPrevActionTriggered()));
    // Opciones de video
    connect(videooptionsaction, SIGNAL(triggered()), this,
        SLOT(onVideoOptionsActionTriggered()));
    connect(videooptionsactionTB, SIGNAL(triggered()), this,
        SLOT(onVideoOptionsActionTriggered()));
    // Acerca de DuarteCorp
    connect(aboutDCaction, SIGNAL(triggered()), this,
        SLOT(onAboutDCactionTriggered()));
    connect(aboutDCactionTB, SIGNAL(triggered()), this,
        SLOT(onAboutDCactionTriggered()));
    // Acerca de DC Media Player
    connect(aboutDCMPaction, SIGNAL(triggered()), this,
        SLOT(onAboutDCMPactionTriggered()));
    connect(aboutDCMPactionTB, SIGNAL(triggered()), this,
        SLOT(onAboutDCMPactionTriggered()));
}

void MainWindow::connectPlayList() {
    // Limpia filtro
    connect(clearfilter, SIGNAL(clicked()), this, SLOT(onClearFilterClicked()));
    connect(playlistwidget, SIGNAL(filter()), this,
        SLOT(onClearFilterClicked()));
    // Filtro
    connect(filter, SIGNAL(textEdited(QString)), this,
        SLOT(onFilterTextEdited(QString)));
}

void MainWindow::connectMultimediaProgress() {
    // Botón pantalla completa
    connect(fullscreen, SIGNAL(clicked()), this, SLOT(onFullScreenClicked()));
    // Deslizador de progreso
    connect(progressslider, SIGNAL(valueChanged(int)), progressbar,
        SLOT(setValue(int))); // Con barra de progreso
    connect(progressslider, SIGNAL(playMultimedia()), this,
        SLOT(onPlayMultimedia()));
    connect(progressslider, SIGNAL(pauseMultimedia()), this,
        SLOT(onPauseMultimedia()));
    // Botón de silencio
    connect(mutesound, SIGNAL(clicked(bool)), this,
        SLOT(onMuteSoundClicked(bool)));
    // Deslizador de volumen
    connect(volumeslider, SIGNAL(valueChanged(int)), this,
        SLOT(onVolumeSliderValueChanged(int)));
}

void MainWindow::connectMultimediaObjects() {
    // MediaPlayer
    connect(mediaplayer, SIGNAL(durationChanged(qint64)), this,
        SLOT(onDurationChanged(qint64)));
    connect(mediaplayer, SIGNAL(positionChanged(qint64)), this,
        SLOT(onPositionChanged(qint64)));
    connect(mediaplayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
        this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
}

void MainWindow::connections() {
    connectActions();
    connectPlayList();
    connectMultimediaProgress();
    connectMultimediaObjects();
}

void MainWindow::lastConfigurations() {
    if (filenames.size() != 0) { // Tiene contenido para leer
        for (int i = 0; i < filenames.size(); ++i) {
            const QString filename = filenames.at(i);
            // Agregar a lista de archivos
            mediaplaylist->addMedia(QUrl::fromLocalFile(filename));
            // Agregar a lista de reproducción
            playlistwidget->addItem(new QListWidgetItem(QIcon(getIconType(
                getFileType(getFileExtension(filename)))), filename));
        }
        // Iniciar la reproducción
        mediaplaylist->setCurrentIndex(0);
        mediaplayer->play();
    }
}
// Fin métodos de conexión

// Ranuras
// Acciones
void MainWindow::onOpenFileActionTriggered() {
    QFileDialog fldao(this);
    fldao.setWindowTitle(tr("Abrir archivo"));
    fldao.setAcceptMode(QFileDialog::AcceptOpen);
    fldao.setFileMode(QFileDialog::ExistingFiles);
    if (fldao.exec() == QDialog::Rejected) return;
    foreach (const QString &filename, fldao.selectedFiles()) {
        // Agregar a lista de archivos
        mediaplaylist->addMedia(QUrl::fromLocalFile(QFileInfo(filename).
            absoluteFilePath()));
        // Agregar a lista de reproducción
        playlistwidget->addItem(new QListWidgetItem(QIcon(getIconType(
            getFileType(getFileExtension(filename)))), filename));
    }
    // Iniciar la reproducción
    mediaplaylist->setCurrentIndex(0);
    mediaplayer->play();
}

void MainWindow::onQuitActionTriggered() {
    close();
}

void MainWindow::onPlayActionTriggered() {
    mediaplayer->play();
}

void MainWindow::onPauseActionTriggered() {
    mediaplayer->pause();
}

void MainWindow::onStopActionTriggered() {
    mediaplayer->stop();
}

void MainWindow::onNextActionTriggered() {
    mediaplaylist->next();
    mediaplayer->play();
    playlistwidget->setCurrentRow(mediaplaylist->currentIndex());
}

void MainWindow::onPrevActionTriggered() {
    mediaplaylist->previous();
    mediaplayer->play();
    playlistwidget->setCurrentRow(mediaplaylist->currentIndex());
}

void MainWindow::onVideoOptionsActionTriggered() {
    videooptionsd->show();
}

void MainWindow::onAboutDCactionTriggered() {
    QString msg = "DuarteCorporation\n";
    msg += "Fundador: Carlos Enrique Duarte Ortiz\n";
    msg += "Fecha: 1 de enero de 2000\n";
    msg += "Objetivo: Desarrollo de software a todos los niveles";
    QMessageBox::information(this, "Acerca de DuarteCorporation", msg);
}

void MainWindow::onAboutDCMPactionTriggered() {
    QString msg = "Compañía: DuarteCorporation\n";
    msg += "Autor: Carlos Enrique Duarte Ortiz\n";
    msg += "Fecha: 11/04/2013\n";
    msg += "Software: DuarteCorp Multimedia Player";
    QMessageBox::about(this, "Acerca de DuarteCorp Multimedia Player", msg);
}
// Fin acciones

// Lista de reproducción
void MainWindow::onClearFilterClicked() { // Limpia filtro
    filter->clear(); // Limpiar texto
    playlistwidget->clear(); // Limpiar lista
    // Cargar todo desde multimediaplaylist
    for (int i = 0; i < mediaplaylist->mediaCount(); ++i) {
        const QString filename = mediaplaylist->media(i).canonicalUrl().
            toLocalFile();
        playlistwidget->addItem(new QListWidgetItem(QIcon(getIconType(
            getFileType(getFileExtension(filename)))), filename));
    }
}

void MainWindow::onFilterTextEdited(const QString &txt) { // Filtro
    // Limpiar lista de archivos
    playlistwidget->clear();
    // Leer todos los archivos multimedia
    for (int i = 0; i < mediaplaylist->mediaCount(); ++i) {
        const QString url = mediaplaylist->media(i).canonicalUrl().toString();
        if (url.contains(txt, Qt::CaseInsensitive)) {
            const QString filename = mediaplaylist->media(i).canonicalUrl().
                toLocalFile();
            if (filename.contains(txt, Qt::CaseInsensitive)) {
                playlistwidget->addItem(new QListWidgetItem(QIcon(getIconType(
                    getFileType(getFileExtension(filename)))), filename));
            }
        }
    }
}
// Fin lista de reproducción

// Progreso multimedia
void MainWindow::onFullScreenClicked() { // Botón pantalla completa
    videowidget->setFullScreen(!videowidget->isFullScreen());
}

void MainWindow::onMuteSoundClicked(bool checked) { // Botón de silencio
    if (checked) { // Silencio
        mutesound->setIcon(QIcon(":mutedsound.png")); // Icono de silencio
        mediaplayer->setMuted(true);
        return;
    }
    mutesound->setIcon(QIcon(":normalsound.png"));
    mediaplayer->setMuted(false);
}

void MainWindow::onVolumeSliderValueChanged(int val) { // Deslizador de volumen
    mediaplayer->setVolume(val);
}

void MainWindow::onPauseMultimedia() {
    // Desconecta temporalmente del cambio de valor del deslizador
    disconnect(mediaplayer, SIGNAL(positionChanged(qint64)), this,
        SLOT(onPositionChanged(qint64)));
    mediaplayer->pause(); // Pausa el medio de reproducción
}

void MainWindow::onPlayMultimedia() {
    // Conecta mediaplayer con cambio de posición
    connect(mediaplayer, SIGNAL(positionChanged(qint64)), this,
        SLOT(onPositionChanged(qint64)));
    // Establece prosición actual del deslizador de progreso
    mediaplayer->setPosition(progressslider->value());
    mediaplayer->play(); // Reproduce el medio
}
// Fin de progreso multimedia

// Objetos multimedia
void MainWindow::onDurationChanged(qint64 dur) {
    progressbar->setMaximum((int) dur); // Barra de progreso
    progressslider->setMaximum((int) dur); // Deslizador de progreso
}

void MainWindow::onPositionChanged(qint64 pos) {
    progressbar->setValue((int) pos); // Barra de progreso
    progressslider->setValue((int) pos); // Deslizador de progreso
    // Tiempo actual
    int total = (int) mediaplayer->duration();
    QString strTotal, strCurrent;
    double msec = total, seg = msec / 1000.0, min = seg / 60.0;
    seg = int((min - int(min)) * 60.0);
    min = int(min);
    strTotal = QString::number(min) + ":" + QString::number(seg);
    msec = pos;
    seg = msec / 1000.0;
    min = seg / 60.0;
    seg = int((min - int(min)) * 60.0);
    min = int(min);
    strCurrent = QString::number(min) + ":" + QString::number(seg);
    timer->setText(strCurrent + "/" + strTotal);
    // Número de archivos
    timer->setText(tr("Número de archivos: %1\t\t\t%2").
        arg(playlistwidget->count()).arg(timer->text()));
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus s) {
    switch (s) {
    // Nada para hacer
    case QMediaPlayer::UnknownMediaStatus: break;
    case QMediaPlayer::NoMedia: break;
    case QMediaPlayer::LoadingMedia: break;
    case QMediaPlayer::LoadedMedia: break;
    case QMediaPlayer::BufferingMedia: break;
    case QMediaPlayer::BufferedMedia: break;
    // Fin de nada para hacer
    // Control de estado
    case QMediaPlayer::StalledMedia:
        QMessageBox::critical(this, tr("Error"), tr("Archivo estancado"));
        break;
    case QMediaPlayer::EndOfMedia: {
            // Reproducir siguiente
            if (playNextWhenFinish->isChecked()) {
                mediaplaylist->next();
                mediaplayer->play();
                playlistwidget->setCurrentRow(mediaplaylist->currentIndex());
            } else mediaplayer->pause();
        }
        break;
    case QMediaPlayer::InvalidMedia:
        QMessageBox::critical(this, tr("Error"), tr("Archivo inválido"));
        break;
    // Fin de control de estado
    }
}

// Fin objetos multimedia
// Fin ranuras

// Redefiniciones
void MainWindow::dragEnterEvent(QDragEnterEvent *e) {
    e->accept();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *e) {
    e->accept();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *e) {
    e->accept();
}

void MainWindow::dropEvent(QDropEvent *e) {
    foreach (const QUrl &url, e->mimeData()->urls()) {
        const QString filename = url.toLocalFile();
        // Agregar a lista de archivos
        mediaplaylist->addMedia(QUrl::fromLocalFile(QFileInfo(filename).
            absoluteFilePath()));
        // Agregar a lista de reproducción
        playlistwidget->addItem(new QListWidgetItem(QIcon(getIconType(
            getFileType(getFileExtension(filename)))), filename));
    }
    e->accept();
}
// Fin redefiniciones

