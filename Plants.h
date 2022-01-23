#ifndef PLANTS_H
#define PLANTS_H

#endif // PLANTS_H
#pragma once
#include <qvector.h>
#include <qstring.h>
#include <Sun.h>

class Plant
{
public:
    Plant(int x,int y,int type,int HP,QString pic_path);
    int x();
    int y();
    int type;
    QString getpic();
    int HP;
    QString pic_path;//":/map/images/Pea_shooter.png"

private:
    int pos_x;
    int pos_y;
};


class Pea_Bullet
{
public:
    Pea_Bullet(int x,int y)
    {
        this->bullet_x=x,this->bullet_y=y;
    }
    int &x()
    {
        return this->bullet_x;
    }
    int &y()
    {
        return this->bullet_y;
    }
private:
    int bullet_x;//就是实际坐标
    int bullet_y;//就是实际坐标
};
