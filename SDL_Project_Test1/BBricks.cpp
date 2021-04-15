#include "BBricks.h"

BBrickType* BBricks::getSoftYellowBrick(int element)
{
    return BrickSoftYellow + element;
}

BBrickType* BBricks::getMediumBlueBrick(int element)
{
    return BrickMediumBlue + element;
}

BBrickType* BBricks::getHardRedBrick(int element)
{
    return BrickHardRed + element;
}

void BBricks::setYellowBrick()
{
    
    for (int i = 0, j = getBricksWidthStart(); i < Level_1.getColumnCount(); i++, j += getBrickWidth()+Level_1.getRowSpacing())
    {
        //set brick ID
        BrickSoftYellow[i].setBrickID('S');
        //set bricks texture
        BrickSoftYellow[i].setBrickTexturePath("SDL_Image_Imports/Yellow_Brick.png");
        //set brick Hit Points
        BrickSoftYellow[i].setHitPoints(1);

        //assign X and Y boarders of each bricks
        //will be used later for ball/bricks collision detection
        for (int x = j, p = 0; x <= j + getBrickWidth(); x+= getBrickWidth(), p++)
        {
            BrickSoftYellow[i].setBrickBoarderOn_X_Element(p, x);
        }
        for (int y = BrickSoftYellow_Y_Start, p = 0; y <= BrickSoftYellow_Y_Start + getBrickHeight(); y+=getBrickHeight(), p++)
        {
            BrickSoftYellow[i].setBrickBoarderOn_Y_Element(p, y);
        }

        BrickSoftYellow[i].loadYellowBrickMedia(BrickSoftYellow[i].getBrickTexturePath());
    }
}

void BBricks::setBlueBrick()
{

    for (int i = 0, j = getBricksWidthStart(); i < Level_1.getColumnCount(); i++, j += getBrickWidth() + Level_1.getRowSpacing())
    {
        //set brick ID
        BrickMediumBlue[i].setBrickID('M');
        //set bricks texture
        BrickMediumBlue[i].setBrickTexturePath("SDL_Image_Imports/Blue_Brick.png");
        //set brick Hit Points
        BrickMediumBlue[i].setHitPoints(2);

        //assign X and Y boarders of each bricks
        //will be used later for ball/bricks collision detection
        for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
        {
            BrickMediumBlue[i].setBrickBoarderOn_X_Element(p, x);
        }
        for (int y = BrickMediumBlue_Y_Start, p = 0; y <= BrickMediumBlue_Y_Start + getBrickHeight(); y += getBrickHeight(), p++)
        {
            BrickMediumBlue[i].setBrickBoarderOn_Y_Element(p, y);
        }

        BrickMediumBlue[i].loadBlueBrickMedia(BrickMediumBlue[i].getBrickTexturePath());
    }
}

void BBricks::setRedBrick()
{

    for (int i = 0, j = getBricksWidthStart(); i < Level_1.getColumnCount(); i++, j += getBrickWidth() + Level_1.getRowSpacing())
    {
        //set brick ID
        BrickHardRed[i].setBrickID('H');
        //set bricks texture
        BrickHardRed[i].setBrickTexturePath("SDL_Image_Imports/Red_Brick.png");
        //set brick Hit Points
        BrickHardRed[i].setHitPoints(3);

        //assign X and Y boarders of each bricks
        //will be used later for ball/bricks collision detection
        for (int x = j, p = 0; x <= j + getBrickWidth(); x += getBrickWidth(), p++)
        {
            BrickHardRed[i].setBrickBoarderOn_X_Element(p, x);
        }
        for (int y = BrickHardRed_Y_Start, p = 0; y <= BrickHardRed_Y_Start + getBrickHeight(); y += getBrickHeight(), p++)
        {
            BrickHardRed[i].setBrickBoarderOn_Y_Element(p, y);
        }

        BrickHardRed[i].loadRedBrickMedia(BrickHardRed[i].getBrickTexturePath());
    }
}

BLevel BBricks::getLevel()
{
    return Level_1;
}
