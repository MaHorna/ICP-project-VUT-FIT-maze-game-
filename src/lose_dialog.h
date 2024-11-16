/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* Shows lose dialog upon hiting ghost
*/
#pragma once
#ifndef LOSE_DIALOG_H
#define LOSE_DIALOG_H

#include <QDialog>

namespace Ui {class lose_dialog;}

class lose_dialog : public QDialog {
    Q_OBJECT

public:
    /**
     * Creates dialog
     * @param parent - unused
     */
    lose_dialog(QWidget* parent = 0);
    /**
     * Destructor
     */
    ~lose_dialog();

private slots:
    /**
     * Closes dialog when custom close button pressed
     */
    void on_pushButton_clicked();

private:
    //! variable for accessing dialog UI
    Ui::lose_dialog *ui;
};

#endif // LOSE_DIALOG_H
