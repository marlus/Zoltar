#include "gamemanager.h"

GameManager::GameManager()
{
    // Define the screen size
    int nWidth = 800;
    int nHeight = 600;

    // Define the position of the screen with the size.
    setGeometry(100, 100, nWidth, nHeight);

    // Define the initial state of the game
    this->currentState = GameManager::MAIN_MENU_STATE;

    // Update the game
    this->Update();
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
    if (this->currentState == GameManager::MAIN_MENU_STATE)
    {
        // Draw the main menu state
        pMainMenuState = new MainMenuState(this, 0);
        setCentralWidget(pMainMenuState);
        pMainMenuState->Draw();
    }
    else if (this->currentState == GameManager::GAME_STATE)
    {
        // Draw the game state
        pGameState = new GameState(this, 0);
        setCentralWidget(pGameState);
        pGameState->Draw();
    }

    else if (this->currentState == GameManager::GAME_OVER_STATE)
    {
        // Draw the game over state
        pGameOverState = new GameOverState(this, 0);
        setCentralWidget(pGameOverState);
        pGameOverState->Draw();
    }

    else if (this->currentState == GameManager::QUIT_STATE)
    {
        // Quit the game
        QCoreApplication::quit();
    }
}


void GameManager::GameOver()
{
    // Change the state to Game Over State
    this->currentState = GameManager::GAME_OVER_STATE;

    // Update the Game
    this->Update();
}

void GameManager::BackToMainMenu()
{
    // Change the state to Game State
    this->currentState = GameManager::MAIN_MENU_STATE;

    // Update the Game
    this->Update();
}

void GameManager::NewGame()
{
    // Change the state to Game State
    this->currentState = GameManager::GAME_STATE;

    // Update the Game
    this->Update();
}

void GameManager::Quit()
{
    // Change the state to Game State
    this->currentState = GameManager::QUIT_STATE;

    // Update the Game
    this->Update();
}
