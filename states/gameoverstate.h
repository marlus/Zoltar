#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <QWidget>
#include <QPushButton>
#include <QCoreApplication>
#include <QMainWindow>
#include <QFormLayout>
#include <QLabel>

class GameOverState : public QWidget
{
Q_OBJECT

public:
    GameOverState(QMainWindow *mainWindow, QWidget *parent = 0);
    ~GameOverState();
    void Draw();

private:
    QPushButton *pBtnMainMenu;
    QMainWindow *pMainWindow;
    QLabel *pLblGameOver;
};

#endif // GAMEOVERSTATE_H
