#include "menu.h"
#include "ui_menu.h"
#include "file_manage.h"

menu::menu(QWidget *parent) : QWidget(parent), ui(new Ui::menu) {
    ui->setupUi(this);
    file_manage* fm = file_manage::get_instance();
    connect(this, SIGNAL(custom_exit()), qApp, SLOT(quit()));
    connect(this, &menu::save_replay, fm, &file_manage::saving_r);
    connect(this, &menu::load_replay, fm, &file_manage::loading_r);
    connect(this, &menu::load_game, fm, &file_manage::loading_g);
    connect(this, &menu::load_game_again, fm, &file_manage::loading_g_again);
}
menu::~menu(){
    delete ui;
}
void menu::on_a4loadcustom_clicked(){
    emit load_game(this);
}
void menu::on_a5playlast_clicked(){
    emit load_game_again();
}
void menu::on_a6savereplay_clicked(){
    emit save_replay(this);
}
void menu::on_a7loadreplay_clicked(){
    emit load_replay(this);
}
void menu::on_a8exit_clicked(){
    emit custom_exit();
}
