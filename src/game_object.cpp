#include <cmath>
#include "game_object.h"
#include "game.h"
#include "file_manage.h"
#include "lose_dialog.h"
#include "win_dialog.h"

game_object::game_object(QObject *parent, int type, double x, double y, int current_direction, int next_direction, bool is_picked_up, QGraphicsPixmapItem* image_view){
    this->type = type;
    this->x = x;
    this->y = y;
    this->current_direction = current_direction;
    this->next_direction = next_direction;
    this->is_picked_up = is_picked_up;
    this->image_view = image_view;
}

void game_object::move() {
    bool is_in_middle_of_tile = false;
    int col_index = round(x);
    int row_index = round(y);
    game* game = game::get_instance();
    if(((fmod(x,1) < 0.02) || (fmod(x,1) > 0.98)) && ((fmod(y,1) < 0.02) || (fmod(y,1) > 0.98))) {
        is_in_middle_of_tile = true;
        if(type == 0){ //player
            if (next_direction != current_direction) { //there was input to change direction
                if (!game->check_if_wall_in_dir(row_index, col_index, next_direction)) {
                    current_direction = next_direction; //rotate
                }
            }
        }
        else if(type == 1){ //ghost
            if (game->check_if_wall_in_dir(row_index, col_index, current_direction)) { //player hit wall, no input to change direction present -> automatic movement to empty cell
                while (game->check_if_wall_in_dir(row_index, col_index, current_direction)) { //while there is a wall in current direction
                    current_direction = rand() % 4; //randomly choose new direction
                }
            }
        }
    }

    if (!game->check_if_wall_in_dir(row_index, col_index, current_direction) || !is_in_middle_of_tile) {
        int x_move = 0;
        int y_move = 0;
        if (current_direction == 0) {
            y_move -= 1;
        }
        if (current_direction == 1) {
            x_move += 1;
        }
        if (current_direction == 2) {
            y_move += 1;
        }
        if (current_direction == 3) {
            x_move -= 1;
        }
        if(x<1.95 || y<1.95 || x>game->board[0].size()-2.95 || y>game->board.size()-2.95) {
            game->timer->stop();
            qDebug() << "player is out of bounds";
        }
        x += x_move*0.05;
        y += y_move*0.05;
        image_view->setOffset(x*game->cell_size, y*game->cell_size);
        file_manage::get_instance()->add_double(x*game->cell_size, y*game->cell_size);
    }
}

void game_object::player_step(double x, double y){
    if(((fmod(x,1) < 0.02) || (fmod(x,1) > 0.98)) && ((fmod(y,1) < 0.02) || (fmod(y,1) > 0.98))) {
        if (prev_x != x || prev_y != y){
            file_manage::get_instance()->add_step(step);
            step++;
        }
        prev_x = x;
        prev_y = y;
    }
}

void game_object::player_check_keys(int x, int y) {
    game* game = game::get_instance();
    if (game->get_instance()->check_if_object_in_tile(y, x, 'K')) { //if player stands on any key
        for (size_t i = 0; i < game->key_list.size(); i++) { //cycle keys
            if (game->key_list[i]->x == x && game->key_list[i]->y == y && !game->key_list[i]->is_picked_up) { //if the key is in the same tile as player - found THE key
                game->key_list[i]->is_picked_up = true;
                game->key_list[i]->image_view->setVisible(false);
                file_manage::get_instance()->add_double(i, -1); //key removal "command"
            }
        }
    }
}

void game_object::player_check_cherries(int x, int y) {
    game* game = game::get_instance();
    if (game->check_if_object_in_tile(y, x, '.')) {
        for (size_t i = 0; i < game->cherry_list.size(); i++) {
            if (game->cherry_list[i]->x == x && game->cherry_list[i]->y == y && !game->cherry_list[i]->is_picked_up) {
                game->cherry_list[i]->is_picked_up = true;
                game->cherry_list[i]->image_view->setVisible(false);
                score++;
                file_manage::get_instance()->add_double(i, score); //cherry removal "command"
            }
        }
    }
}

void game_object::player_check_end(int x, int y) {
    game* game = game::get_instance();
    if (game->check_if_object_in_tile(y, x, 'T')) {
        size_t keys_taken = 0;
        for (size_t i = 0; i < game->key_list.size(); i++) {
            if (game->key_list[i]->is_picked_up) {
                keys_taken++;
            }
        }
        if (keys_taken == game->key_list.size()) {
            qDebug()  << "player won";
            game->timer->stop();
            game->state = 3;
            win_dialog* win_d = new win_dialog();
        }
        else {
            qDebug()  << "player not yet collected all keys";
        }
    }
}

void game_object::player_check_ghosts(int x, int y) {
    game* game = game::get_instance();
    for (size_t i = 0; i < game->ghost_list.size(); i++) {
        if (round(game->ghost_list[i]->x) == x && round(game->ghost_list[i]->y) == y) {
            game->timer->stop();
            game->state = 3;
            qDebug() << "player hit a ghost";
            lose_dialog* lose_d = new lose_dialog();
        }
    }
}
