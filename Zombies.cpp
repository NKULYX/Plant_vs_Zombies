#include "Zombies.h"

Zombie::Zombie(int x,int y,int HP,QString pic_path)
{
    this->pos_x=x,this->pos_y=y,this->HP=HP,this->pic_path=pic_path;
}


int &Zombie::x()
{
    return this->pos_x;
}

int &Zombie::y()
{
    return this->pos_y;
}

QString Zombie::getpic()
{
    return this->pic_path;
}

