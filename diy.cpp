#include "diy.h"
#include "ui_diy.h"
#include <qstring.h>
#include <QFileDialog>
#include <qdebug.h>
#include <QMessageBox>
#include <QScrollBar>

DIY::DIY(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DIY)
{
    ui->setupUi(this);
}


DIY::~DIY()
{
    delete ui;
}

void DIY::paintEvent(QPaintEvent*event)
{
    QPushButton* button[4]={ui->Zombie,ui->Conehead_Zombie,ui->Bucket_Zombie,ui->Flag_Zombie};
    for(int i=0;i<4;i++)
    {
        button[i]->setStyleSheet("empty");
        QIcon icon;
        icon.addFile(present_ui->zombies_path[i]);
        button[i]->setIconSize(QSize(100,100));
        button[i]->setIcon(icon);
    }
}


void DIY::on_Zombie_clicked()
{
    QString Zombie_path=QFileDialog::getOpenFileName(this,"open file");
    if(!Zombie_path.isEmpty())
    {
        present_ui->zombies_path[0]=Zombie_path;
        ui->Zombie->setStyleSheet("empty");
        QIcon icon;
        icon.addFile(Zombie_path);
        ui->Zombie->setIconSize(QSize(100,100));
        ui->Zombie->setIcon(icon);
    }
}


void DIY::on_Conehead_Zombie_clicked()
{
    QString Conehead_Zombie_path=QFileDialog::getOpenFileName(this,"open file");
    if(!Conehead_Zombie_path.isEmpty())
    {
        present_ui->zombies_path[1]=Conehead_Zombie_path;
        ui->Conehead_Zombie->setStyleSheet("empty");
        QIcon icon;
        icon.addFile(Conehead_Zombie_path);
        ui->Conehead_Zombie->setIconSize(QSize(100,100));
        ui->Conehead_Zombie->setIcon(icon);
    }
}


void DIY::on_Bucket_Zombie_clicked()
{
    QString Bucket_Zombie_path=QFileDialog::getOpenFileName(this,"open file");
    if(!Bucket_Zombie_path.isEmpty())
    {
        present_ui->zombies_path[2]=Bucket_Zombie_path;
        ui->Bucket_Zombie->setStyleSheet("empty");
        QIcon icon;
        icon.addFile(Bucket_Zombie_path);
        ui->Bucket_Zombie->setIconSize(QSize(100,100));
        ui->Bucket_Zombie->setIcon(icon);
    }
}


void DIY::on_Flag_Zombie_clicked()
{
    QString Flag_Zombie_path=QFileDialog::getOpenFileName(this,"open file");
    if(!Flag_Zombie_path.isEmpty())
    {
        present_ui->zombies_path[3]=Flag_Zombie_path;
        ui->Flag_Zombie->setStyleSheet("empty");
        QIcon icon;
        icon.addFile(Flag_Zombie_path);
        ui->Flag_Zombie->setIconSize(QSize(100,100));
        ui->Flag_Zombie->setIcon(icon);
    }
}

void DIY::on_pushButton_5_clicked()
{
    QMessageBox mes(QMessageBox::Information,"提示","保存成功");
    mes.exec();
}

void DIY::on_pushButton_6_clicked()
{
    QString original_path[4]={":/map/images/Zombie.png",":/map/images/Conehead_Zombie.png",":/map/images/Bucket_Zombie.png",":/map/images/Flag_Zombie.png"};
    for(int i=0;i<4;i++)
        present_ui->zombies_path[i]=original_path[i];
    QPushButton* button[4]={ui->Zombie,ui->Conehead_Zombie,ui->Bucket_Zombie,ui->Flag_Zombie};
    for(int i=0;i<4;i++)
    {
        button[i]->setStyleSheet("empty");
        QIcon icon;
        icon.addFile(original_path[i]);
        button[i]->setIconSize(QSize(100,100));
        button[i]->setIcon(icon);
    }
}



