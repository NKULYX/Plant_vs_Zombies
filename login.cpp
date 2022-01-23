#include "login.h"
#include "ui_login.h"
#include "plants_zombies.h"



Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setGeometry(200,50,864,544);
}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,864,544,QPixmap(":/map/images/login.png"));
}

void Login::mousePressEvent(QMouseEvent *event)
{
    if(event->x()>=264&&event->x()<=600&&event->y()>=481&&event->y()<=526)
    {
        Plants_Zombies *ui_pvz=new Plants_Zombies();
        ui_pvz->show();
        this->close();
    }
}
