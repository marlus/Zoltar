#include "gamestate.h"

GameState::GameState(QMainWindow *mainWindow, QWidget *parent)
    : QWidget(parent),
      pMainWindow(mainWindow)
{
    // Creates the riddles.
    riddle riddle1      = {"Does the animal that your thought about, lives in water?", "shark"};
    riddle riddle11     = {"Does the animal that your thought about, lives in swamp?", "aligator"};
    riddle riddle111    = {"Does the animal that your thought about, is an arthropod?", "crab"};
    riddle riddle112    = {"Does the animal that your thought about, is a bird?", "carcaja"};
    riddle riddle12     = {"Does the animal that your thought about, he knows how to fly?", "seagull"};
    riddle riddle121    = {"Does the animal that your thought about, is a bug", "dragon fly"};
    riddle riddle122    = {"Does the animal that your thought about, came from fantasy?", "wyvern"};

    // Add the riddles to the container
    stRiddles.push_back(riddle1);
    stRiddles[0].stRiddles.push_back(riddle11);
    stRiddles[0].stRiddles[0].stRiddles.push_back(riddle111);
    stRiddles[0].stRiddles[0].stRiddles.push_back(riddle112);

    stRiddles[0].stRiddles.push_back(riddle12);
    stRiddles[0].stRiddles[1].stRiddles.push_back(riddle121);
    stRiddles[0].stRiddles[1].stRiddles.push_back(riddle122);

    // Initialize the index
    iCurrentRiddle  = 0;
    iLastRiddle  = 0;
    pCurrentVector  = &stRiddles;
    pLastVector     = &stRiddles;
    isToCreateChild = false;

    // Create a flag to start questions
    currentGameRiddleState = GameState::GAME_NOT_STARTED;
}

GameState::~GameState()
{

}

void GameState::Draw()
{
    // Instantiate widgets
    pLblQuestion = new QLabel(tr("  Think about an animal...  "));
    pBtnYes = new QPushButton(tr("&Yes"));
    pBtnNo = new QPushButton(tr("&No"));

    // Add the events
    connect(pBtnYes, SIGNAL (released()), this, SLOT (AnswerYes()));
    connect(pBtnNo, SIGNAL (released()), this, SLOT (AnswerNo()));

    // Draw
    QFormLayout *mainLayout = new QFormLayout;
    mainLayout->addRow("", pLblQuestion);
    mainLayout->addRow("", pBtnYes);
    mainLayout->addRow("", pBtnNo);

    setLayout(mainLayout);
}

void GameState::DrawNewRiddleAnswer()
{
    // Delete the Game Layout
    delete(pLblQuestion);
    delete(pBtnYes);
    delete(pBtnNo);
    delete layout();

    // Instantiate widgets
    pLblQuestion = new QLabel(tr("What was the animal that you tought about?"));
    pTextRiddleAnswer = new QTextEdit();
    pBtnInsertRiddle = new QPushButton(tr("&Ok"));

    // Add the events
    connect(pBtnInsertRiddle, SIGNAL (released()), this, SLOT (AddRiddleAnswer()));

    // Draw
    QFormLayout *mainLayout = new QFormLayout;
    mainLayout->addRow("", pLblQuestion);
    mainLayout->addRow("", pTextRiddleAnswer);
    mainLayout->addRow("", pBtnInsertRiddle);

    setLayout(mainLayout);
}

void GameState::AddRiddleAnswer()
{
    // Get the Answer
    riddle lastRiddle = {"", pTextRiddleAnswer->toPlainText().toLocal8Bit().constData()};

    // Create a child
    if (isToCreateChild)
    {
        // Get the reference of the sub vector with a dereference pointer.
        pLastVector = pCurrentVector;
        pCurrentVector = &((*pCurrentVector)[iCurrentRiddle].stRiddles);

        // Set the values of riddles
        iLastRiddle = iCurrentRiddle;
        iCurrentRiddle = 0;

        (*pCurrentVector).push_back(lastRiddle);
    }
    // Create a brother
    else
    {
        (*pCurrentVector).push_back(lastRiddle);
    }

    this->DrawNewRiddleQuestion();
}

void GameState::DrawNewRiddleQuestion()
{
    // Delete the Game Layout
    delete(pLblQuestion);
    delete(pTextRiddleAnswer);
    delete(pBtnInsertRiddle);
    delete layout();

    // Instantiate widgets
    std::string riddleQuestion = "A " + (*pCurrentVector)[(*pCurrentVector).size()-1].answer + " ________________ but a shark does not (Fill it with an animal trait, like 'lives on water')";
    pLblQuestion = new QLabel(QString(riddleQuestion.c_str()));
    pTextRiddleQuestion = new QTextEdit();
    pBtnInsertRiddle = new QPushButton(tr("&Ok"));

    // Add the events
    connect(pBtnInsertRiddle, SIGNAL (released()), this, SLOT (AddRiddleQuestion()));

    // Draw
    QFormLayout *mainLayout = new QFormLayout;
    mainLayout->addRow("", pLblQuestion);
    mainLayout->addRow("", pTextRiddleQuestion);
    mainLayout->addRow("", pBtnInsertRiddle);

    setLayout(mainLayout);
}

