#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <QWidget>
#include "plants_zombies.h"

namespace Ui {
class Game_Over;
}

class Game_Over : public QWidget
{
    Q_OBJECT

public:
    explicit Game_Over(QWidget *parent = nullptr);
    ~Game_Over();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Game_Over *ui;
};

#endif // GAME_OVER_H
