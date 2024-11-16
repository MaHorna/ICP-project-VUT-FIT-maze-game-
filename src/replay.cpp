#include <QDebug>
#include <string>
#include "replay.h"
#include "mainwindow.h"
replay* replay::instance;

void replay::replay_init(QString file_name){
    file_path = file_name;
    parse_data();
    MainWindow *mw = MainWindow::getInstance();
    mw->draw_board(board, width-4, height-4);
    mw->show_buttons();
    mw->show_labels();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &replay::do_replay_step);
    connect(this, &replay::update_labels, mw, &MainWindow::change_labels);
}

void replay::parse_data(){
    fstream reader(file_path.toStdString()); //file reader
    string file_data = "";
    if (getline(reader, file_data)) {
        QString tmp_str = QString::fromStdString(file_data); //width and height
        QStringList tmp_list = tmp_str.split(' ');
        height = tmp_list[0].toInt();
        width = tmp_list[1].toInt();
        board = vector<vector<char>>(height); //board array creation
        int row_index = 0;
        while (getline(reader, file_data)){ //parse map
            if (file_data.empty() || file_data == "*") { //found end of map
                break;
            }
            if (file_data.size() != width) {
                qDebug() << "Declared map size mismatch (columns)";
            }
            board[row_index] = vector<char> (file_data.begin(), file_data.end());

            row_index++;
            if (row_index == height+1) { //more rows than declared
                qDebug() << "Declared map size mismatch (more rows)";
            }
        }
        if (row_index<height) { //less rows than declared
            qDebug() << "Declared map size mismatch (less rows)";
        }
        int size = 40;
        QGraphicsPixmapItem* tmp_image_item;

        //get player
        getline(reader, file_data);
        tmp_str = QString::fromStdString(file_data);
        tmp_list = tmp_str.split(' ');
        int x_pos = tmp_list[0].toInt();
        int y_pos = tmp_list[1].toInt();
        tmp_image_item = MainWindow::getInstance()->create_image_view(x_pos*size, y_pos*size, ":/images/game/pacman.png");
        pl = new game_object(this, 0, x_pos, y_pos, 0, 0, false, tmp_image_item);
        getline(reader, file_data);
        if (file_data != "*") {
            qDebug() << "Missing section delimeter, not well formed replay ? 1";
        }

        //get end
        getline(reader, file_data);
        tmp_str = QString::fromStdString(file_data);
        tmp_list = tmp_str.split(' ');
        x_pos = tmp_list[0].toInt();
        y_pos = tmp_list[1].toInt();
        tmp_image_item = MainWindow::getInstance()->create_image_view(x_pos*size, y_pos*size, ":/images/game/trophy.png");
        end = pair<int, int> (x_pos, y_pos);
        getline(reader, file_data);
        if (file_data != "*") {
            qDebug() << "Missing section delimeter, not well formed replay ? 2";
        }

        //get keys
        getline(reader, file_data);
        while (file_data != "*") {
            tmp_str = QString::fromStdString(file_data);
            tmp_list = tmp_str.split(' ');
            x_pos = tmp_list[0].toInt();
            y_pos = tmp_list[1].toInt();
            tmp_image_item = MainWindow::getInstance()->create_image_view(x_pos*size, y_pos*size, ":/images/game/key.png");
            key_list.push_back(new game_object(this, 2, x_pos, y_pos, 0, 0, false, tmp_image_item));
            getline(reader, file_data);
        }

        //get cherries
        getline(reader, file_data);
        while (file_data != "*") {
            tmp_str = QString::fromStdString(file_data);
            tmp_list = tmp_str.split(' ');
            x_pos = tmp_list[0].toInt();
            y_pos = tmp_list[1].toInt();
            tmp_image_item = MainWindow::getInstance()->create_image_view(x_pos*size, y_pos*size, ":/images/game/cherry.png");
            cherry_list.push_back(new game_object(this, 3, x_pos, y_pos, 0, 0, false, tmp_image_item));
            getline(reader, file_data);
        }

        //get ghosts
        getline(reader, file_data);
        while (file_data != "*") {
            tmp_str = QString::fromStdString(file_data);
            tmp_list = tmp_str.split(' ');
            x_pos = tmp_list[0].toInt();
            y_pos = tmp_list[1].toInt();
            tmp_image_item = MainWindow::getInstance()->create_image_view(x_pos*size, y_pos*size, ":/images/game/ghost.png");
            ghost_list.push_back(new game_object(this, 1, x_pos, y_pos, 0, 0, false, tmp_image_item));
            getline(reader, file_data);
        }

        //get steps
        getline(reader, file_data);
        if (file_data.empty() || file_data == "\n") {
            return;
        }
        while (!file_data.empty() || file_data != "\n" || file_data != "") {
            QString player_position = "";
            QString player_step = "";
            QString key_changes = "";
            QString cherry_changes = "";
            vector<QString> ghost_position;
            // Player position
            while (file_data != "!") {
                player_position = QString::fromStdString(file_data);
                getline(reader, file_data);
                if (file_data.empty() || file_data == "\n") {
                    return;
                }
            }
            // Step
            getline(reader, file_data);
            if (file_data.empty() || file_data == "\n") {
                return;
            }
            while (file_data != "!") {
                player_step = QString::fromStdString(file_data);
                getline(reader, file_data);
            }
            // Keys
            getline(reader, file_data);
            if (file_data.empty() || file_data == "\n") {
                return;
            }
            while (file_data != "!") {
                key_changes = QString::fromStdString(file_data);
                getline(reader, file_data);
            }
            // Cherries
            getline(reader, file_data);
            if (file_data.empty() || file_data == "\n") {
                return;
            }
            while (file_data != "!") {
                cherry_changes = QString::fromStdString(file_data);
                getline(reader, file_data);
            }
            // Ghosts moves
            getline(reader, file_data);
            if (file_data.empty() || file_data == "\n") {
                return;
            }
            while (file_data != "*") {
                ghost_position.push_back(QString::fromStdString(file_data));
                getline(reader, file_data);
            }
            step_list.push_back(new step(ghost_position, player_position, key_changes, cherry_changes, player_step));
            ghost_position.clear();
            getline(reader, file_data);
            if (file_data.empty() || file_data == "\n") {
                return;
            }
        }
        qDebug() << "Loaded replay";
    }
    else {
        qDebug() << "File is empty";
    }
}

