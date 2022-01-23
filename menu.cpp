#include "menu.h"
#include "ui_menu.h"
#include "plants_zombies.h"
#include "diy.h"


Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    present_ui->timer_creat_sun->start(5000);
    present_ui->timer_creat_zombies->start(10000);
    present_ui->timer_move->start(200);
    present_ui->timer_creat_bullet->start(5000);
    this->close();
}

void Menu::on_pushButton_2_clicked()
{
    present_ui->close();
    this->close();
    Plants_Zombies *new_ui=new Plants_Zombies();
    new_ui->show();
}

void Menu::on_pushButton_3_clicked()
{
    present_ui->close();
    this->close();
}

void Menu::on_pushButton_4_clicked()
{
    DIY *diy_ui=new DIY();
    diy_ui->present_ui=this->present_ui;
    diy_ui->show();
}
