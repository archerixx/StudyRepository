 else
    {
    BGame gBall;
    BPlayerControl gPlayer;

    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;

    //Start game flag
    bool start = false;
    //Gameover flag
    bool gameOver = false;

    //temp values for score and lives
    int tempScore = 0;
    int tempLives = 0;

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
                break;
            }

            //Handle mouse motion events
            gPlayer.handleEvent(&e);

            //Enable music with key 9 (to play/pause) and 0 (to stop)
            gBall.getSound()->handleMusicEvent(&e);

            //start game with mouse click
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                start = true;
            }
        }
        //if mouse button is clicked, start game
        if (start)
        {
            //Clear screen
            SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
            SDL_RenderClear(baseRenderer);

            //Render background texture to screen
            gBall.renderBackground();

            //render bricks from level
            for (int i = 0; i < gBall.getBrickLevel_1()->getLevel_1()->getColumnCount(); i++)
            {
                gBall.getBrickLevel_1()->getSoftYellowBrick(i)->renderYellowBrick(gBall.getBrickLevel_1()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrickLevel_1()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
                gBall.getBrickLevel_1()->getMediumBlueBrick(i)->renderBlueBrick(gBall.getBrickLevel_1()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrickLevel_1()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
                gBall.getBrickLevel_1()->getHardRedBrick(i)->renderRedBrick(gBall.getBrickLevel_1()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrickLevel_1()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
            }

            //keep previous score
            tempScore = gBall.getScore();
            tempLives = gBall.getBrickLevel_1()->getLevel_1()->getBallLives();

            //ball movement/collision
            gBall.ballMovementAndCollision(gPlayer.getBoardPosition().x, gPlayer.getBoardPosition().y);

            //checks if it is game over
            if (gBall.getBrickLevel_1()->getLevel_1()->getBallLives() == 0)
            {
                gameOver = true;
                break;
            }
            //if game is not lost, reset ball on board and wait for mouse click
            else if (gBall.getLifeLostState() == true)
            {
                start = false;
            }

            //if score is changed, load and render it on screen
            if (gBall.getScore() > tempScore || gBall.getBrickLevel_1()->getLevel_1()->getBallLives() < tempLives)
            {
                gBall.loadScoreAndLivesMedia(gBall.getScore(), gBall.getBrickLevel_1()->getLevel_1()->getBallLives());
            }
            gBall.getScoreTexture()->renderTexture(730, 530);
            gBall.getLivesTexture()->renderTexture(50, 530);


            //game delay, speed
            SDL_Delay(2);

            //Render player board
            gPlayer.renderPlayerBoard();

            //Update screen
            SDL_RenderPresent(baseRenderer);
        }
        //show starting textures, wait for mouse click
        else
        {
            //Clear screen
            SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
            SDL_RenderClear(baseRenderer);

            //Render background texture to screen
            gBall.renderBackground();
            gBall.renderMenu();

            //render bricks from level
            for (int i = 0; i < gBall.getBrickLevel_1()->getLevel_1()->getColumnCount(); i++)
            {
                gBall.getBrickLevel_1()->getSoftYellowBrick(i)->renderYellowBrick(gBall.getBrickLevel_1()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrickLevel_1()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
                gBall.getBrickLevel_1()->getMediumBlueBrick(i)->renderBlueBrick(gBall.getBrickLevel_1()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrickLevel_1()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
                gBall.getBrickLevel_1()->getHardRedBrick(i)->renderRedBrick(gBall.getBrickLevel_1()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrickLevel_1()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
            }

            //render ball on board
            gBall.setBallPoint(gPlayer.getBoardPosition().x + gBall.getBoardWidth() / 2, gPlayer.getBoardPosition().y - gBall.getBallSize());
            gBall.renderBall(gPlayer.getBoardPosition().x + gBall.getBoardWidth() / 2, gPlayer.getBoardPosition().y - gBall.getBallSize());

            //Render player board
            gPlayer.renderPlayerBoard();

            //Render current frame
            gBall.getScoreTexture()->renderTexture(730, 530);
            gBall.getLivesTexture()->renderTexture(50, 530);

            //Update screen
            SDL_RenderPresent(baseRenderer);
        }
    }

    if (gameOver == true)
    {
        if (gBall.getScore() > tempScore || gBall.getBrickLevel_1()->getLevel_1()->getBallLives() < tempLives)
        {
            gBall.loadScoreAndLivesMedia(gBall.getScore(), gBall.getBrickLevel_1()->getLevel_1()->getBallLives());
        }
        while (!quit)
        {
            //Handle events on queue
            while (SDL_PollEvent(&e))
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                    break;
                }
            }
            //Clear screen
            SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
            SDL_RenderClear(baseRenderer);

            //Render background texture to screen
            gBall.renderGameOverBackground();
            gBall.getScoreTexture()->renderTexture(730, 530);
            gBall.getLivesTexture()->renderTexture(50, 530);

            //Update screen
            SDL_RenderPresent(baseRenderer);
        }
    }
    }