#include "managers/gamemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameManager gameManager;

    gameManager.show();
    return app.exec();
}
