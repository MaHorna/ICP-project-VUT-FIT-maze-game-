#include "lose_dialog.h"
#include "ui_lose_dialog.h"

lose_dialog::lose_dialog(QWidget *parent) : QDialog(parent), ui(new Ui::lose_dialog){
    ui->setupUi(this);
    show();
}

lose_dialog::~lose_dialog(){
    delete ui;
}

void lose_dialog::on_pushButton_clicked(){
    this->close();
}
