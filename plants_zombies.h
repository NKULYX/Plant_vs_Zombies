#ifndef PLANTS_ZOMBIES_H
#define PLANTS_ZOMBIES_H

#include <QMainWindow>
#include <qqueue.h>
#include "Plants.h"
#include "Zombies.h"
#include "Sun.h"
#include <qlabel.h>
#include <qtimer.h>
#include "game_over.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Plants_Zombies; }
QT_END_NAMESPACE


class Plants_Zombies : public QMainWindow
{
    Q_OBJECT

public:
    Plants_Zombies(QWidget *parent = nullptr);
    ~Plants_Zombies();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);


    //对太阳的一系列操作
    //包括创建太阳 和 计算太阳的总数
    int sum_sun=500;//太阳的数量
    void show_sun_sum();//显示太阳的数量
    QLabel *label_sun=new QLabel(this);

    //------------------------------------------------------

    //对植物选择栏的一系列操作
    //包括判断植物是否能被选中 设置植物的是否被选中的状态 以及植物栏内的图片路径
    bool select_plant=0;//是否选择植物
    bool erase_plant=0;//是否移除植物
    int plant_type;//选定的植物的类型
    void set_blank_state();//判断植物能不能被选择
    bool blank_state[6]={1,1,1,1,0,0};//判断植物是否可以点击
    int plant_cool_down[6]={5,5,10,10,20,5};//植物冷却时长

    //能够选择的植物的图片路径
    QString blank_able[6]={":/map/images/able_Sun_flower.png",":/map/images/able_Pea_shooter.png",":/map/images/able_Wall_nut.png",":/map/images/able_Potato_Mine.png",":/map/images/able_Cherry_Bomb.png",":/map/images/able_Repeater.png"};
    //不能选择的植物的图片路径
    QString blank_unable[6]={":/map/images/unable_Sun_flower.png",":/map/images/unable_Pea_shooter.png",":/map/images/unable_Wall_nut.png",":/map/images/unable_Potato_Mine.png",":/map/images/unable_Cherry_Bomb.png",":/map/images/unable_Repeater.png"};
    //植物所需要的阳光的数量
    int plant_need_sun[6]={50,100,50,25,150,200};

    //僵尸的图片路径
    QString zombies_path[4]={":/map/images/Zombie.png",":/map/images/Conehead_Zombie.png",":/map/images/Bucket_Zombie.png",":/map/images/Flag_Zombie.png"};

    //植物的一系列行为
    void plant_behavior(Plant &p);

    //定时器系列操作
    QTimer *timer_move=new QTimer(this);//用来操作子弹以及僵尸的移动
    QTimer *timer_creat_sun=new QTimer(this);//用来产生太阳
    QTimer *timer_creat_zombies=new QTimer(this);//用来产生僵尸
    QTimer *timer_creat_bullet=new QTimer(this);//用来产生子弹
    int time_creat_zombie=10000;
    int time_creat_sun=5000;

    //判断游戏结束
    int kill_zombies=0;
    void gameover();
    bool game_over=0;
    bool win=-1;



public slots:
    //子弹和僵尸的移动
    void move();

    //检查僵尸和植物是否受到攻击
    void check();

    //创建太阳
    void Creat_Sun();

    //随机产生僵尸
    void Creat_Zombies();

    //产生子弹
    void Creat_Bullet();

    //显示游戏结束
    void Show_Game();



private:
    Ui::Plants_Zombies *ui;
    QQueue<Zombie>zombie;//存放僵尸的队列
    QQueue<Plant>plant;//存放植物的队列
    QQueue<Sun>sun;//存放太阳的队列
    QQueue<Pea_Bullet>bullets;//存放豌豆子弹
    QQueue<Plant>SunFlower;//存放太阳花
    QQueue<Plant>PeaShooter;//存放豌豆射手
    QQueue<Plant>WallNut;//存放坚果墙
    QQueue<Plant>PotatoMine;//存放土豆地雷
    QQueue<Plant>CherryBomb;//存放樱桃炸弹
    QQueue<Plant>Repeater;//存放双枪豌豆
};


#endif // PLANTS_ZOMBIES_H
