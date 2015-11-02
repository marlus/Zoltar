#include "mainmenustate.h"

MainMenuState::MainMenuState(QMainWindow *mainWindow, QWidget *parent)
    : QWidget(parent),
      pMainWindow(mainWindow)
{

}

MainMenuState::~MainMenuState()
{
    delete(pNewGame);
    delete(pQuitGame);
}

void MainMenuState::Draw()
{
    // Instantiate buttons
    pNewGame = new QPushButton(tr("&New Game"));
    pQuitGame = new QPushButton(tr("&Quit"));
    pLblZoltar = new QLabel();

    // Set the alignment to center
    pLblZoltar->setAlignment(Qt::AlignCenter);

    // Add the events
    connect(pNewGame, SIGNAL (released()), pMainWindow, SLOT (NewGame()));
    connect(pQuitGame, SIGNAL (released()), pMainWindow, SLOT (Quit()));

    // Load the png texture
    QPixmap zoltarTexture (":/textures/Zoltar.png");
    pLblZoltar->setPixmap(zoltarTexture);

    // Draw
    QFormLayout *mainLayout = new QFormLayout;

    mainLayout->addRow("", pLblZoltar);
    mainLayout->addRow("", pNewGame);
    mainLayout->addRow("", pQuitGame);

    setLayout(mainLayout);
}
