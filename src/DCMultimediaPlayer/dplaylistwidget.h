#ifndef DPLAYLISTWIDGET_H // OK
#define DPLAYLISTWIDGET_H

#include <QListWidget>

class QMenu;
class QMediaPlaylist;
class QMediaPlayer;
class QAction;

/**
 * @brief The DPlayListWidget class
 */
class DPlayListWidget : public QListWidget {
    Q_OBJECT
public:
    /**
     * @brief DPlayListWidget
     * @param parent
     */
    explicit DPlayListWidget(QWidget *parent = 0);

    /**
     * @brief setMediaPlayer
     * @param mymediaplayer
     */
    void setMediaPlayer(QMediaPlayer *mymediaplayer) {
        mediaplayer = mymediaplayer;
    }

    /**
     * @brief setPlaylist
     * @param myplaylist
     */
    void setPlaylist(QMediaPlaylist *myplaylist) {
        playlist = myplaylist;
    }    
protected:
    /**
     * @brief contextMenuEvent
     * @param e
     */
    virtual void contextMenuEvent(QContextMenuEvent *e); // Muestra menú
signals:
    /**
     * @brief filter
     */
    void filter();
private slots:
    void onDeleteItemTriggered(); // Elimina un elementos de la lista
    void onDeleteAllItemsTriggered(); // Elimina todos los elementos
    void onClicked(QModelIndex index); // Clic en la lista de elementos
private:
    QMenu *menu;
    QAction *deleteItem;
    QAction *deleteAllItems;
    QMediaPlaylist *playlist;
    QMediaPlayer *mediaplayer;
};

#endif // DPLAYLISTWIDGET_H
