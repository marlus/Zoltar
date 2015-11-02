#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QMainWindow>
#include <vector>
#include <QTextEdit>

#include "data/riddle.h"

class GameState : public QWidget
{
Q_OBJECT

public:
    GameState(QMainWindow *mainWindow, QWidget *parent = 0);
    ~GameState();
    void Draw();
    void DrawNewRiddleAnswer();
    void DrawNewRiddleQuestion();

private slots:
    void AnswerYes();
    void AnswerNo();
    void AddRiddleAnswer();
    void AddRiddleQuestion();

private:
    QLabel *pLblQuestion;
    QPushButton *pBtnYes;
    QPushButton *pBtnNo;
    QPushButton *pBtnInsertRiddle;
    QTextEdit *pTextRiddleQuestion;
    QTextEdit *pTextRiddleAnswer;

    QMainWindow *pMainWindow;
    std::vector<riddle> stRiddles;

    unsigned int iCurrentRiddle;
    unsigned int iLastRiddle;
    std::vector<riddle> *pCurrentVector;
    std::vector<riddle> *pLastVector;
    bool isToCreateChild;

    enum GameRiddleState
    {
        GAME_NOT_STARTED,
        QUESTION_MADE,
        QUESTION_ANSWERED
    };

    GameRiddleState currentGameRiddleState;
};

#endif // GAMESTATE_H
