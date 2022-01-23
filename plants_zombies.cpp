#include "plants_zombies.h"
#include "ui_plants_zombies.h"
#include <qpainter.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <qvector.h>
#include <QTime>
#include <qtimer.h>
#include <qfont.h>
#include <qlabel.h>
#include "ui_game_over.h"
#include "menu.h"

Plants_Zombies::Plants_Zombies(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Plants_Zombies)
{
    ui->setupUi(this);
    this->setGeometry(QRect(200,30,900,650));
    Sun tmp(250,550);
    sun.push_back(tmp);
    //设置和产生僵尸相关的计时器
    timer_creat_zombies->start(time_creat_zombie);
    connect(timer_creat_zombies,SIGNAL(timeout()),SLOT(Creat_Zombies()));
    //设置和移动相关的计时器
    timer_move->start(200);
    connect(timer_move,&QTimer::timeout,this,&Plants_Zombies::move);
    //设置和产生太阳相关的计时器
    timer_creat_sun->start(time_creat_sun);
    connect(timer_creat_sun,SIGNAL(timeout()),SLOT(Creat_Sun()));
    //设置和产生子弹相关的计时器
    timer_creat_bullet->start(5000);
    connect(timer_creat_bullet,SIGNAL(timeout()),SLOT(Creat_Bullet()));
}

Plants_Zombies::~Plants_Zombies()
{
    delete ui;
}


void Plants_Zombies::paintEvent(QPaintEvent *event)
{
    //先检查一下植物和僵尸的状态
    check();
    QPainter painter(this);
    //画地图
    painter.drawPixmap(0,150,900,500,QPixmap(":/map/images/MAP.png"));
    //画植物选择栏
    painter.drawPixmap(0,0,760,150,QPixmap(":/map/images/blank.png"));
    set_blank_state();//先设置一下当前植物能否被选中
    for(int i=0;i<6;i++)
        if(blank_state[i])
            painter.drawPixmap(145+i*100,15,85,120,blank_able[i]);
        else
            painter.drawPixmap(145+i*100,15,85,120,blank_unable[i]);
    show_sun_sum();
    //画铲子
    painter.drawPixmap(760,0,140,150,QPixmap(":/map/images/shovel.png"));
    //画豌豆子弹
    for(int i=0;i<bullets.size();i++)
        painter.drawPixmap(bullets[i].x(),bullets[i].y(),25,25,QPixmap(":/map/images/Pea_Bullet.png"));
    //画植物
    for(int i=0;i<6;i++)
        for(int j=0;j<plant.size();j++)
            painter.drawPixmap(plant[j].x()*100,plant[j].y()*100+50,100,100,QPixmap(plant[j].getpic()));
    //画僵尸
    for(int i=0;i<zombie.size();i++)
        painter.drawPixmap(zombie[i].x(),zombie[i].y()+50,100,100,QPixmap(zombie[i].getpic()));
    //画太阳
    for(int i=0;i<sun.size();i++)
        painter.drawPixmap(sun[i].x(),sun[i].y(),75,75,sun[i].getpic());
    if(!game_over)
    {
        gameover();
    }
}


