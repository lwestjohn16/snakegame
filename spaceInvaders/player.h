#ifndef PLAYER_H
#define PLAYER_H
#include <QRect>

class player
{
private:
    int lives;
    QRect rect;
    int xcoord, ycoord, xspeed, yspeed;
public:
    player();
};

#endif // PLAYER_H
