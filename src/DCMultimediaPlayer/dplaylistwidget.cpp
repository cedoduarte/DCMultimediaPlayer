#include <dplaylistwidget.h>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <mainwindow.h>
#include <QMediaPlayer>

DPlayListWidget::DPlayListWidget(QWidget *parent) : QListWidget(parent) {
    setContextMenuPolicy(Qt::DefaultContextMenu);
    playlist = 0;
    mediaplayer = 0;
    menu = new QMenu(this);
    deleteItem = new QAction(QIcon(":delete.png"), tr("Eliminar"), this);
    deleteAllItems = new QAction(QIcon(":deleteall"),
        tr("Eliminar todos"), this);
    menu->addAction(deleteItem);
    menu->addSeparator();
    menu->addAction(deleteAllItems);
    connect(deleteItem, SIGNAL(triggered()), this,
        SLOT(onDeleteItemTriggered()));
    connect(deleteAllItems, SIGNAL(triggered()), this,
        SLOT(onDeleteAllItemsTriggered()));
    connect(this, SIGNAL(clicked(QModelIndex)), this,
        SLOT(onClicked(QModelIndex)));
}

void DPlayListWidget::onDeleteItemTriggered() {
    if (!playlist->removeMedia(currentRow())) {
        QMessageBox::critical(this, tr("Error"),
            tr("No se ha podido eliminar"));
    }
    delete currentItem(); // Elimina elemento de la lista
}

void DPlayListWidget::onDeleteAllItemsTriggered() {
    if (!playlist->clear()) {
        QMessageBox::critical(this, tr("Error"),
            tr("No se ha podido eliminar"));
    }
    clear(); // Limpia la lista de elementos
}

void DPlayListWidget::onClicked(QModelIndex index) {
    playlist->setCurrentIndex(index.row()); // Reproduce el índice "index"
    mediaplayer->play(); // Reproduce
}

void DPlayListWidget::contextMenuEvent(QContextMenuEvent *e) {
    emit filter();
    menu->setGeometry(cursor().pos().x(), cursor().pos().y(), 174, 49);
    menu->show();
    e->accept();
}
