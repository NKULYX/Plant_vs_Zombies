#ifndef SUN_H
#define SUN_H

#endif // SUN_H
#pragma once
#include <qvector.h>
#include <qstring.h>


class Sun
{
public:
    Sun(int x,int y);
    int x();
    int y();
    int addsum();
    QString getpic();
private:
    QString pic_path=":/map/images/Sun.png";
    int sun_x;//实际坐标
    int sun_y;//实际坐标
};
