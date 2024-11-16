/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* Class that handles game. game "simulation" calls...
*/
#pragma once
#ifndef GAME_H
#define GAME_H
#include <QDebug>
#include <QString>
#include <QTimer>
#include "game_object.h"

class game : public QObject {
    Q_OBJECT
    //singleton
private:
    //! holds singleton instance of main window
    static game* instance;
    /**
     * Constructor
     */
    game(){}
public:
    /**
     * Deletes instance
     */
    game(const game &obj) = delete;

    /**
     * Function for accessing game instance. Creates instance when there is none.
     * @returns game* current instance of game
     */
    static game* get_instance() {
        if (instance == NULL)
            instance = new game();
        return instance;
    }

    /**
     * Deletes instance, used for reseting
     */
    void delete_instance() {
        delete instance;
        instance = NULL;
    }
    //singleton

private:
    //! Speed of "simulation" - how fast to call stepping function (tick every X miliseconds)
    double simulation_speed = 10.0;     //tick every x miliseconds

public:
    //! Tells mainwindow if game is loaded and keypresses should effect game instance
    bool is_loaded = false;
    //! State of game, controls timer - start/pause/play/stopped-reset
    //! 0 = not started, 1 = in progress, 2 = paused, 3 = finished
    int state = 0;
    //! constant for proper scaling. Pixel size of cell (width and height)
    int cell_size = 40;
    //! Time elapsed in game (is not counting while paused/not yet started)
    double play_time = 0.0;
    //! Holds path to file of game
    QString file_path = "";
    //! height of board
    int height = 0;
    //! width of board
    int width = 0;
    //! Timer, calls game logic every x miliseconds
    QTimer *timer;
    //! points to player GO
    game_object* pl;
    //! board - 2D array (vectors) with map tiles
    std::vector<std::vector<char>> board;
    //! stores start position (pair of ints)
    std::pair<int,int> start;
    //! stores end position (pair of ints)
    std::pair<int,int> end;
    //! stores key GOs
    std::vector<game_object*> key_list;
    //! stores cherry GOs
    std::vector<game_object*> cherry_list;
    //! stores ghost GOs
    std::vector<game_object*> ghost_list;

    /**
     * Checks if object is in tile
     * @param y position of object
     * @param x position of object
     * @param tile char representation of tile
     * @return true if there is searched object
     */
    bool check_if_object_in_tile(int y, int x, char tile);

    /**
     * Checks if wall is in direction
     * @param y position of GO
     * @param x position of GO
     * @param dir direction GO is facing
     * @return true if there is wall
     */
    bool check_if_wall_in_dir(int y, int x, int dir);

    /**
     * Gives game instance a file of game map to play. Parse data, draw board to main window, readies UI and timer
     * @param file_name file path string
     */
    void game_init(QString filename);

public slots:
    /**
     * Game loop function, runs every few miliseconds based on timer calls , calls GO functions for moving , checking, and adds delimeters to file_manage save file.
     */
    void do_sim_step();
signals:
    /**
     * Signal for changing of labels of main_window
     * @param score - number of cherries pickedup
     * @param step - number of steps made by player
     * @param play_time - play time in seconds
     */
    void update_labels(int score, int step, double play_time);
};
#endif // GAME_H
