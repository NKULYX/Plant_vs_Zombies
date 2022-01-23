#include "Plants.h"

Plant::Plant(int x,int y,int type,int HP,QString pic_path)
{
    this->pos_x=x,this->pos_y=y,this->type=type,this->pic_path=pic_path,this->HP=HP;
}

int Plant::x()
{
    return this->pos_x;
}

int Plant::y()
{
    return this->pos_y;
}

QString Plant::getpic()
{
    return this->pic_path;
}



