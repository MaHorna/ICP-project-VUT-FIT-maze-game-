/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* Manages keypresses and displaing of the game through graphicsview widget
*/
#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
using namespace std;
#include <QMainWindow>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

protected:
    /**
     * Constructor
     */
    MainWindow(QWidget* = NULL);

public:
    /**
     * Function for accessing main window instance. Creates instance when there is none.
     * @returns MainWindow* current instance of main window
     */
    static MainWindow* getInstance(){
        if(!instance){
            instance = new MainWindow();
        }
        return instance;
    }

private:
    //! holds singleton instance of main window
    static MainWindow* instance;

    //! variable for accessing main window UI
    Ui::MainWindow *ui;

    //! if replay buttons are shown
    bool replay_buttons_shown = true;

    //! if labels are shown
    bool labels_shown = true;

    //! global variable for accessing scene of graphicsview
    QGraphicsScene* scene;

public:
    /**
     * Destructor
     */
    ~MainWindow();

    /**
     * Shows labels, for use in game and replay
     */
    void show_labels();

    /**
     * Hides labels, not used, labels are hidden from the start
     */
    void hide_labels();

    /**
     * Shows buttons, for use in replay
     */
    void show_buttons();

    /**
     * Hides buttons, used in game
     */
    void hide_buttons();

    /**
     * Draws walls with custom drawing algorithm, creating pacman-like walls. General function, used by replay and game when setting up.
     * @param board - 2D array of tiles
     * @param width - width of board
     * @param height - height of board
     * @returns QGraphicsPixmapItem* pointer to item, is generally used to modify its position in scene
     */
    void draw_board(std::vector<std::vector<char>> board, int width, int height);

    /**
     * Finds image by filename, creates image instance, adds instance as item to graphics scene at position
     * @param x - x position of image in pixels starting from top left corner
     * @param y - y position of image in pixels starting from top left corner
     * @returns QGraphicsPixmapItem* pointer to item, is generally used to modify its position in scene
     */
    QGraphicsPixmapItem* create_image_view(int x, int y, std::string filename);

    /**
     * Used when reseting game/replay, changing from game to replay/replay to game , loading game/replay. Deletes instances, resets file_manage variables and clears graphicsscene of main window
     */
    void delete_instances();

    /**
     * Creates game instance and calls its setup. Checks for file existance, even when playing the same map again (load again button)
     */
    void load_game(QString new_file);

    /**
     * Creates replay instance and calls its setup. Checks for file existance
     */
    void load_replay(QString new_file);

protected:
    /**
     * Handles all keyboard events
     * @param event - event that caused this call, holds pressed key code
     */
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    /**
     * Sets labels
     * @param score - new score count
     * @param step - new step count
     * @param play_time - new playtime
     */
    void change_labels(int score, int step, double play_time);

private slots:
    /**
     * Replay button pressed: start
     */
    void on_pushButton_1_clicked();

    /**
     * Replay button pressed: back
     */
    void on_pushButton_2_clicked();

    /**
     * Replay button pressed: play/pause
     */
    void on_pushButton_3_clicked();

    /**
     * Replay button pressed: forward
     */
    void on_pushButton_4_clicked();

    /**
     * Replay button pressed: end
     */
    void on_pushButton_5_clicked();

    /**
     * Replay button pressed: step
     */
    void on_pushButton_6_clicked();

    /**
     * Replay button pressed: flow
     */
    void on_pushButton_7_clicked();
};
#endif // MAINWINDOW_H
