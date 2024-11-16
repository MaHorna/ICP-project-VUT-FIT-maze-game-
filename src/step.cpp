#include "step.h"

step::step(std::vector<QString> ghosts, QString player, QString key_changes, QString cherry_changes, QString player_step)
{
    this->ghosts = ghosts;
    this->player = player;
    this->key_changes = key_changes;
    this->cherry_changes = cherry_changes;
    this->player_step = player_step;
}
