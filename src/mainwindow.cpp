#include <QFile>
#include <QKeyEvent>
#include "game.h"
#include "mainwindow.h"
#include "replay.h"
#include "ui_mainwindow.h"
#include "file_manage.h"

MainWindow* MainWindow::instance;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphics_view->setScene(scene);
    ui->graphics_view->show();
    hide_labels();
    hide_buttons();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::show_labels(){
    if (!labels_shown) {
        ui->label_1->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        labels_shown = true;
    }
}
void MainWindow::hide_labels(){
    if (labels_shown) {
        ui->label_1->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        labels_shown = false;
    }
}

void MainWindow::show_buttons(){
    if (!replay_buttons_shown) {
        ui->pushButton_1->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(true);
        ui->pushButton_5->setVisible(true);
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        replay_buttons_shown = true;
    }
}
void MainWindow::hide_buttons(){
    if (replay_buttons_shown) {
        ui->pushButton_1->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(false);
        ui->pushButton_4->setVisible(false);
        ui->pushButton_5->setVisible(false);
        ui->pushButton_6->setVisible(false);
        ui->pushButton_7->setVisible(false);
        replay_buttons_shown = false;
    }
}

void MainWindow::change_labels(int score, int step, double play_time){
    ui->label_1->setText(("Score: " + QString::number(score)));
    ui->label_2->setText(("Steps: " + QString::number(step)));
    ui->label_3->setText(("Time: " + QString::number(play_time)));
}

void MainWindow::draw_board(vector<vector<char>> board, int width, int height)
{
    if (board.empty()) {
        return;
    }
    for (int i = 1; i < width+3; i++) { //x
        for (int j = 1; j < height+3; j++) { //y
            if (board[j][i] == 'X') { //we are drawing a wall
                char up = board[j-1][i];
                char down = board[j+1][i];
                char left = board[j][i-1];
                char right = board[j][i+1];
                QPointF point1;
                QPointF point2;
                QPointF point_b;
                QPainterPath path;
                QPen pen = QPen(QColor(0,0,255,255));
                pen.setWidth(2);

                //up right
                point1 = (up == 'X')?QPointF(0.75,0.0):QPointF(0.5,0.25);
                point2 = (right == 'X')?QPointF(1.0,0.25):QPointF(0.75,0.5);
                point1 = QPointF((point1.x()+i)*40, (point1.y()+j)*40); //apply board and graphic position
                point2 = QPointF((point2.x()+i)*40, (point2.y()+j)*40); //apply board and graphic position
                point_b = QPointF((i+0.75)*40, (j+0.25)*40);
                path = QPainterPath();
                path.moveTo(point1);
                path.quadTo(point_b, point2);
                scene->addPath(path, pen, QBrush());
                //up right

                //right down
                point1 = (right == 'X')?QPointF(1.0,0.75):QPointF(0.75,0.5);
                point2 = (down == 'X')?QPointF(0.75,1.0):QPointF(0.5,0.75);
                point1 = QPointF((point1.x()+i)*40, (point1.y()+j)*40); //apply board and graphic position
                point2 = QPointF((point2.x()+i)*40, (point2.y()+j)*40); //apply board and graphic position
                point_b = QPointF((i+0.75)*40, (j+0.75)*40);
                path = QPainterPath();
                path.moveTo(point1);
                path.quadTo(point_b, point2);
                scene->addPath(path, pen, QBrush());
                //right down

                //down left
                point1 = (down == 'X')?QPointF(0.25,1.0):QPointF(0.5,0.75);
                point2 = (left == 'X')?QPointF(0.0,0.75):QPointF(0.25,0.5);
                point1 = QPointF((point1.x()+i)*40, (point1.y()+j)*40); //apply board and graphic position
                point2 = QPointF((point2.x()+i)*40, (point2.y()+j)*40); //apply board and graphic position
                point_b = QPointF((i+0.25)*40, (j+0.75)*40);
                path = QPainterPath();
                path.moveTo(point1);
                path.quadTo(point_b, point2);
                scene->addPath(path, pen, QBrush());
                //down left

                //left up
                point1 = (left == 'X')?QPointF(0.0,0.25):QPointF(0.25,0.5);
                point2 = (up == 'X')?QPointF(0.25,0.0):QPointF(0.5,0.25);
                point1 = QPointF((point1.x()+i)*40, (point1.y()+j)*40); //apply board and graphic position
                point2 = QPointF((point2.x()+i)*40, (point2.y()+j)*40); //apply board and graphic position
                point_b = QPointF((i+0.25)*40, (j+0.25)*40);
                path = QPainterPath();
                path.moveTo(point1);
                path.quadTo(point_b, point2);
                scene->addPath(path, pen, QBrush());
                //left up
            }
        }
    }
}