//鼠标点击 先判断位置
//如果在上方植物栏内，就判断是哪个植物 并获取下一次鼠标点击事件 获取要把这个植物种到哪里
//如果点在铲子内，就获取下一次鼠标事件 铲除该处的植物
//如果点在地图内，判断是否有太阳 如果有 太阳消失 并且太阳的数量增加100
void Plants_Zombies::mousePressEvent(QMouseEvent *event)
{
    int click_x=event->x(),click_y=event->y();
    if(game_over)
    {
        Show_Game();
    }
    if(click_x>=145&&click_x<=230&&click_y>=15&&click_y<=135&&select_plant==0&&blank_state[(click_x-100)/100]==1)//点到第一个植物 太阳花 并且现在阳光足够
    {
        select_plant=1,plant_type=0;
    }
    else if(click_x>=245&&click_x<=330&&click_y>=15&&click_y<=135&&select_plant==0&&blank_state[(click_x-100)/100]==1)//点到第二个植物 豌豆射手 并且现在阳光足够
    {
        select_plant=1,plant_type=1;
    }
    else if(click_x>=345&&click_x<=430&&click_y>=15&&click_y<=135&&select_plant==0&&blank_state[(click_x-100)/100]==1)//点到第三个植物 坚果 并且现在阳光足够
    {
        select_plant=1,plant_type=2;
    }
    else if(click_x>=445&&click_x<=530&&click_y>=15&&click_y<=135&&select_plant==0&&blank_state[(click_x-100)/100]==1)//点到第四个植物 土豆地雷 并且现在阳光足够
    {
        select_plant=1,plant_type=3;
    }
    else if(click_x>=545&&click_x<=630&&click_y>=15&&click_y<=135&&select_plant==0&&blank_state[(click_x-100)/100]==1)//点到第五个植物 樱桃炸弹 并且现在阳光足够
    {
        select_plant=1,plant_type=4;
    }
    else if(click_x>=645&&click_x<=730&&click_y>=15&&click_y<=135&&select_plant==0&&blank_state[(click_x-100)/100]==1)//点到第六个植物 双枪豌豆 并且现在阳光足够
    {
        select_plant=1,plant_type=5;
    }
    else if(click_x>=760&&click_x<=900&&click_y>=0&&click_y<=150)//如果点到了铲子的位置 就说明我要移除植物
        erase_plant=1;
    else if(click_x>=0&&click_x<=900&&click_y>=150&&click_y<=650&&select_plant==1)//如果上一次点击选择过了植物
    {
        switch(plant_type)//判断植物的类型
        {
        case 0://太阳花
        {
            Plant tmp_plant(click_x/100,click_y/100,0,100,":/map/images/Sun_flower.png");
            plant.push_back(tmp_plant),SunFlower.push_back(tmp_plant);
            break;
        }
        case 1://豌豆射手
        {
            Plant tmp_plant(click_x/100,click_y/100,1,100,":/map/images/Pea_shooter.png");
            plant.push_back(tmp_plant),PeaShooter.push_back(tmp_plant);
            break;
        }
        case 2://坚果墙
        {
            Plant tmp_plant(click_x/100,click_y/100,2,200,":/map/images/Wall_nut.png");
            plant.push_back(tmp_plant),WallNut.push_back(tmp_plant);
            break;
        }
        case 3://土豆地雷
        {
            Plant tmp_plant(click_x/100,click_y/100,3,100,":/map/images/Potato_Mine.png");
            plant.push_back(tmp_plant),PotatoMine.push_back(tmp_plant);
            break;
        }
        case 4://樱桃炸弹
        {
            Plant tmp_plant(click_x/100,click_y/100,4,100,":/map/images/Cherry_Bomb.png");
            plant.push_back(tmp_plant),CherryBomb.push_front(tmp_plant);
            break;
        }
        case 5://双枪豌豆
        {
            Plant tmp_plant(click_x/100,click_y/100,5,100,":/map/images/Repeater.png");
            plant.push_back(tmp_plant),Repeater.push_back(tmp_plant);
            break;
        }
        }
        sum_sun-=plant_need_sun[plant_type];//要减去种下当前植物所需要的太阳数量
        label_sun->close();//关闭显示太阳数量的标签 避免一次次叠加
        select_plant=0;//重置当前没有选择植物
    }
    else if(click_x>=0&&click_x<=900&&click_y>=150&&click_y<=650&&erase_plant==1)//如果上一次点了铲子
    {
        int index_x=click_x/100,index_y=click_y/100,click_type=-1;//获取点击的位置
        for(int i=0;i<plant.size();i++)//遍历植物队列 寻找该位置的植物
        {
            if(plant[i].x()==index_x&&plant[i].y()==index_y)
            {
                click_type=plant[i].type;
                plant.erase(plant.begin()+i,plant.begin()+i+1);//找到植物就把他删掉
                switch(click_type)
                {
                case 0://如果点到的是太阳花
                {
                    for(int i=0;i<SunFlower.size();i++)//遍历太阳花队列 寻找该位置的植物
                        if(SunFlower[i].x()==index_x&&SunFlower[i].y()==index_y)
                        {
                            SunFlower.erase(SunFlower.begin()+i,SunFlower.begin()+i+1);//找到太阳花就把他删掉
                            break;
                        }
                    break;
                }
                case 1://如果点到的是豌豆射手
                {
                    for(int i=0;i<PeaShooter.size();i++)//遍历豌豆射手队列 寻找该位置的豌豆射手
                        if(PeaShooter[i].x()==index_x&&PeaShooter[i].y()==index_y)
                        {
                            PeaShooter.erase(PeaShooter.begin()+i,PeaShooter.begin()+i+1);//找到豌豆射手就把他删掉
                            break;
                        }
                    break;
                }
                case 5://双枪豌豆
                {
                    for(int i=0;i<Repeater.size();i++)//遍历双枪豌豆队列 寻找该位置的双枪豌豆
                        if(Repeater[i].x()==index_x&&Repeater[i].y()==index_y)
                        {
                            Repeater.erase(Repeater.begin()+i,Repeater.begin()+i+1);//找到双枪豌豆就把他删掉
                            break;
                        }
                    break;
                }
                }
                break;
            }
        }
        erase_plant=0;//不管找没找到 遍历一次之后都要把erase_plant置零
    }
    else if((click_x<0||click_x>900||click_y<150||click_y>650)&&select_plant==1)//当选择过植物后，鼠标电机在地图外侧，则视为无效操作，并重置当前没有选择植物
        select_plant=0,erase_plant=0;
    else//判断是不是点到了太阳
        for(int i=0;i<sun.size();i++)
            if(click_x>=sun[i].x()&&click_x<=sun[i].x()+75&&click_y>=sun[i].y()&&click_y<=sun[i].y()+75)
            {
                sum_sun+=25;
                sun.erase(sun.begin()+i,sun.begin()+i+1);
                //Creat_Sun();
                this->update();
            }
    this->update();
}


