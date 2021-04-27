#include "GameBase.h"
#include "LTexture.h"
#include "barrier.h"
#include "grass.h"
#include "fly.h"
#include "checkCollision.h"
#include "Button.h"
#include <iostream>

bool init();


bool loadMedia();


void close();


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Mix_Music* gMusic = NULL;
Mix_Chunk* gJump = NULL;
Mix_Chunk* gCollision = NULL;
Mix_Chunk* gButton = NULL;
Mix_Chunk* gButtonOn = NULL;

TTF_Font* gFont = NULL;
TTF_Font* gFontGameOver = NULL;


LTexture gScoreTextTexture;
LTexture gHightScoreTextTexture;
LTexture DinosourTexture;
LTexture cactusTexture;
LTexture cactus1Texture;
LTexture plotTexture;
LTexture treeTexture;
LTexture treeNightTexture;
LTexture cloudsTexture;
LTexture cloudsNightTexture;
LTexture birdTexture;
LTexture GameOverTexture;
LTexture backGroundTexture;

const int WALKING_ANIMATION_FRAMES = 6;
SDL_Rect CharacterClips[ WALKING_ANIMATION_FRAMES ];

const int BIRD_ANIMATION_FRAMES = 9;
SDL_Rect birdClips[ BIRD_ANIMATION_FRAMES ];


//Mouse button sprites
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
LTexture gPlayButttonTexture;
LTexture gExitTexture;
LTexture gPlayAgainTexture;
//Buttons objects
LButton gPlayButton;
LButton gExitButton;
LButton gPlayAgain;


