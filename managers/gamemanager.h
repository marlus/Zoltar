#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QMainWindow>
#include "states/mainmenustate.h"
#include "states/gamestate.h"
#include "states/gameoverstate.h"

namespace Ui {
class GameManager;
}

class GameManager : public QMainWindow
{
    Q_OBJECT

public:
    GameManager();
    ~GameManager();

    enum State
    {
       MAIN_MENU_STATE,
       GAME_STATE,
       GAME_OVER_STATE,
       QUIT_STATE
    };

    GameManager::State currentState;

public slots:
    void NewGame();
    void BackToMainMenu();
    void GameOver();
    void Quit();

private:
    void Update();

    MainMenuState *pMainMenuState;
    GameState *pGameState;
    GameOverState *pGameOverState;
};

#endif // GAMEMANAGER_H
