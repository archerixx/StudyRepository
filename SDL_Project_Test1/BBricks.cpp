#include "BBricks.h"

BBricks::BBricks()
{
    Level_1 = new BLevel();
    Level_2 = new BLevel(6, 11, 5, 5, "SDL_Image_Imports / retro_arcade_background.png", 3);

    BrickSoftYellow = new BBrickType*[Level_1->getColumnCount()];
    BrickMediumBlue = new BBrickType*[Level_1->getColumnCount()];
    BrickHardRed = new BBrickType*[Level_1->getColumnCount()];
    BrickImpenetrablePurple = new BBrickType * [22];
    for (int i=0;i< Level_1->getColumnCount();i++)
    { 
        BrickSoftYellow[i] = new BBrickType;
        BrickMediumBlue[i] = new BBrickType;
        BrickHardRed[i] = new BBrickType;
    }
    for (int i = 0; i < 22; i++)
    {
        BrickImpenetrablePurple[i] = new BBrickType;
    }

    BrickSoftYellow_Y_FromStart = 200;
    BrickMediumBlue_Y_FromStart = 175;
    BrickHardRed_Y_FromStart = 150;
    BrickImpenetrable_Y_FromStart = 125;
    BrickImpenetrable_Y_ToEnd = 225;
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

    //add purple

    delete Level_1;
    Level_1 = NULL;
    delete Level_2;
    Level_2 = NULL;
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
BBrickType* BBricks::getImpenetrablePurpleBrick(int element)
{
    return *(BrickImpenetrablePurple + element);;
}
BLevel* BBricks::getLevel_1()
{
    return Level_1;
}
BLevel* BBricks::getLevel_2()
{
    return Level_2;
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
    //
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
void BBricks::setPurpleBrick()
{
    for (int i = 0, j = getBricksWidthStart(); i < 22; i++, j += getBrickWidth() + Level_1->getRowSpacing())
    {
        if (i==10)
        {
            j =getBricksWidthStart();
        }

        if (i > 0 && i < 20 && i != 10)
        {
            //set bricks texture
            BrickImpenetrablePurple[i]->setBrickTexturePath("SDL_Image_Imports/Purple_Brick.png");
            //set brick Hit Points
            BrickImpenetrablePurple[i]->setHitPoints(0);
            //set brick break gameScore
            BrickImpenetrablePurple[i]->setBreakScore(0);

            //assign X and Y boarders of each bricks
            //will be used later for ball/bricks collision detection
            for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
            {
                BrickImpenetrablePurple[i]->setBrickBoarderOn_X_Element(p, x);
            }
            if (i<10)
                for (int y = getGametableHeightStart() + BrickImpenetrable_Y_FromStart, p = 0; p < 2 ; y += getBrickHeight(), p++)
                {
                   if (i<5 && y == getGametableHeightStart() + BrickImpenetrable_Y_FromStart)
                        BrickImpenetrable_Y_FromStart = BrickImpenetrable_Y_FromStart - 25;
                   else if (i>=5 && y == getGametableHeightStart() + BrickImpenetrable_Y_FromStart)
                   {
                       BrickImpenetrable_Y_FromStart = BrickImpenetrable_Y_FromStart + 25;
                   }
                    BrickImpenetrablePurple[i]->setBrickBoarderOn_Y_Element(p, y);
                }
            else
            {
                for (int y = getGametableHeightStart() + BrickImpenetrable_Y_ToEnd, p = 0; p < 2; y += getBrickHeight(), p++)
                {
                    if (i < 15 && y == getGametableHeightStart() + BrickImpenetrable_Y_ToEnd)
                        BrickImpenetrable_Y_ToEnd = BrickImpenetrable_Y_ToEnd + 25;
                    else if (i >= 15 && y == getGametableHeightStart() + BrickImpenetrable_Y_ToEnd)
                    {
                        BrickImpenetrable_Y_ToEnd = BrickImpenetrable_Y_ToEnd - 25;
                    }
                    BrickImpenetrablePurple[i]->setBrickBoarderOn_Y_Element(p, y);
                }
            }
            
            BrickImpenetrablePurple[i]->loadPurpleBrickMedia(BrickImpenetrablePurple[i]->getBrickTexturePath());
        }

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