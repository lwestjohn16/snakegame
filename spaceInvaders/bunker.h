#ifndef BUNKER_H
#define BUNKER_H
#include <QRect>

class bunker
{
private:
    int health = 3;
    QRect rect;
    int xcoord, ycoord;
public:
    bunker();
};

#endif // BUNKER_H
