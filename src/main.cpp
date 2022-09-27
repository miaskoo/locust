#include "constructorWindow.h"
#include "factoryScene.h"

int main(int argc, char **argv) {
    auto construct = constructorWindow::getInstance();
    construct->initWindow(argc, argv);
    construct->initTextures({"greenChip.png", "pinkChip.png", "redChip.png", "yellowChip.png", "whitePixel.png", "negativeChip.png", "blueChip.png"});
    construct->setGameScene(factoryScene::createGameScene());
    construct->createInfoNode();
    construct->initGlutFunc();
    construct->startUpdateThread();
    construct->startMainLoop();
    std::atexit([](){
        constructorWindow::cleanup();
    });
    return 0;
}
