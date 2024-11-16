/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* Manages button presses of side menu
*/
#pragma once
#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui { class menu; }

class menu : public QWidget {
    Q_OBJECT
private:
    //! variable for accessing menu UI
    Ui::menu *ui;
public:
    /**
     * creates menu widget
     * @param parent parent widget
     */
    explicit menu(QWidget *parent = nullptr);
    /**
     * Destructor
     */
    ~menu();

private slots:
    /**
     * If load custom game button pressed
     */
    void on_a4loadcustom_clicked();
    /**
     * If play again last game button pressed
     */
    void on_a5playlast_clicked();
    /**
     * If save current game replay button pressed
     */
    void on_a6savereplay_clicked();
    /**
     * If load replay button pressed
     */
    void on_a7loadreplay_clicked();
    /**
     * If exit button pressed
     */
    void on_a8exit_clicked();
signals:
    /**
     * signal: called when exit button pressed
     */
    void custom_exit();
    /**
     * signal: called when save replay button pressed
     * @param qw parent widget
     */
    void save_replay(QWidget* qw);
    /**
     * signal: called when load replay button pressed
     * @param qw parent widget
     */
    void load_replay(QWidget* qw);
    /**
     * signal: called when load game button pressed
     * @param qw parent widget
     */
    void load_game(QWidget* qw);
    /**
     * signal: called when load game again button pressed
     * @param qw parent widget
     */
    void load_game_again();
};
#endif // MENU_H
