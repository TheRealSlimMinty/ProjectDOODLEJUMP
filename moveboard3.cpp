#include<iostream>
#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include<SDL/SDL_gfxPrimitives.h>
#include"SDL/SDL_ttf.h"
#include<cstdlib>
#include<ctime>
#include<math.h>
#include<sstream>
#include <string>
using namespace std;

struct boards
{
    float x;
    float y;
    int type;
    int len;
    float vy;
    float vx;
};

const int board_n = 15;
boards board[board_n];

//boards type
const int broken = 1;
const int stable = 2;
const int movable = 3;
const int spring = 4;
const int jet = 5;
const int monster1 = 6;
const int monster2 = 7;
const int monster3 = 8;
const int empty = 9;
const int mirror = 10;

void init_board()
{
    for( int i=0 ; i<board_n ; i++)
    {
        board[i].x = rand()%600;
        board[i].y = (700/board_n)*i;
        board[i].len = 700/board_n;
        board[i].vy = 0.5;
        board[i].vx = 0;


        int x=rand()%100;
        if( x<20 )
        {
            if( board[i-1].type!= broken || board[i-2].type!= broken )
            {
                board[i].type = broken;
            }
            else
            {
                board[i].type = stable;
            }
        }
        else
        {
                if (x<40)
                {
                    board[i].type = spring;
                   
                }
                 else
                    {
                        board[i].type = stable;
                    }

        }
    }
}

void move_board ()
{
    for( int i=board_n ; i>=0 ; i-- )
    {
        board[i].y+=board[i].vy;
        board[i].x+=board[i].vx;

        if ( board[i].x<20 || board[i].x>580 )
        {
             board[i].vx*=-1;
          
        }
        int h = 0;
        for( int j=0 ; j<=i ; j++)
        {
            h+=board[j].len;
        }
        if( board[i].y>=h )
        {
            board[i+1].x = board[i].x;
            board[i+1].y = board[i].y;
            board[i+1].type = board[i].type;
            board[i+1].len = board[i].len;
            board[i+1].vy = board[i].vy;
            board[i+1].vx = board[i].vx;

            board[i].type = empty;

            if ( i==0 )
            {
                board[i].x = rand()%600;
                board[i].y = 0;
                board[i].len +=2;
                board[i].vy = 0.5;
                int x=rand()%100;
                

                if( x<20 )
                {
                    if( board[i+1].type!= broken || board[i+2].type!= broken )
                    {
                        board[i].type = broken;
                        board[i].vx = 0;
                    }
                    else
                    {
                        board[i].type = stable;
                        board[i].vx = 0;
                    }
                }
                else
                {
                    if( x<40 )
                    {
                        board[i].type = movable;
                        board[i].vx = rand()%5+1;
                    }
                    else
                    {
                        if ( x<60 )
                        {
                            board[i].type = spring;
                            board[i].vx = 0;
                        }
                        else 
                        {
                            if( x<65 )
                            {
                                int a = rand()%3;
                                switch (a)
                                {
                                case 0 :
                                    board[i].type = monster1;
                                    board[i].vx = 0;
                                    break;
                                case 1 :
                                    board[i].type = monster2;
                                    board[i].vx = 0;
                                    break;
                                case 2 :
                                    board[i].type = monster3;
                                    board[i].vx = 0;
                                    break;
                                }
                            }
                            else
                            {
                                board[i].type = stable;
                                board[i].vx = 0;
                            }
                        }
                    }
                }

           }//check kon badish monster nabashe age bood khali kone
            
        }
    }

}


