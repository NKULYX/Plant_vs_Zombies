#include "Sun.h"

Sun::Sun(int x,int y)
{
    this->sun_x=x,this->sun_y=y;
}

int Sun::x()
{
    return this->sun_x;
}

int Sun::y()
{
    return this->sun_y;
}

QString Sun::getpic()
{
    return this->pic_path;
}
