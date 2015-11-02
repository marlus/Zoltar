#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QCoreApplication>
#include <QMainWindow>
#include <QLabel>

static const QSize resultSize(200, 200);

class MainMenuState : public QWidget
{
Q_OBJECT

public:
    MainMenuState(QMainWindow *mainWindow, QWidget *parent = 0);
    ~MainMenuState();
    void Draw();


private:

    QPushButton *pNewGame;
    QPushButton *pQuitGame;
    QMainWindow *pMainWindow;
    QLabel *pLblZoltar;
};

#endif // MAINMENUSTATE_H
