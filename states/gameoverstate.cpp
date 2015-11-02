#include "gameoverstate.h"

GameOverState::GameOverState(QMainWindow *mainWindow, QWidget *parent)
    : QWidget(parent),
      pMainWindow(mainWindow)
{

}

GameOverState::~GameOverState()
{
    delete(pBtnMainMenu);
}

void GameOverState::Draw()
{
    // Instantiate buttons
    pBtnMainMenu = new QPushButton(tr("&Back to Main Menu"));
    pLblGameOver = new QLabel();

    // Set the alignment to center
    pLblGameOver->setAlignment(Qt::AlignCenter);

    // Add the events
    connect(pBtnMainMenu, SIGNAL (released()), pMainWindow, SLOT (BackToMainMenu()));

    // Load the png texture
    QPixmap gameOverTexture (":/textures/GameOver.png");
    pLblGameOver->setPixmap(gameOverTexture);

    // Draw
    QFormLayout *mainLayout = new QFormLayout;

    mainLayout->addRow("", pLblGameOver);
    mainLayout->addRow("", pBtnMainMenu);

    setLayout(mainLayout);
}