//随机产生一个僵尸类型，并且随机给他一个行数，起始的x实在屏幕外的 并压入僵尸的队列中
void Plants_Zombies::Creat_Zombies()
{
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int zombie_type=rand()%10,y=rand()%5;
    switch(zombie_type)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    {
        Zombie tmp_zombie(900,y*100+100,100,zombies_path[0]);
        zombie.push_back(tmp_zombie);
        break;
    }
    case 4:
    case 5:
    case 6:
    {
        Zombie tmp_zombie(900,y*100+100,150,zombies_path[1]);
        zombie.push_back(tmp_zombie);
        break;
    }
    case 7:
    case 8:
    {
        Zombie tmp_zombie(900,y*100+100,200,zombies_path[2]);
        zombie.push_back(tmp_zombie);
        break;
    }
    case 9:
    {
        Zombie tmp_zombie(900,y*100+100,100,zombies_path[3]);
        zombie.push_back(tmp_zombie);
        break;
    }
    }
}


//随机在一个位置产生一个太阳，并把它压到太阳的队列中
//随机选择几个太阳花产生太阳
void Plants_Zombies::Creat_Sun()
{
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x=rand()%9,y=rand()%5;
    Sun tmp_sun(x*100,y*100+150);
    sun.push_back(tmp_sun);
    int flower=rand()%2;
    if(!SunFlower.empty()&&flower)
    {
        int index=rand()%SunFlower.size();
        Sun tmp(SunFlower[index].x()*100+50,SunFlower[index].y()*100+50);
        sun.push_back(tmp);
    }
}


//设置植物选择栏内 植物是否能被选择
void Plants_Zombies::set_blank_state()
{
    for(int i=0;i<6;i++)
        if(plant_need_sun[i]<=sum_sun)
            blank_state[i]=1;
        else
            blank_state[i]=0;
}


// 显示拥有的太阳的数量
void Plants_Zombies::show_sun_sum()
{
    label_sun->setGeometry(50,115,60,20);
    QFont qfont;
    qfont.setPointSize(15);
    label_sun->setFont(qfont);
    label_sun->setNum(sum_sun);
    label_sun->show();
}


//产生子弹
void Plants_Zombies::Creat_Bullet()
{

    for(int i=0;i<PeaShooter.size();i++)//检查豌豆射手
    {
        bool creat=0;
        for(int j=0;j<zombie.size();j++)
            if(zombie[j].y()/100==PeaShooter[i].y())
            {
                creat=1;//在这一行有僵尸 允许产生豌豆
                break;
            }
        if(creat)
        {
            Pea_Bullet bullet(PeaShooter[i].x()*100+50,PeaShooter[i].y()*100+65);
            bullets.push_back(bullet);
        }
    }
    for(int i=0;i<Repeater.size();i++)//检查双枪豌豆
    {
        bool creat=0;
        for(int j=0;j<zombie.size();j++)
            if(zombie[j].y()/100==Repeater[i].y())
            {
                creat=1;//在这一行有僵尸 允许产生豌豆
                break;
            }
        if(creat)
        {
            Pea_Bullet bullet1(Repeater[i].x()*100+50,Repeater[i].y()*100+65),bullet2(Repeater[i].x()*100+75,Repeater[i].y()*100+65);
            bullets.push_back(bullet1),bullets.push_back(bullet2);
        }
    }
}


//移动子弹和僵尸
void Plants_Zombies::move()
{
    for(int i=0;i<bullets.size();i++)
        bullets[i].x()+=5;
    for(int i=0;i<zombie.size();i++)
        if(zombie[i].ismove)
            zombie[i].pos_x-=2;
    this->update();
}


