#include <QFileDialog>
#include "file_manage.h"
#include "game.h"
#include "game_object.h"
#include "mainwindow.h"
#include "replay.h"
using namespace std;
file_manage* file_manage::instance;

void file_manage::reset_internal_strings() {
    saving_file = "";
    loaded_file = "";
}

//saving

void file_manage::add_map(game* game) {
    saving_file += QString::number(game->board.size()) + " " + QString::number(game->board[0].size()) + "\n";
    for (size_t i = 0; i < game->board.size(); i++) {
        for (size_t j = 0; j < game->board[0].size(); j++) {
            saving_file += game->board[i][j];
        }
        saving_file += "\n";
    }
    add_section_delimeter();
}
void file_manage::add_objects(game* game) {
    //player info
    if (game->start.first == 0 && game->start.second == 0) { //uninitialized
        qDebug() << "missing start in game file";
    }
    else {
        add_double(game->start.first, game->start.second);
        add_section_delimeter();
    }
    //end info
    if (game->end.first == 0 && game->end.second == 0) { //uninitialized
        qDebug() << "missing end in game file";
    }
    else {
        add_double(game->end.first, game->end.second);
        add_section_delimeter();
    }
    //keys info
    for (size_t k_i = 0; k_i < game->key_list.size(); ++k_i) {
        add_triplet(game->key_list[k_i]->x, game->key_list[k_i]->y, true);
    }
    add_section_delimeter();
    //cherry info
    for (size_t c_i = 0; c_i < game->cherry_list.size(); ++c_i) {
        add_triplet(game->cherry_list[c_i]->x, game->cherry_list[c_i]->y, true);
    }
    add_section_delimeter();
    //ghost info
    for (size_t g_i = 0; g_i < game->ghost_list.size(); ++g_i) {
        add_double(game->ghost_list[g_i]->x, game->ghost_list[g_i]->y);
    }
    add_section_delimeter();
}
void file_manage::add_section_delimeter() {
    saving_file += "*\n";
}
void file_manage::add_update_delimeter() {
    saving_file += "!\n";
}
void file_manage::add_step(int step) {
    saving_file += QString::number(step) + "\n";
}
void file_manage::add_triplet(int x, int y, bool boolean) {
    saving_file += QString::number(x) + " " + QString::number(y) + " " + QString::number(boolean) + "\n";
}
void file_manage::add_double(int x, int y) {
    saving_file += QString::number(x) + " " + QString::number(y) + "\n";
}
void file_manage::add_double(double x, double y) {
    saving_file += QString::number(x) + " " + QString::number(y) + "\n";
}
void file_manage::saving_r(QWidget* qw){
    qDebug() << "saving";
    if (saving_file != "") { //if there is something to save
        QString filename= QFileDialog::getSaveFileName(qw, "Save replay");
        if (!filename.isEmpty()){ //if dialog not closed/failed
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
                QTextStream out(&file);
                out << saving_file;
                file.close();
            }
        }
    }
}
//saving

//loading
void file_manage::loading_r(QWidget* qw) {
    MainWindow::getInstance()->delete_instances();
    QString file_name = QFileDialog::getOpenFileName(qw,tr("Open replay file"), "", tr("Text files (*.txt)"));
    MainWindow::getInstance()->load_replay(file_name);
}
void file_manage::loading_g(QWidget* qw) {
    MainWindow::getInstance()->delete_instances();
    QString file_name = QFileDialog::getOpenFileName(qw,tr("Open game map file"), "", tr("Text files (*.txt)"));
    MainWindow::getInstance()->load_game(file_name);
}
void file_manage::loading_g_again() {
    QString file_name = game::get_instance()->file_path;
    MainWindow::getInstance()->delete_instances();
    MainWindow::getInstance()->load_game(file_name);
}
void file_manage::loading_r_again() {
    QString file_name = replay::get_instance()->file_path;
    MainWindow::getInstance()->delete_instances();
    MainWindow::getInstance()->load_replay(file_name);
}
void file_manage::add_row_to_board(game* game, int row, const char row_data[]) {
    if (strlen(row_data) != (size_t)game->width) {
        qDebug() << "Declared map size mismatch (columns)";
    }
    for (int i = 2; i < game->width+2; i++) {
        char c = row_data[i-2];
        MainWindow* mw = MainWindow::getInstance();
        QGraphicsPixmapItem* tmp_image_item;
        int size = game->cell_size;
        if (c == 'S') { //start
            game->start = pair<int, int> (i, row);
            tmp_image_item = mw->create_image_view(i*size, row*size, ":/images/game/pacman.png");
            game->pl = new game_object(game, 0, i, row, 0, 0, false, tmp_image_item);
        }
        if (c == 'K') { //key
            tmp_image_item = mw->create_image_view(i*size, row*size, ":/images/game/key.png");
            game->key_list.push_back(new game_object(game, 2, i, row, 0, 0, false, tmp_image_item));
        }
        if (c == '.') { //cherry
            tmp_image_item = mw->create_image_view(i*size, row*size, ":/images/game/cherry.png");
            game->cherry_list.push_back(new game_object(game, 3, i, row, 0, 0, false, tmp_image_item));
        }
        if (c == 'G') { //ghost
            tmp_image_item = mw->create_image_view(i*size, row*size, ":/images/game/ghost.png");
            game->ghost_list.push_back(new game_object(game, 1, i, row, 0, 0, false, tmp_image_item));
        }
        if (c == 'T') { //end
            mw->create_image_view(i*size, row*size, ":/images/game/trophy.png");
            game->end = pair<int, int> (i, row);
        }
        game->board[row][i] = c; //content
    }
}
void file_manage::load_board() {
    game* game = game::get_instance();
    fstream read_file(game->file_path.toStdString()); //file reader
    string file_data = "";

    if (getline(read_file, file_data)) {
        int delim = file_data.find(" "); //getting params
        game->height = stoi(file_data.substr(0, delim));
        game->width = stoi(file_data.substr(delim+1, file_data.size()-delim-1));

        game->board = vector<vector<char>>(game->height+4); //board array creation
        for (int i = 0; i < game->height+4; ++i) {
            game->board[i] = vector<char>(game->width+4);
        }

        for (int i = 0; i < game->height+4; i++) { //adds top and bottom border
            game->board[i][0] = '.';
            if (i == 0 || i == game->height+3) {
                game->board[i][1] = '.';
                game->board[i][game->width+2] = '.';
            }
            else {
                game->board[i][1] = 'X';
                game->board[i][game->width+2] = 'X';
            }
            game->board[i][game->width+3] = '.';
        }
        int row_index = 2;
        while (getline(read_file, file_data)){
            add_row_to_board(game, row_index, file_data.data());
            row_index++;
            if (row_index-2 == game->height+1) { //more rows than declared
                qDebug() << "Declared map size mismatch (more rows)";
            }
        }
        if (row_index+2<game->height) { //less rows than declared
            qDebug() << "Declared map size mismatch (less rows)";
        }
        for (int i = 2; i < game->width+2; i++){
            game->board[0][i] = '.'; //adds left border
            game->board[1][i] = 'X'; //adds left border
            game->board[game->height+2][i] = 'X'; //adds right border
            game->board[game->height+3][i] = '.'; //adds right border
        }
    }
    else {
        qDebug() << "File is empty";
    }
    read_file.close();
}
//loading