void replay::do_replay_step(){
    if (forward){
        show_replay_step(steps++);
    }else{
        show_replay_step(steps--);
    }
}

void replay::show_replay_step(int step)
{
    if (step+1 > step_list.size()) { //if trying to show step above the number of steps
        steps = step_list.size()-1;
        step = step_list.size()-1;
    }
    if (step < 0) { //if trying to show steps "before the start of game"
        steps = 0;
        step = 0;
    }
    play_time = step/100;

    //player move
    if (step_list[step]->player != "") {
        QStringList tmp_list = step_list[step]->player.split(' ');
        pl->image_view->setOffset(tmp_list[0].toDouble(), tmp_list[1].toDouble());
    }
    //player steps
    if (step_list[step]->player_step != "") {
        step_player = step_list[step]->player_step.toInt();
    }
    //key changes
    if (step_list[step]->key_changes != "") {
        QStringList tmp_list = step_list[step]->key_changes.split(' ');
        if (forward)
            key_list[tmp_list[0].toInt()]->image_view->setVisible(false);
        else
            key_list[tmp_list[0].toInt()]->image_view->setVisible(true);
    }
    //cherry changes
    if (step_list[step]->cherry_changes != "") {
        QStringList tmp_list = step_list[step]->cherry_changes.split(' ');
        if (forward)
            cherry_list[tmp_list[0].toInt()]->image_view->setVisible(false);
        else
            cherry_list[tmp_list[0].toInt()]->image_view->setVisible(true);
        score = tmp_list[1].toInt();
    }
    //ghosts move
    for (size_t i = 0; i < step_list[step]->ghosts.size(); i++) {
        if (step_list[step]->ghosts[i] != "") {
            QStringList tmp_list = step_list[step]->ghosts[i].split(' ');
            ghost_list[i]->image_view->setOffset(tmp_list[0].toDouble(), tmp_list[1].toDouble());
        }
    }
    //finish
    if (((step+1 == step_list.size()) && forward )|| ((step == 0) && !forward)){
        timer->stop();
        qDebug() << "replay finished";
        state = 2;
    }
    emit update_labels(score, step_player, play_time); //updates labels in main window
}
