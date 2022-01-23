#ifndef ZOMBIES_H
#define ZOMBIES_H

#endif // ZOMBIES_H
#pragma once
#include <qvector.h>
#include <qstring.h>

class Zombie
{
public:
    Zombie(int x,int y,int HP,QString pic_path);
    int &x();
    int &y();
    QString getpic();
    bool ismove=1;
    int pos_x;
    int HP;
    QString pic_path;//":/map/images/Zombie.png"
    int pos_y;
};
