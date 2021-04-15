//#include "Graphics.h"


LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(const char* path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError();
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(baseRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            std::cout << "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError();
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(baseRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}



LMouseMotion::LMouseMotion()
{
    mPosition.x = 370;
    mPosition.y = 570;
}

void LMouseMotion::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void LMouseMotion::handleEvent(SDL_Event* e)
{
    if (e->type = SDL_MOUSEMOTION)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in area of game
        bool inside = true;
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            if (x < mPosition.x)
            {
                mPosition.x = mPosition.x - 10;
                if (mPosition.x == 90)
                    mPosition.x = mPosition.x + 10;
                inside = false;
            }
            else if (x > mPosition.x + BOARD_WIDTH)
            {
                mPosition.x = mPosition.x + 10;
                if (mPosition.x == 610)
                    mPosition.x = mPosition.x - 10;
                inside = false;
            }
            else if (y < mPosition.y)
            {
                inside = false;
            }
            else if (y > mPosition.y + BOARD_HEIGHT)
            {
                inside = false;
            }
        default:
            break;
        }
    }
}

void LMouseMotion::render()
{
    player_Board.render(mPosition.x, mPosition.y);
}

void game()
{
    //Start up SDL and create window
    if (!initWindow())
    {
        std::cout << "Failed to initialize!\n";
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            std::cout << "Failed to load media!\n";
        }
        else
        {
            //Main loop flag
            bool quit = false;
            //Event handler
            SDL_Event e;

            //While application is running
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e))
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    //Handle button events
                    gButtons.handleEvent(&e);
                }

                //Clear screen
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(baseRenderer);

                //Render background texture to screen
                baseBackgroundTexture.render(0, 0);

                //Render blue bricks to the screen
                blueBrickTexture.render(105, 150);

                //Render red bricks to the screen
                redBrickTexture.render(105, 175);

                //Render yellow bricks to the screen
                yellowBrickTexture.render(105, 200);

                //Render buttons
                gButtons.render();

                //Update screen
                SDL_RenderPresent(baseRenderer);

            }
        }
    }
    //Free resources and close SDL
    closeWindow();
}

bool initWindow()
{
    //Initialization flag - check if function ends successfully
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        success = false;
    }
    else
    {
        //Create window
        baseWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (baseWindow == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
            success = false;
        }
        else
        {
            //Create renderer for window
            baseRenderer = SDL_CreateRenderer(baseWindow, -1, SDL_RENDERER_ACCELERATED);
            if (baseRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color (2D)
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load Foo' texture
    if (!blueBrickTexture.loadFromFile("SDL_Image_Imports/Blue_Brick.png"))
    {
        printf("Failed to load Foo' texture image!\n");
        success = false;
    }

    //Load background texture
    if (!redBrickTexture.loadFromFile("SDL_Image_Imports/Red_Brick.png"))
    {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    //Load background texture
    if (!yellowBrickTexture.loadFromFile("SDL_Image_Imports/Yellow_Brick.png"))
    {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    //Load background texture
    if (!baseBackgroundTexture.loadFromFile("SDL_Image_Imports/Breakout_Layout.png"))
    {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    //Load sprites
    if (!player_Board.loadFromFile("SDL_Image_Imports/player_board.png"))
    {
        printf("Failed to load button sprite texture!\n");
        success = false;
    }

    return success;
}

void closeWindow()
{
    //Free loaded images
    blueBrickTexture.free();
    redBrickTexture.free();
    yellowBrickTexture.free();
    baseBackgroundTexture.free();

    //Destroy window    
    SDL_DestroyRenderer(baseRenderer);
    SDL_DestroyWindow(baseWindow);
    baseWindow = NULL;
    baseRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}