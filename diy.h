#ifndef DIY_H
#define DIY_H

#include <QWidget>
#include <plants_zombies.h>
#include <QPaintEvent>
namespace Ui {
class DIY;
}

class DIY : public QWidget
{
    Q_OBJECT

public:
    explicit DIY(QWidget *parent = nullptr);
    ~DIY();
    Plants_Zombies *present_ui;
    void paintEvent(QPaintEvent*event);

private slots:
    void on_Zombie_clicked();

    void on_Conehead_Zombie_clicked();

    void on_Bucket_Zombie_clicked();

    void on_Flag_Zombie_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::DIY *ui;
};

#endif // DIY_H
