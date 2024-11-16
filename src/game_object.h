/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* General class for in-game objects - collectibles, player, ghosts
*/
#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <QGraphicsPixmapItem>
#include <QObject>

class game_object : public QObject
{
    Q_OBJECT
public:
    /**
     * Creates game object with given values
     * @param parent - unused
     * @param type - type of object
     * @param x - x board position
     * @param y - y board position
     * @param current_direction - where the object is heading
     * @param next_direction - next heading direction for player object
     * @param is_picked_up - boolean, if objects has been picked up - initialize to false (or true if object is generaly a mandatory object (key) and you dont want it to be mandatory to pick this item)
     * @param item - GUI element representing this object
     */
    game_object(QObject *parent, int type, double x, double y, int current_direction, int next_direction, bool is_picked_up, QGraphicsPixmapItem* item);

    //! Specifies the type of game object
    //! 0 = player, 1 = ghost, 2 = key, 3 = cherry
    //! Applies to all object types
    int type;

    //! X position of object on game/replay board.
    //! Start of boards first cell is at (0,0) , middle of first cell is (0.5, 0.5), first cell ends at (1,1).
    //! Applies to all object types
    double x;

    //! Y position of object on game/replay board.
    //! Start of boards first cell is at (0,0) , middle of first cell is (0.5, 0.5), first cell ends at (1,1).
    //! Applies to all object types
    double y;

    //! Holds current direction. Used in moving the image_view and player position.
    //! 0 = up, 1 = right, 2 = down, 3 = left
    //! Applies to player and ghost
    int current_direction;

    //! Holds next direction to rotate to. This value is passed down to current_direction when rotation possible (middle of tile),
    //! 0 = up, 1 = right, 2 = down, 3 = left
    //! Applies to player
    int next_direction;

    //! Player score counter
    //! Applies to player
    int score=0;

    //! Number of steps of a player
    //! Applies to player
    int step=0;

    //! Previous x position on board, used to determine number of steps
    //! Applies to player
    double prev_x;

    //! Previous y position on board, used to determine number of steps
    //! Applies to player
    double prev_y;

    //! Whether the object was picked up
    //! Applies to key and cherry object
    bool is_picked_up;

    //! Holds shown image
    //! Applies to all object types
    QGraphicsPixmapItem* image_view;

    /**
     * Moves gameobjects (player and ghosts) based on the current/next direction. First checks if rotate is possible - in middle of tile. Then moves internal position and image_view. Logs the move.
     */
    void move();

    /**
     * Counts player steps - if in the middle of tile, and not at the same tile as previously visited (prevents multiple "new steps" happening while at the centre of tile for a few ticks of game).
     * @param x - player x position
     * @param y - player y position
     */
    void player_step(double x, double y);

    /**
     * Checks if player hit key object, removes it, and logs the pickup
     * @param x - player x position
     * @param y - player y position
     */
    void player_check_keys(int x, int y);

    /**
     * Checks if player hit cherry object, removes it, and logs the pickup
     * @param x - player x position
     * @param y - player y position
     */
    void player_check_cherries(int x, int y);

    /**
     * Checks if player hit goal(trophy tile) and if game can be ended (if player collected all keys), shows win dialog window
     * @param x - player x position
     * @param y - player y position
     */
    void player_check_end(int x, int y);

    /**
     * Checks if player object hit ghost object. If player hit ghost game ends, shows lose dialog window
     * @param x - player x position
     * @param y - player y position
     */
    void player_check_ghosts(int x, int y);
};

#endif // GAME_OBJECT_H