//检查僵尸和植物是否收到攻击 检查僵尸是否遇到植物 遇到植物就不能前进了
void Plants_Zombies::check()
{
    //先检查僵尸是否收到攻击以及僵尸是否能够继续前进 以及植物是否收到攻击
    for(int i=0;i<zombie.size();i++)
    {
        //判断僵尸是否受到攻击
        for(int j=0;j<bullets.size();j++)
        {
            if(bullets[j].y()==zombie[i].y()+65&&bullets[j].x()-zombie[i].x()>=10)//子弹和僵尸在同一行，并且子弹x比僵尸靠后10以上
                zombie[i].HP-=10,bullets.erase(bullets.begin()+j,bullets.begin()+j+1),j--;
        }
        //判断僵尸是否遇到植物
        for(int j=0;j<plant.size();j++)
        {
            if(abs(zombie[i].x()-plant[j].x()*100)<=80&&zombie[i].y()==plant[j].y()*100)//植物和僵尸在同一行 并且两者相差90以内
                {
                    zombie[i].ismove=0,plant[j].HP--;//每100ms收到1点攻击，即1秒十点
                    break;//遇到植物了 就停下来，也不用判断后面是否还有符合的植物
                }
            if(j==plant.size()-1)//如果到了最后一个植物，并且判断完上面的过后没有跳出循环 说明没有植物挡住去路
                zombie[i].ismove=1;//僵尸可以继续移动
        }
    }
    //检查僵尸和植物的血量是否为零 如果为零 就要把它剔除出去
    for(int i=0;i<zombie.size();i++)
        if(zombie[i].HP<=0)//如果血量小于等于0 那么这个僵尸就挂了 就要把它从队列里踢出去 但注意此时i要--
            zombie.erase(zombie.begin()+i,zombie.begin()+i+1),i--,kill_zombies++;
        else if(zombie[i].HP<=100)
            zombie[i].pic_path=zombies_path[0];
    for(int i=0;i<plant.size();i++)
        if(plant[i].HP<=0)//如果血量小于等于0 那么这个植物就挂了 就要把它从队列里踢出去 但注意此时i要--
            plant.erase(plant.begin()+i,plant.begin()+i+1),i--;
    //检查土豆地雷和樱桃炸弹是不是能够引爆
    for(int i=0;i<plant.size();i++)
        if(plant[i].type==3)
        {
            for(int j=0;j<zombie.size();j++)
                if(abs(zombie[j].x()-plant[i].x()*100)<=90&&zombie[j].y()==plant[i].y()*100)
                {
                    zombie.erase(zombie.begin()+j,zombie.begin()+j+1);
                    kill_zombies++;
                    plant[i].HP=0,plant[i].pic_path=":/map/images/Bomb_Mine.png";
                    break;
                }
        }
        else if(plant[i].type==4)
        {
             for(int j=0;j<zombie.size();j++)
                 if(((abs(zombie[j].x()-plant[i].x()*100)<=100&&(abs(zombie[j].y()/100-plant[i].y()))<=1))||(zombie[j].y()/100==plant[i].y()&&abs(zombie[j].x()-plant[i].x()*100)<=100))
                 {
                     zombie.erase(zombie.begin()+j,zombie.begin()+j+1);
                     kill_zombies++;
                     plant[i].HP=0,plant[i].pic_path=":/map/images/Bomb_Cherry.png";
                 }
        }
}


//判断游戏结束
//有僵尸进入到你的房子 或者打死了50个僵尸
void Plants_Zombies::gameover()
{
    if(kill_zombies>=50)
    {
        win=1;//表示赢了
        game_over=1;
        timer_move->stop(),timer_creat_zombies->stop(),timer_creat_sun->stop(),timer_creat_bullet->stop();//计时器暂停
        QPainter painter(this);
        painter.drawPixmap(150,225,600,200,QPixmap(":/map/images/Win.png"));
        //游戏结束了
    }
    for(int i=0;i<zombie.size();i++)
        if(zombie[i].x()<=-20)//表示僵尸进入了你的房子
            {
                timer_move->stop(),timer_creat_zombies->stop(),timer_creat_sun->stop(),timer_creat_bullet->stop();//计时器暂停
                win=0;
                game_over=1;
                break;//游戏也结束了
            }
    if(win==0)
    {
        QPainter painter(this);
        painter.drawPixmap(0,0,900,650,QPixmap(":/map/images/gamelose.png"));
    }
}


//键盘事件 主要是为了获取ESC 来提供菜单窗口
void Plants_Zombies::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        Menu *ui_menu=new Menu();
        ui_menu->present_ui=this;
        timer_creat_zombies->stop(),timer_move->stop(),timer_creat_sun->stop(),timer_creat_bullet->stop();//计时器暂停
        ui_menu->show();
    }
}


void Plants_Zombies::Show_Game()
{        
    Game_Over *ui_gameover=new Game_Over();
    this->close();
    ui_gameover->show();
}
