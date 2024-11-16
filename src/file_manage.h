/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* Handles loading and saving of files. Interface functions for adding structured variables to save file.
*/
#pragma once
#ifndef FILE_MANAGE_H
#define FILE_MANAGE_H
#include <QObject>
#include <QString>
#include <fstream>
#include <iostream>
#include "game.h"

class file_manage : public QObject {
    Q_OBJECT
    //singleton
private:
    //! holds singleton instance of file manage
    static file_manage* instance;
    /**
     * Constructor
     */
    file_manage(){saving_file = "";}
public:
    /**
     * Deletes instance
     */
    file_manage(const file_manage &obj) = delete;
    /**
     * Function for accessing file_manage instance. Creates instance when there is none.
     * @returns file_manage* current instance of file_manage
     */
    static file_manage* get_instance() {
        if (instance == NULL)
            instance = new file_manage();
        return instance;
    }
    //singleton

public:
    /**
     * Function for accessing file_manage instance. Creates instance when there is none.
     * @returns file_manage* current instance of file_manage
     */
    void reset_internal_strings();

    /**
     * Adds map(board) of game to save file
     * @param game* pointer to game instance with board
     */
    void add_map(game* game);

    /**
     * Adds GOs, start and end of game to save file.
     * @param game* pointer to game instance with these objects
     */
    void add_objects(game *game);

    /**
     * Adds section delimeter - * - to save file. It separates different parts of replay file
     */
    void add_section_delimeter();

    /**
     * Adds update delimeter - ! - to save file. It separates different parts of step update
     */
    void add_update_delimeter();

    /**
     * Adds step number as line to save file
     * @param step int number of current step
     */
    void add_step(int step);

    /**
     * Adds triplet (set of three values) as line to save file.
     * @param x x position of GO
     * @param y y position of GO
     * @param boolean int number of current step
     */
    void add_triplet(int x, int y, bool boolean);

    /**
     * Adds double (set of two values) as line to save file.
     * @param x x position of GO
     * @param y y position of GO
     */
    void add_double(int x, int y);

    /**
     * Adds triplet (set of two values) as line to save file.
     * @param x x position of GO
     * @param y y position of GO
     */
    void add_double(double x, double y);

    /**
     * Reads file, saves to game board
     */
    void load_board();

private:
    //! string with everything writen by game, upon press of saving file button, this string is outputed. No changes needed.
    QString saving_file;
    //! string for loading from file. Not being used at the moment.
    QString loaded_file;

    /**
     * Adds given string to board, goes trough all tiles, creating image views at correct position.
     * @param game* game instance for board editing
     * @param row_index what row of board should be added to
     * @param row_data string with tiles
     */
    void add_row_to_board(game* game, int row_index, const char* row_data);

public slots:
    /**
     * Called when save replay button pressed, opens file dialog window, outputs saving_file string to file.
     * @param qw* parent widget,
     */
    void saving_r(QWidget* qw);

    /**
     * Called when load replay button pressed, resets instances, opens file dialog window, calls replay class to load its file.
     * @param qw* parent widget,
     */
    void loading_r(QWidget* qw);

    /**
     * Called when load game button pressed, resets instances, opens file dialog window, calls game class to load its file.
     * @param qw* parent widget,
     */
    void loading_g(QWidget* qw);

    /**
     * Called when play again button pressed or reseting game, resets instances, calls game class to load its file.
     */
    void loading_g_again();

    /**
     * Called when reseting replay, resets instances,  calls replay class to load its file.
     */
    void loading_r_again();
};
#endif // FILE_MANAGE_H
