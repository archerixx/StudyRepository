#include "BBricks.h"

BBricks::BBricks()
{
    Level_1 = new BLevel();

    BrickSoftYellow = new BBrickType*[Level_1->getColumnCount()];
    BrickMediumBlue = new BBrickType*[Level_1->getColumnCount()];
    BrickHardRed = new BBrickType*[Level_1->getColumnCount()];
    for (int i=0;i< Level_1->getColumnCount();i++)
    { 
        BrickSoftYellow[i] = new BBrickType;
        BrickMediumBlue[i] = new BBrickType;
        BrickHardRed[i] = new BBrickType;
    }

    BrickSoftYellow_Y_FromStart = 150;
    BrickMediumBlue_Y_FromStart = 125;
    BrickHardRed_Y_FromStart = 100;
}
BBricks::~BBricks()
{
    for (int i = 0; i < Level_1->getColumnCount(); i++)
    {
        delete BrickSoftYellow[i];
        BrickSoftYellow[i] = NULL;
    }
    delete[] BrickSoftYellow;
    for (int i = 0; i < Level_1->getColumnCount(); i++)
    {
        delete BrickMediumBlue[i];
        BrickMediumBlue[i] = NULL;
    }
    delete[] BrickMediumBlue;
    for (int i = 0; i < Level_1->getColumnCount(); i++)
    {
        delete BrickHardRed[i];
        BrickHardRed[i] = NULL;
    }
    delete[] BrickHardRed;

    delete Level_1;
    Level_1 = NULL;
}

/*
    GETs
*/
BBrickType* BBricks::getSoftYellowBrick(int element)
{
    return *(BrickSoftYellow + element);
}
BBrickType* BBricks::getMediumBlueBrick(int element)
{
    return *(BrickMediumBlue + element);
}
BBrickType* BBricks::getHardRedBrick(int element)
{
    return *(BrickHardRed + element);
}
BLevel* BBricks::getLevel()
{
    return Level_1;
}

/*
    SETs
*/
void BBricks::setYellowBrick()
{
    for (int i = 0, j = getBricksWidthStart(); i < Level_1->getColumnCount(); i++, j += getBrickWidth()+Level_1->getRowSpacing())
    {
        //set bricks texture
        BrickSoftYellow[i]->setBrickTexturePath("SDL_Image_Imports/Yellow_Brick.png");
        //set brick Hit Points
        BrickSoftYellow[i]->setHitPoints(1);
        //set brick break gameScore
        BrickSoftYellow[i]->setBreakScore(10);

        //assign X and Y boarders of each bricks
        //will be used later for ball/bricks collision detection
        for (int x = j, p = 0; x <= j + getBrickWidth(); x+= getBrickWidth(), p++)
        {
            BrickSoftYellow[i]->setBrickBoarderOn_X_Element(p, x);
        }
        for (int y = getGametableHeightStart() + BrickSoftYellow_Y_FromStart, p = 0; y <= getGametableHeightStart() + BrickSoftYellow_Y_FromStart + getBrickHeight(); y+=getBrickHeight(), p++)
        {
            BrickSoftYellow[i]->setBrickBoarderOn_Y_Element(p, y);
        }

        BrickSoftYellow[i]->loadYellowBrickMedia(BrickSoftYellow[i]->getBrickTexturePath());
    }
}
void BBricks::setBlueBrick()
{

    for (int i = 0, j = getBricksWidthStart(); i < Level_1->getColumnCount(); i++, j += getBrickWidth() + Level_1->getRowSpacing())
    {
        //set bricks texture
        BrickMediumBlue[i]->setBrickTexturePath("SDL_Image_Imports/Blue_Brick.png");
        //set brick Hit Points
        BrickMediumBlue[i]->setHitPoints(2);
        //set brick break gameScore
        BrickMediumBlue[i]->setBreakScore(30);

        //assign X and Y boarders of each bricks
        //will be used later for ball/bricks collision detection
        for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
        {
            BrickMediumBlue[i]->setBrickBoarderOn_X_Element(p, x);
        }
        for (int y = getGametableHeightStart() + BrickMediumBlue_Y_FromStart, p = 0; y <= getGametableHeightStart() + BrickMediumBlue_Y_FromStart + getBrickHeight(); y += getBrickHeight(), p++)
        {
            BrickMediumBlue[i]->setBrickBoarderOn_Y_Element(p, y);
        }

        BrickMediumBlue[i]->loadBlueBrickMedia(BrickMediumBlue[i]->getBrickTexturePath());
    }
}
void BBricks::setRedBrick()
{

    for (int i = 0, j = getBricksWidthStart(); i < Level_1->getColumnCount(); i++, j += getBrickWidth() + Level_1->getRowSpacing())
    {
        //set bricks texture
        BrickHardRed[i]->setBrickTexturePath("SDL_Image_Imports/Red_Brick.png");
        //set brick Hit Points
        BrickHardRed[i]->setHitPoints(3);
        //set brick break gameScore
        BrickHardRed[i]->setBreakScore(50);

        //assign X and Y boarders of each bricks
        //will be used later for ball/bricks collision detection
        for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
        {
            BrickHardRed[i]->setBrickBoarderOn_X_Element(p, x);
        }
        for (int y = getGametableHeightStart() + BrickHardRed_Y_FromStart, p = 0; y <= getGametableHeightStart() + BrickHardRed_Y_FromStart + getBrickHeight(); y += getBrickHeight(), p++)
        {
            BrickHardRed[i]->setBrickBoarderOn_Y_Element(p, y);
        }

        BrickHardRed[i]->loadRedBrickMedia(BrickHardRed[i]->getBrickTexturePath());
    }
}
void BBricks::setBrickSoftYellow_Y_Start(int position_y)
{
    this->BrickSoftYellow_Y_FromStart = position_y;
}
void BBricks::setBrickMediumBlue_Y_Start(int position_y)
{
    this->BrickMediumBlue_Y_FromStart = position_y;
}
void BBricks::setBrickHardRed_Y_Start(int position_y)
{
    this->BrickHardRed_Y_FromStart = position_y;
}

