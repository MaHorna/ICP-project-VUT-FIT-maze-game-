#include <cmath>
#include <QTimer>
#include "file_manage.h"
#include "game.h"
#include "mainwindow.h"
game* game::instance;
file_manage* fm;

void game::game_init(QString filename){
    file_path = filename;
    fm = file_manage::get_instance();
    fm->load_board();
    fm->add_map(this);
    fm->add_objects(this);
    MainWindow *mw = MainWindow::getInstance();
    mw->draw_board(board, width, height);
    mw->show_labels();
    mw->hide_buttons();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &game::do_sim_step);
    connect(this, &game::update_labels, mw, &MainWindow::change_labels);
}

void game::do_sim_step() {
    int x_i = round(pl->x);
    int y_i = round(pl->y);
    pl->move();
    fm->add_update_delimeter(); //after player move update
    pl->player_step(pl->x,pl->y);
    fm->add_update_delimeter(); //after player step count update
    pl->player_check_keys(x_i,y_i);
    fm->add_update_delimeter(); //after key pickup
    pl->player_check_cherries(x_i,y_i);
    fm->add_update_delimeter(); //after cherry pickup
    pl->player_check_end(x_i,y_i); //no FM data entry
    for (size_t i = 0; i<ghost_list.size();i++) { ghost_list[i]->move(); }
    pl->player_check_ghosts(x_i,y_i); //no FM data entry
    fm->add_section_delimeter(); //end update section
    play_time+=0.01;
    emit update_labels(pl->score, pl->step, play_time);
}

bool game::check_if_object_in_tile(int y, int x, char tile) {
    return game::get_instance()->board[y][x] == tile;
}

bool game::check_if_wall_in_dir(int y, int x, int dir) {
    if (dir == 0) {
        y -= 1;
    }
    if (dir == 1) {
        x += 1;
    }
    if (dir == 2) {
        y += 1;
    }
    if (dir == 3) {
        x -= 1;
    }
    return check_if_object_in_tile(y, x, 'X');
}
