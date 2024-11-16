/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* Shows win dialog upon hiting trophy
*/
#pragma once
#ifndef WIN_DIALOG_H
#define WIN_DIALOG_H

#include <QDialog>

namespace Ui {class win_dialog;}

class win_dialog : public QDialog{
    Q_OBJECT

public:
    /**
     * Creates dialog
     * @param parent - unused
     */
    win_dialog(QWidget* parent = 0);
    /**
     * Destructor
     */
    ~win_dialog();

private slots:
    /**
     * Closes dialog when custom close button pressed
     */
    void on_pushButton_clicked();

private:
    //! variable for accessing dialog UI
    Ui::win_dialog *ui;
};

#endif // WIN_DIALOG_H