void GameState::AddRiddleQuestion()
{
    // Create a new Question
    std::string question = "Does the animal that your thought about, ";
    question.append(pTextRiddleQuestion->toPlainText().toLocal8Bit().constData());
    question.append("?");
    (*pCurrentVector)[(*pCurrentVector).size()-1].question = question.c_str();

    delete(pLblQuestion);
    delete(pTextRiddleQuestion);
    delete(pBtnInsertRiddle);
    delete layout();

    // Initialize the index
    iCurrentRiddle  = 0;
    iLastRiddle  = 0;
    pCurrentVector  = &stRiddles;
    pLastVector     = &stRiddles;
    isToCreateChild = false;

    currentGameRiddleState =  GameState::GAME_NOT_STARTED;
    this->Draw();
}

void GameState::AnswerYes()
{
    // If the game is not started we make the first question
    if (currentGameRiddleState == GameState::GAME_NOT_STARTED)
    {
        pLblQuestion->setText(QString::fromStdString((*pCurrentVector)[iCurrentRiddle].question));
        currentGameRiddleState = GameState::QUESTION_MADE;
    }
    // If a question has been made
    else if (currentGameRiddleState == GameState::QUESTION_MADE)
    {
        // Verify if it has sub riddles
        if ((*pCurrentVector)[iCurrentRiddle].stRiddles.size() > 0)
        {
            // Get the reference of the sub vector with a dereference pointer.
            pLastVector = pCurrentVector;
            pCurrentVector = &((*pCurrentVector)[iCurrentRiddle].stRiddles);

            // Set the values of riddles
            iLastRiddle = iCurrentRiddle;
            iCurrentRiddle = 0;

            // Make the question again
            pLblQuestion->setText(QString::fromStdString((*pCurrentVector)[iCurrentRiddle].question));
            currentGameRiddleState = GameState::QUESTION_MADE;
        }
        else
        {
            // Try to answer the riddle
            std::string answer = "Is the animal that you tought a " + (*pCurrentVector)[iCurrentRiddle].answer + "?";
            pLblQuestion->setText(QString::fromStdString(answer));
            currentGameRiddleState = GameState::QUESTION_ANSWERED;

            isToCreateChild = true;
        }
    }
    // If a question has been answered
    else if (currentGameRiddleState == GameState::QUESTION_ANSWERED)
    {
        // Zoltar wins!
        QMetaObject::invokeMethod(pMainWindow, "GameOver", Qt::DirectConnection);
    }
}

void GameState::AnswerNo()
{
    if (currentGameRiddleState == GameState::GAME_NOT_STARTED)
    {
        // Go to main menu
        QMetaObject::invokeMethod(pMainWindow, "BackToMainMenu", Qt::DirectConnection);
    }
    else if(currentGameRiddleState == GameState::QUESTION_MADE)
    {
        // Verify if we reach the last question
        if (iCurrentRiddle < ((*pCurrentVector).size()-1))
        {
            // Go to the next question.
            iCurrentRiddle++;
            pLblQuestion->setText(QString::fromStdString((*pCurrentVector)[iCurrentRiddle].question));
            currentGameRiddleState = GameState::QUESTION_MADE;
        }
        // Try to guess
        else
        {
            // Ok, Zoltar doesn't know, is the first of the first
            if (pLastVector == pCurrentVector)
            {
                if (iCurrentRiddle == 0)
                {
                    std::string answer = "Is the animal that you tought a monkey?";
                    pLblQuestion->setText(QString::fromStdString(answer));
                    currentGameRiddleState = GameState::QUESTION_ANSWERED;
                }
                else
                {
                    // Ok, Zoltar doesn't know, inform a new animal!
                    this->DrawNewRiddleAnswer();
                }
            }
            else
            {
                // Try to answer the riddle
                std::string answer = "Is the animal that you tought a " + (*pLastVector)[iLastRiddle].answer + "?";
                pLblQuestion->setText(QString::fromStdString(answer));
                currentGameRiddleState = GameState::QUESTION_ANSWERED;
            }
        }
    }
    else if (currentGameRiddleState == GameState::QUESTION_ANSWERED)
    {
        // Ok, Zoltar doesn't know, inform a new animal!
        this->DrawNewRiddleAnswer();
    }
}
