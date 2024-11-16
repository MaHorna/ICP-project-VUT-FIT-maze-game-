/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* Class for handling replay. Parsing file, play logic, step displaying
*/
#pragma once
#ifndef REPLAY_H
#define REPLAY_H
#include <fstream>
#include <QObject>
#include <QTimer>
using namespace std;
#include "game_object.h"
#include "step.h"

class replay : public QObject{
    Q_OBJECT

    //singleton
private:

    //! holds singleton instance of main window
    static replay* instance;

    /**
     * Constructor
     */
    replay(){}
public:

    /**
     * Deletes instance
     */
    replay(const replay &obj) = delete;

    /**
     * Function for accessing replay instance. Creates instance when there is none.
     * @returns replay* current instance of replay
     */
    static replay* get_instance() {
        if (instance == NULL)
            instance = new replay();
        return instance;
    }

    /**
     * Deletes instance, used for reseting
     */
    void delete_instance(){
        delete instance;
        instance = NULL;
    }
    //singleton
public:
    //! Timer, calls step display every x miliseconds
    QTimer *timer;
    //! Tells mainwindow if replay is loaded and keypresses should effect replay instance
    bool is_loaded = false;
    //! State of replay, controls timer - start/pause/play/stopped-reset
    //! 0 = not started, 1 = in progress, 2 = paused, 3 = finished
    int state = 0;
    //! Replay mode
    //! true = forward, false = backward
    bool forward = true;
    //! Replay mode
    //! true = flow, false = step
    bool mod = true;
    //! Holds path to file of replay
    QString file_path = "";
    //! Current displayed step
    int steps = 0;
    //! List of all parsed steps
    std::vector<step*> step_list;
private:
    //! Time of step (how far into game this step happened)
    double play_time = 0;
    //! current score of player
    int score = 0;
    //! current step of player (how many tiles he walked over)
    int step_player = 0;
    //! constant for proper scaling. Pixel size of cell (width and height)
    int cell_size = 40;
    //! Speed of "simulation" - how fast to call stepping function (tick every X miliseconds)
    double simulation_speed = 10.0;
    //! height of board
    int height = 0;
    //! width of board
    int width = 0;
    //! board - 2D array (vectors) with map tiles
    std::vector<std::vector<char>> board;
    //! points to player GO
    game_object* pl;
    //! stores end position (not used variable) (pair of ints)
    std::pair<int,int> end;
    //! stores key GOs
    std::vector<game_object*> key_list;
    //! stores cherry GOs
    std::vector<game_object*> cherry_list;
    //! stores ghost GOs
    std::vector<game_object*> ghost_list;

private:

    /**
     * Parses replay file, gets parameters of board, board, list of ghosts, player, cherries, keys, end, start and list of steps.
     */
    void parse_data();

public:
    /**
     * Displays step with given index -  moves game_objects, changes their visibility, changes labels...
     * @param step - index of step to display
     */
    void show_replay_step(int step);

    /**
     * Gives replay instance a file of replay to play. Parse data, draw board to main window, readies UI and timer
     * @param file_name file path string
     */
    void replay_init(QString file_name);

private slots:
    /**
     * Runs show_replay_step with the step index based on mode of replay - forwards/backwards
     */
    void do_replay_step();

signals:
    /**
     * Signal for changing of labels of main_window
     * @param score - number of cherries pickedup
     * @param step - number of steps made by player
     * @param play_time - play time in seconds
     */
    void update_labels(int score, int step, double play_time);
};

#endif // REPLAY_H
