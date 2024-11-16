/**
* @file
* @author Matej Horňanský
* @version 1.0
*
* @section DESCRIPTION
* Class holding information about one step of the replay
*/
#pragma once
#ifndef STEP_H
#define STEP_H
#include <QObject>

class step : public QObject{
    Q_OBJECT
public:
    /**
     * Creates step object
     * @param ghosts - list of ghost position changes
     * @param player - player position change
     * @param key_changes - key change
     * @param cherry_changes - cherry change, and score label change
     * @param player_step - step label change
     */
    step(std::vector<QString> ghosts, QString player, QString key_changes, QString cherry_changes, QString player_step);

    //! List of changes to ghost positions (multiple pairs of double values)
    std::vector<QString> ghosts;

    //! Holds changes to player position (pair of double values)
    QString player;

    //! Holds changes to keys - their pickup (int - index of key, int -1 - symbolic command, not really needed in structured replay file like the one being used)
    QString key_changes;

    //! Holds changes to cherris - their pickup, and current score (int - index_of_cherry, int score)
    QString cherry_changes;

    //! Holds changes to step counter label (int current_step_count)
    QString player_step;
};

#endif // STEP_H