int main( int argc, char* args[] )
{
    srand(time(0));

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
            bool gameOver = false;
            bool playAgain = false;
            bool play = false;
            bool exit = false;
			//Event handler


			SDL_Color textColor = {0, 0, 0 , 255};
            SDL_Color textColor_GameOver = {255, 255, 255, 255 };


            while ( playAgain || !quit)
            {
			std::stringstream ScoreText;;
            std::stringstream HightScoreText;
            Mix_Music* Music_gameplay = gMusic;
            int frame_charactor = 0;
            int frame_bird = 0;
            int time = 0;
            double speed = 5;
            int score = 0;

            character dinosaur;
            barrier cactus[3];
            grass plot;
            grass Tree;
            grass Clouds;
            fly bird;

            SDL_Event e;
            std::ifstream file_in ("diem_so.txt");
            int max_score ;
            while (!file_in.eof() )
            {
                file_in >> max_score;
            }
            file_in.close();

            std::cout << max_score << "sai" << std::endl;
                cactus[0].PosX = 1280;
                cactus[0].PosY = 545;
                cactus[1].PosX = cactus[0].PosX + rand() % 200 + 300 ;
                cactus[1].PosY = 535;
			while( !quit )
			{
				while( SDL_PollEvent( &e ) )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if (!gameOver && play) {
                        dinosaur.handleEvent( e , gJump );
					}
					else if (!gameOver ) {
					gPlayButton.handleEvent(e, play, gButton, gButtonOn);
					gExitButton.handleEvent(e, exit, gButton, gButtonOn);
					}
					else if (gameOver) {
					gPlayAgain.handleEvent(e, playAgain, gButton, gButtonOn);
					gExitButton.handleEvent(e, exit, gButton, gButtonOn);
					}
				}

				ScoreText.str( "" );
				HightScoreText.str( "" );
				ScoreText << "YOUR SCORE : " << score/20 ;
				HightScoreText << "HIGH SCORE : " << max_score;

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
                if (!gameOver && !playAgain){
                backGroundTexture.render(0, 0, NULL, gRenderer);
				gPlayButton.render(gPlayButttonTexture, gSpriteClips, gRenderer);
				gExitButton.render(gExitTexture, gSpriteClips, gRenderer);
                }

                if (playAgain) {

                    gameOver = false;

                    //play = true;
                    playAgain = false;
                    quit = false;
                    break;
                }
                else if (exit)
                {
                    quit = true;
                    playAgain = false;

                    gameOver = true;


                }

				if (play)
                {
				if (!gameOver && play )
                {
                    if ( !gScoreTextTexture.loadFromRenderedText(ScoreText.str().c_str() , textColor, gRenderer, gFont)
                    || !gHightScoreTextTexture.loadFromRenderedText(HightScoreText.str().c_str(), textColor, gRenderer, gFont )  )
                        {
                                printf("time textture \n");
                        }
                }
                else {
                    if ( !gScoreTextTexture.loadFromRenderedText(ScoreText.str().c_str() , textColor_GameOver, gRenderer, gFontGameOver)
                    || !gHightScoreTextTexture.loadFromRenderedText(HightScoreText.str().c_str(), textColor_GameOver, gRenderer, gFontGameOver )  )
                        {
                                printf("time textture \n");
                        }
                }


                if (check_collision_character_barrier(dinosaur, cactus[0]) || check_collision_character_barrier(dinosaur, cactus[1])
                || check_collision_character_barrier(dinosaur, cactus[2] ) || check_collision_character_bird(dinosaur, bird) )
                {
                dinosaur.move();
				cactus[0].move(speed);
                cactus[1].move(speed);
                bird.move(speed + 4);
                plot.move(speed);
                Tree.move(speed - 2);
				Clouds.move(speed - 4);

                dinosaur.stop();
                cactus[0].stop(speed);
                cactus[1].stop(speed);
                plot.stop(speed);
                Tree.stop(speed - 2);
                Clouds.stop(speed - 4);
                bird.stop(speed + 4);
                frame_charactor--;
                frame_bird--;
                gameOver = true;

                }
                else
                {
                dinosaur.move();

				cactus[0].move(speed);
                if (cactus[0].X() < 0) {
                cactus[1].move(speed);
                if (cactus[1].X() < 0)
                {
                cactus[0].PosX = rand() % 300 + 1280;
                }
                }
                if (cactus[1].X() < 0) cactus[1].PosX = cactus[1].PosX + cactus[0].PosX;



                if(time > 500) bird.move(speed + 4);
                plot.move(speed);
                Tree.move(speed - 2);
				Clouds.move(speed - 4);
				int speed_up = int(score);
				if (speed_up % 300 == 0)
				std::cout << speed_up % 1000;
				speed += 0.005;
				score++;
                }

                if (!gameOver && play)
                {
               if( Mix_PlayingMusic() == 0 )
                {
                    Mix_PlayMusic( Music_gameplay, -1 );
                }
                    else if( Mix_PausedMusic() == 1 )
                    {
                        Mix_ResumeMusic();
                    }
                }
                else {
                    Mix_PauseMusic();
                    if ( score == time -1 ) Mix_PlayChannel(-1, gCollision, 0);
                }



                double Cloud_x = Clouds.X()- 1280;
                double Cloud_y = Clouds.Y() - 535;

                int night = score / 500;
                if (night % 2 == 0) {
                cloudsTexture.render(Cloud_x, Cloud_y, NULL, gRenderer);
                cloudsTexture.render(Cloud_x + 1280, Cloud_y, NULL, gRenderer);
                Tree.render( treeTexture, gRenderer);
                }
                else {
                    cloudsNightTexture.render(Cloud_x, Cloud_y, NULL, gRenderer);
                    cloudsNightTexture.render(Cloud_x + 1280, Cloud_y, NULL, gRenderer);
                    Tree.render(treeNightTexture, gRenderer);
                }



                SDL_Rect* currentClip = &CharacterClips[ frame_charactor/6 ];

                dinosaur.render(DinosourTexture, currentClip, gRenderer);

                cactus[0].render(cactusTexture, NULL, gRenderer);
                cactus[1].render(cactus1Texture, NULL, gRenderer);

                SDL_Rect* birdCurrentClip = &birdClips[frame_bird/9 ];

                bird.render(birdTexture, birdCurrentClip, gRenderer );

                double plotX = plot.X() - 1280 ;
                double plotY = plot.Y() + 62;
                plotTexture.render(plotX,plotY,NULL,gRenderer);
                plotTexture.render(plotX + 1280,plotY,NULL,gRenderer);


                if (!gameOver) {
                        gScoreTextTexture.render(700,0,NULL, gRenderer);
                gHightScoreTextTexture.render(700, 50, NULL, gRenderer);
                }
                if (gameOver) {
                //GameOverTexture.render(0, 0, NULL, gRenderer);
                gScoreTextTexture.render(SCREEN_HEIGHT / 2, 200,NULL, gRenderer);
                gHightScoreTextTexture.render(SCREEN_HEIGHT / 2 , 200 - 100, NULL, gRenderer);
                gPlayAgain.render(gPlayAgainTexture, gSpriteClips, gRenderer);
				gExitButton.render(gExitTexture, gSpriteClips, gRenderer);

                }
                if (dinosaur.Y() < 550) frame_charactor;
				else ++frame_charactor;
                ++frame_bird;
				if (frame_bird / 9 >= BIRD_ANIMATION_FRAMES ) frame_bird = 0;
				if( frame_charactor / 6 >= WALKING_ANIMATION_FRAMES )
				{
					frame_charactor = 0;
				}
                time++;
			}

			SDL_RenderPresent( gRenderer );
			}

			std::ofstream file_out ("diem_so.txt");
			if (score/20 > max_score ) {
			    max_score = score/20;
                file_out << max_score << std::endl;
			file_out.close();
			}
			else {
                    file_out << max_score;
                file_out.close();
			}
			std::cout << max_score << std::endl;
		}
		}
	}


	close();

	return 0;
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Dion in jungle ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize!", Mix_GetError() );
                    success = false;
                }

                if (TTF_Init() == -1 )
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

    DinosourTexture.loadFromFile( "img//char.png", gRenderer );
{
        int x = 0, y = 0;
        for (int i = 0; i < 6; ++i)
        {
		CharacterClips[ i ].x =   x;
		CharacterClips[ i ].y =   y;
		CharacterClips[ i ].w =  57;
		CharacterClips[ i ].h =  57;
		x+= 57;
        }
}
	birdTexture.loadFromFile("img//bird1.png", gRenderer);
    {
    int x = 0, y = 0;
    for (int i = 0; i < 9; i++)
    {
        birdClips[i].x = x;
        birdClips[i].y = y;
        birdClips[i].w = 80;
        birdClips[i].h = 80;
        x+= 80;
    }
    }
	cactusTexture.loadFromFile("img//cactus.png", gRenderer);
	cactus1Texture.loadFromFile("img//cactus1.png", gRenderer);
	plotTexture.loadFromFile("img//plot.png", gRenderer);
	treeTexture.loadFromFile("img//tree.png", gRenderer);
	treeNightTexture.loadFromFile("img//tree1.png", gRenderer);
	cloudsTexture.loadFromFile("img//bk1.png", gRenderer);
	cloudsNightTexture.loadFromFile("img//bk2.png", gRenderer);
	GameOverTexture.loadFromFile("img//gameOver.png", gRenderer);
	backGroundTexture.loadFromFile("img//background.png", gRenderer);

	gJump = Mix_LoadWAV("sound//Jump.wav");
	gCollision = Mix_LoadWAV("sound//collision.wav");
	gButton = Mix_LoadWAV("sound//mouse_click.wav");
	gButtonOn = Mix_LoadWAV("sound//button_on.wav");
	gMusic = Mix_LoadMUS("sound//beat.mp3");

	gFont = TTF_OpenFont("lazy.otf", 30 );
	gFontGameOver = TTF_OpenFont("lazy.otf", 60);
    gPlayButttonTexture.loadFromFile("img//play_button.png", gRenderer);
    gExitTexture.loadFromFile("img//exit_button.png", gRenderer);
    gPlayAgainTexture.loadFromFile("img//play_button.png", gRenderer);

        for (int i = 0; i < BUTTON_SPRITE_TOTAL; i++)
        {
            gSpriteClips[i].x = 150*i;
            gSpriteClips[i].y = 0;
            gSpriteClips[i].w = BUTTON_WIDTH;
            gSpriteClips[i].h = BUTTON_HEIGHT;
        }
        gPlayButton.setPosition(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2);
        gExitButton.setPosition(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 + 80);
        gPlayAgain.setPosition(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2);


	return success;
}

void close()
{
	//Free loaded images
	DinosourTexture.free();
    plotTexture.free();
    cloudsTexture.free();
    cloudsNightTexture.free();
    treeTexture.free();
    treeNightTexture.free();
    cactusTexture.free();
    cactus1Texture.free();
    birdTexture.free();
    GameOverTexture.free();
    backGroundTexture.free();
    gScoreTextTexture.free();
    gHightScoreTextTexture.free();
    gPlayButttonTexture.free();
    gExitTexture.free();
    gPlayAgainTexture.free();

    Mix_FreeChunk(gJump);
    Mix_FreeChunk(gCollision);
    Mix_FreeChunk(gButton);
    Mix_FreeChunk(gButtonOn);
    gJump = NULL;
    gCollision = NULL;
    gButton = NULL;
    gButtonOn = NULL;

    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    TTF_CloseFont(gFont);
    TTF_CloseFont(gFontGameOver);
    gFont = NULL;
    gFontGameOver = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}