QGraphicsPixmapItem *MainWindow::create_image_view(int x, int y, std::string filename){
    QPixmap pixmaptmp = QPixmap(QString::fromStdString(filename));
    pixmaptmp = pixmaptmp.scaledToWidth(40, Qt::FastTransformation);
    QGraphicsPixmapItem* qgpi = new QGraphicsPixmapItem(pixmaptmp);
    qgpi->setOffset(x, y);
    scene->addItem(qgpi);
    return qgpi;
}

void MainWindow::on_pushButton_1_clicked(){ //x , start
    replay* replay = replay::get_instance();
    replay->timer->stop();
    replay->state = 2;
    int i = replay->steps;
    replay->forward = false;
    while (i > -1) {
        replay->show_replay_step(i--);
    }
    replay->steps = 0;
    replay->forward = true;
}
void MainWindow::on_pushButton_2_clicked(){ //left arrow, back
    replay* replay = replay::get_instance();
    if (replay->mod){
        replay->forward = false;
    }
    else {
        int i = 0;
        bool tmp = replay->forward;
        replay->forward = false;
        for (i = replay->steps ;i > replay->steps-10; i--) {
            replay->show_replay_step(i);
            if (i == 0){
                break;
            }
        }
        replay->forward = tmp;
        replay->steps = i;
    }
}
void MainWindow::on_pushButton_3_clicked(){ //space , play/pause
    replay* replay = replay::get_instance();
    if (replay->state == 0) { //not yet started
        replay->state = 1; //start replay
        replay->timer->start(10);
        ui->pushButton_3->setIcon(QPixmap(":/images/menu/pause.png"));
    }
    else if (replay->state == 1) { //in progress
        replay->state = 2; //pause replay
        replay->timer->stop();
        ui->pushButton_3->setIcon(QPixmap(":/images/menu/play.png"));
    }
    else if (replay->state == 2 && replay->mod) { //paused
        replay->state = 1; //resume replay
        replay->timer->start(10);
        ui->pushButton_3->setIcon(QPixmap(":/images/menu/pause.png"));
    }
    else if (replay->state == 3) { //finished
        replay->state = 0; //restart replay
        replay->timer->stop();
        ui->pushButton_3->setIcon(QPixmap(":/images/menu/play.png"));
        file_manage::get_instance()->loading_r_again();
    }
}
void MainWindow::on_pushButton_4_clicked(){ //right arrow, next
    replay* replay = replay::get_instance();
    if (replay->mod){
        replay->forward = true;
    }
    else {
        int i = 0;
        bool tmp = replay->forward;
        replay->forward = true;
        for (i = replay->steps ;i < replay->steps+10; i++) {
            replay->show_replay_step(i);
            if (i == replay->step_list.size()-1){
                break;
            }
        }
        replay->forward = tmp;
        replay->steps = i;
    }
}
void MainWindow::on_pushButton_5_clicked(){ //c, end
    replay* replay = replay::get_instance();
    replay->timer->stop();
    replay->state = 2;
    int i = replay->steps;
    replay->forward = true;
    while (i < replay->step_list.size()) {
        replay->show_replay_step(i++);
    }
    replay->steps = replay->step_list.size()-1;
    replay->forward = false;
}
void MainWindow::on_pushButton_6_clicked(){ //step
    replay* replay = replay::get_instance();
    replay->mod = false;
    replay->timer->stop();
    replay->state = 2;
    ui->pushButton_6->setChecked(true);
    ui->pushButton_7->setChecked(false);
}
void MainWindow::on_pushButton_7_clicked(){ //flow
    replay* replay = replay::get_instance();
    replay->mod = true;
    replay->timer->stop();
    replay->state = 2;
    ui->pushButton_6->setChecked(false);
    ui->pushButton_7->setChecked(true);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    game* game = game::get_instance();
    replay* replay = replay::get_instance();
    if (game->is_loaded) {
        int next_dir = -1;
        int key = event->key();
        if (key == Qt::UpArrow || key == Qt::Key_W) {
            next_dir = 0;
        }
        else if (key == Qt::RightArrow || key == Qt::Key_D) {
            next_dir = 1;
        }
        else if (key == Qt::DownArrow || key == Qt::Key_S) {
            next_dir = 2;
        }
        else if (key == Qt::LeftArrow || key == Qt::Key_A) {
            next_dir = 3;
        }
        if (next_dir != -1 && game->pl->current_direction != next_dir) { //change of direction planned for player
            game->pl->next_direction = next_dir;
        }
        if (key == Qt::Key_Space) { //game state logic, pausing and playing , reseting ...
            if (game->state == 0) { //not yet started
                game->state = 1; //start game
                game->timer->start(10);
            }
            else if (game->state == 1) { //in progress
                game->state = 2; //pause game
                game->timer->stop();
            }
            else if (game->state == 2) { //paused
                game->state = 1; //resume game
                game->timer->start(10);
            }
            else if (game->state == 3) { //finished
                game->state = 0; //restart game
                game->timer->stop();
                file_manage::get_instance()->loading_g_again();
            }
        }
    }
    else if (replay->is_loaded) {
        int key = event->key();
        if (key == Qt::Key_Space) { //game state logic, pausing and playing , reseting ...
            if (replay->state == 0) { //not yet started
                replay->state = 1; //start replay
                replay->timer->start(10);
                ui->pushButton_3->setIcon(QPixmap(":/images/menu/pause.png"));
            }
            else if (replay->state == 1) { //in progress
                replay->state = 2; //pause replay
                replay->timer->stop();
                ui->pushButton_3->setIcon(QPixmap(":/images/menu/play.png"));
            }
            else if (replay->state == 2 && replay->mod) { //paused
                replay->state = 1; //resume replay
                replay->timer->start(10);
                ui->pushButton_3->setIcon(QPixmap(":/images/menu/pause.png"));
            }
            else if (replay->state == 3) { //finished
                replay->state = 0; //restart replay
                replay->timer->stop();
                ui->pushButton_3->setIcon(QPixmap(":/images/menu/play.png"));
                file_manage::get_instance()->loading_r_again();
            }
        }
        else if (key == Qt::RightArrow) {
            if (replay->mod){
                replay->forward = true;
            }
            else {
                int i = 0;
                bool tmp = replay->forward;
                replay->forward = true;
                for (i = replay->steps ;i < replay->steps+10; i++) {
                    replay->show_replay_step(i);
                    if (i == replay->step_list.size()-1){
                        break;
                    }
                }
                replay->forward = tmp;
                replay->steps = i;
            }
        }
        else if (key == Qt::LeftArrow) {
            if (replay->mod){
                replay->forward = false;
            }
            else {
                int i = 0;
                bool tmp = replay->forward;
                replay->forward = false;
                for (i = replay->steps ;i < replay->steps-10; i--) {
                    replay->show_replay_step(i);
                    if (i == 0){
                        break;
                    }
                }
                replay->forward = tmp;
                replay->steps = i;
            }
        }
        else if (key == Qt::UpArrow) {
            replay->mod = true;
            replay->timer->stop();
            replay->state = 2;
        }
        else if (key == Qt::DownArrow) {
            replay->mod = false;
            replay->timer->stop();
            replay->state = 2;
        }
        else if (key == Qt::Key_C) {
            replay->timer->stop();
            replay->state = 2;
            int i = replay->steps;
            replay->forward = true;
            while (i < replay->step_list.size()) {
                replay->show_replay_step(i++);
            }
            replay->steps = replay->step_list.size()-1;
            replay->forward = false;
        }
        else if (key == Qt::Key_X) {
            replay->timer->stop();
            replay->state = 2;
            int i = replay->steps;
            replay->forward = false;
            while (i > -1) {
                replay->show_replay_step(i--);
            }
            replay->steps = 0;
            replay->forward = true;
        }
    }
}

void MainWindow::delete_instances(){
    MainWindow::getInstance()->scene->clear();
    file_manage::get_instance()->reset_internal_strings();
    game* game = game::get_instance();
    game->delete_instance();
    replay* replay = replay::get_instance();
    replay->delete_instance();
    ui->label_1->setText("Score: 0");
    ui->label_2->setText("Steps: 0");
    ui->label_3->setText("Time: 0");
}
void MainWindow::load_game(QString new_file){
    if (QFile::exists(new_file)) {
        game* game = game::get_instance();
        game->game_init(new_file);
        game->is_loaded = true;
    }
}
void MainWindow::load_replay(QString new_file){
    if (QFile::exists(new_file)) {
        replay* replay = replay::get_instance();
        replay->replay_init(new_file);
        replay->is_loaded = true;
    }
}
