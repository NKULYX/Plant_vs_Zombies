#include "game_over.h"
#include "ui_game_over.h"
#include "plants_zombies.h"

Game_Over::Game_Over(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game_Over)
{
    ui->setupUi(this);
}

Game_Over::~Game_Over()
{
    delete ui;
}

void Game_Over::on_pushButton_clicked()
{
    Plants_Zombies *ui_pvz=new Plants_Zombies();
    ui_pvz->show();
    this->close();
}


void Game_Over::on_pushButton_2_clicked()
{
    this->close();
}
