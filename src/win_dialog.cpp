#include "win_dialog.h"
#include "ui_win_dialog.h"

win_dialog::win_dialog(QWidget *parent) : QDialog(parent), ui(new Ui::win_dialog){
    ui->setupUi(this);
    show();
}

win_dialog::~win_dialog(){
    delete ui;
}

void win_dialog::on_pushButton_clicked(){
    this->close();
}
