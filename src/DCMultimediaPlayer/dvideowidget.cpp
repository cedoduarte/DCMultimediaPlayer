#include <dvideowidget.h>
#include <QMenu>
#include <QAction>
#include <mainwindow.h>
#include <QContextMenuEvent>

DVideoWidget::DVideoWidget(QWidget *parent) : QVideoWidget(parent) {
    setContextMenuPolicy(Qt::DefaultContextMenu);
    myparent = static_cast<MainWindow *>(parent);
    menu = new QMenu(this); // Menú contextual
    play = new QAction(QIcon(":play.png"), tr("Reproducir"), this); // Reproducir
    pause = new QAction(QIcon(":pause.png"), tr("Pausar"), this); // Pausar
    stop = new QAction(QIcon(":stop.png"), tr("Detener"), this); // Detener
    next = new QAction(QIcon(":next.png"), tr("Siguiente"), this); // Siguiente
    prev = new QAction(QIcon(":prev.png"), tr("Anterior"), this); // Anterior
    // Abrir archivo
    openfile = new QAction(QIcon(":openfile.png"), tr("Abrir archivo"), this);
    // Pantalla completa
    fullscreen = new QAction(QIcon(":fullscreen.png"),tr("Pantalla completa"),
        this);
    // Opciones de video
    videooptions = new QAction(QIcon(":videooptions.png"),
        tr("Opciones de video"), this);
    // Muestra ventana principal
    showmainwindow = new QAction(QIcon(":mainwindow.png"),
        tr("Muestra ventana principal"), this);
    quit = new QAction(QIcon(":quit.png"), tr("Quitar"), this); // Quita programa
    menu->addAction(play);
    menu->addAction(pause);
    menu->addAction(stop);
    menu->addSeparator();
    menu->addAction(prev);
    menu->addAction(next);
    menu->addSeparator();
    menu->addAction(openfile);
    menu->addSeparator();
    menu->addAction(fullscreen);
    menu->addAction(videooptions);
    menu->addSeparator();
    menu->addAction(showmainwindow);
    menu->addSeparator();
    menu->addAction(quit);
    connect(play, SIGNAL(triggered()), this, SLOT(onPlayTriggered()));
    connect(pause, SIGNAL(triggered()), this, SLOT(onPauseTriggered()));
    connect(stop, SIGNAL(triggered()), this, SLOT(onStopTriggered()));
    connect(next, SIGNAL(triggered()), this, SLOT(onNextTriggered()));
    connect(prev, SIGNAL(triggered()), this, SLOT(onPrevTriggered()));
    connect(openfile, SIGNAL(triggered()), this, SLOT(onOpenFileTriggered()));
    connect(fullscreen, SIGNAL(triggered()),this,SLOT(onFullScreenTriggered()));
    connect(videooptions, SIGNAL(triggered()), this,
        SLOT(onVideoOptionsTriggered()));
    connect(showmainwindow, SIGNAL(triggered()), this,
        SLOT(onShowMainWindowTriggered()));
    connect(quit, SIGNAL(triggered()), this, SLOT(onQuitTriggered()));
}

void DVideoWidget::onPlayTriggered() {
    myparent->onPlayActionTriggered();
}

void DVideoWidget::onPauseTriggered() {
    myparent->onPauseActionTriggered();
}

void DVideoWidget::onStopTriggered() {
    myparent->onStopActionTriggered();
}

void DVideoWidget::onNextTriggered() {
    myparent->onNextActionTriggered();
}

void DVideoWidget::onPrevTriggered() {
    myparent->onPrevActionTriggered();
}

void DVideoWidget::onOpenFileTriggered() {
    myparent->onOpenFileActionTriggered();
}

void DVideoWidget::onFullScreenTriggered() {
    myparent->onFullScreenClicked();
}

void DVideoWidget::onVideoOptionsTriggered() {
    myparent->onVideoOptionsActionTriggered();
}

void DVideoWidget::onShowMainWindowTriggered() {
    myparent->hide();
    myparent->show();
}

void DVideoWidget::onQuitTriggered() {
    myparent->onQuitActionTriggered();
}

void DVideoWidget::contextMenuEvent(QContextMenuEvent *e) {
    menu->setGeometry(cursor().pos().x(), cursor().pos().y(), 200, 239);
    menu->show();
    e->accept();
}

void DVideoWidget::mouseDoubleClickEvent(QMouseEvent *e) {
    onFullScreenTriggered();
    e->accept();
}

void DVideoWidget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape) setFullScreen(false);
    e->accept();
}