int loadIMG( SDL_Surface *screen , string filename , int image_x , int image_y ){

	bool flag = true;
	
	
	SDL_Surface *image;	
	SDL_Surface *temp;	//This pointer will temporarily reference our bitmap sprite
	SDL_Rect src, dest;	//These rectangles will describe the source and destination regions of our blit
	
	
	//When this program exits, SDL_Quit must be called
	atexit(SDL_Quit);
	
	if (screen == NULL) {

		flag=false;
		return 1;
	}
	
	
	temp = SDL_LoadBMP(filename.c_str());

	if (temp == NULL) 
	{
		flag=false;
		return 1;
	}
 
 image = SDL_DisplayFormat(temp);

 Uint32 colorkey = SDL_MapRGB( image->format, 0xFF, 0xFF, 0xFF );
 SDL_SetColorKey( image , SDL_SRCCOLORKEY, colorkey );
	
 SDL_FreeSurface(temp);

  

// while(flag==true){
 
	//Construct the source rectangle for our blit
	src.x = 0;
	src.y = 0;
	src.w = image->w;	//Use imagew to display the entire width of the image
	src.h = image->h;	//Use imageh to display the entire height of the image
	
	//Construct the destination rectangle for our blit
	dest.x = image_x;		//Display the image at the (X,Y) coordinates (100,100)
	dest.y = image_y;
	dest.w = image->w;	//Ensure the destination is large enough for the image's entire width/height
	dest.h = image->h;
	
	
	SDL_BlitSurface(image, &src, screen, &dest);
	
	
	
//	}
  return 0;
}
//doodle_move_function

void print_board(SDL_Surface *screen)
{
    for ( int i=0 ; i<board_n ; i++)
    {
        
//		SDL_Surface* boards;
        switch ( board[i].type )
        {
            case stable :
                loadIMG(screen, "stable.bmp", board[i].x, board[i].y);
                break;
            case broken :
                loadIMG(screen, "broken.bmp", board[i].x, board[i].y);
                break;
            case movable :
                loadIMG(screen, "movable.bmp", board[i].x, board[i].y);
                break;
            case spring :
                loadIMG(screen, "spring.bmp",board[i].x, board[i].y-17);
                break;
            case jet:
                loadIMG(screen, "jet.bmp",board[i].x, board[i].y-100);
                loadIMG(screen, "stable.bmp", board[i].x, board[i].y);
                break;
            case monster1:
                loadIMG(screen, "monster1.bmp",board[i].x, board[i].y-100);
                loadIMG(screen, "stable.bmp", board[i].x, board[i].y);
                break;
            case monster2:
                loadIMG(screen, "monster2.bmp",board[i].x, board[i].y-100);
                loadIMG(screen, "stable.bmp", board[i].x, board[i].y);
                break;
            case monster3:
                 loadIMG(screen, "monster3.bmp",board[i].x, board[i].y-100);
                 loadIMG(screen, "stable.bmp", board[i].x, board[i].y);
                break;
            case mirror:
                if(board[i].x>300)
                {
                    loadIMG(screen, "mirror.bmp",450, board[i].y-50);
                    loadIMG(screen, "stable.bmp",100, board[i].y);
                }
                else
                {
                    loadIMG(screen, "mirror.bmp",50, board[i].y-50);
                    loadIMG(screen, "stable.bmp",500, board[i].y);
                }
                break;
        }
    }
}
 
int main(int argc, char *argv[])
{     
    srand(time(0));
	SDL_Event occur;
	bool mahnaz = true;
	SDL_Init(SDL_INIT_EVERYTHING);

	if (SDL_Init(SDL_INIT_EVERYTHING)!= 0) 
	 {
	 	 mahnaz = false;
          return 1;

	  } 

       SDL_Surface *screen;
	  screen = SDL_SetVideoMode(700 , 700 , 32 , SDL_DOUBLEBUF);
	 if (screen == NULL) {

		mahnaz=false;
		return 1;
	  }

      init_board();

	 
	while(mahnaz==true)
	{
        loadIMG( screen , "background.bmp" , 0 , 0 );
        print_board(screen);

        SDL_Flip(screen);

        move_board();
	    
      SDL_PollEvent(&occur);
  
 	if(occur.type==SDL_QUIT)
	{

 	mahnaz=false;
	 SDL_FreeSurface(screen);
 	return 1;

	}

	}
   

    SDL_QUIT;
	return 0;
 }
