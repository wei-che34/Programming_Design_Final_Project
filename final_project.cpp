#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

//global variable: score
int score = 0;
Font font;
sf::Text score_text;
void game();
void dead();

//two games will use point.
struct point
{
    int x, y;
};

//defination of Minesweeper
class Minesweeper{
public:
    point loc[100];
    void run();
    void processInput();
    void check_blank(int, int, int, int);
    int grid[12][12];
    int sgrid[12][12]; // for showing
    int grid_hard[20][20];
    int sgrid_hard[20][20];
private:
    RenderWindow app;
    int w=32;
    int left=0;
    int score=0;
    Font font;
    sf::Text score_text;
    sf::Font font2;
    sf::Text left_text;
    Texture t;
    int select();
};
//end of Minesweeper
//definaion of Doodle run
class Doodle
{
public:
    void run();

    class DoodleForOne
    {
    public:
        void processInputOne();

    private:
        RenderWindow app;
        Texture t1, t2, t3;
        int x = 100, y = 100, h = 200;
        float dx = 0, dy = 0;
        string character;
        void selectForOne();
        sf::SoundBuffer buffer;
        sf::Sound sound;
    };
    // nested class for two modes
    class DoodleForTwo
    {
    public:
        void processInputTwo();

    private:
        RenderWindow app;
        // variables needed inside program
        Texture t1, t2, t3, t4;
        int x = 100, y = 100, h = 200;
        int x2 = 500, y2 = 100;
        float dx = 0, dy = 0;
        float dx2 = 0, dy2 = 0;
        string character1, character2; // strings to record character's position
        void selectForTwo1(); // first player select character
        void selectForTwo2(); // second player select character
        sf::SoundBuffer buffer;
        sf::Sound sound;
    };

private:
    int mode = 0;
    void selectMode(); // record the mode selected
};
//end of Doodle run
//defination of Arkanoid
class Arkanoid
{
public:
    void run();
    void processInput();

private:
    RenderWindow app;
    Texture t1, t2, t3, t4;
};
//end of Arkanoid

int main()
{
    game(); //start the game!
    return 0;
}

void game()
{
    //main interface
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Final_Project");
    sf::Texture texture;
    texture.loadFromFile("images/start game.png");
    sf::Sprite sprite(texture);
    sf::Music startbgm;
    startbgm.openFromFile("bgm/start.ogg");
    startbgm.play();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                //X: Doodle run
                if (event.key.code == sf::Keyboard::X)
                {
                    startbgm.stop();
                    window.close();
                    Doodle doodle;
                    doodle.run();
                }
                //Y: Minesweeper
                else if (event.key.code == sf::Keyboard::Y)
                {
                    startbgm.stop();
                    window.close();
                    Minesweeper minesweeper;
                    minesweeper.run();
                }
                //Z: Arkanoid
                else if (event.key.code == sf::Keyboard::Z)
                {
                    startbgm.stop();
                    window.close();
                    Arkanoid arkanoid;
                    arkanoid.run();
                }
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}

void dead()
{
    //dead interface
    RenderWindow dead_window(sf::VideoMode(1024, 768), "Dead!");
    sf::Texture dead_pic;
    dead_pic.loadFromFile("images/6.png");
    sf::Sprite dead(dead_pic);
    //showing score
    font.loadFromFile("ARIALN.TTF");
    Text your_score;
    your_score.setFont(font);
    your_score.setFillColor(sf::Color::White);
    your_score.setCharacterSize(60);
    your_score.setString("Your Score is " + std::to_string(score));
    while (dead_window.isOpen())
    {
        sf::Event dead_event;
        while (dead_window.pollEvent(dead_event))
        {
            if (dead_event.type == sf::Event::Closed)
                dead_window.close();
            else if (dead_event.type == sf::Event::KeyPressed)
            {
            	//X: end
                if (dead_event.key.code == sf::Keyboard::X)
                    dead_window.close();
                //Y: restart
                else if (dead_event.key.code == sf::Keyboard::Y)
                {
                    dead_window.close();
                    game();
                }
            }
        }
        dead_window.draw(dead);
        dead_window.draw(your_score);
        dead_window.display();
    }
}

//select easier or harder
int Minesweeper::select(){
	RenderWindow select(VideoMode(1024,768), "Select!");
	Texture texture;
	texture.loadFromFile("Minesweeper_images/Mode.png");
	Sprite sprite(texture);
	while (select.isOpen())
    {	
        sf::Event event;
        while (select.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                select.close();
            else if(event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Y){
					select.close();
                	return 2;
				}
				else if (event.key.code == sf::Keyboard::X){
					select.close();
					return 1;
				}
			}	 	
        }
        select.draw(sprite);
        select.display();		
    }
}
//return 1 or 2 for different modes
//checking blank or not
void Minesweeper::check_blank(int x, int y, int count, int size){
    if (size == 10) {
        if (1 <= x and x <= size and 1 <= y and y <= size) {
            for (int i = 0; i < count; i++) {
                if (loc[i].x == x and loc[i].y == y)
                    return;
            }
            loc[count].x = x, loc[count].y = y;
            count++;
            sgrid[x][y] = grid[x][y];
            if (grid[x][y] == 0) {
                check_blank(x, y + 1, count, 10);
                check_blank(x + 1, y, count, 10);
                check_blank(x - 1, y, count, 10);
                check_blank(x, y - 1, count, 10);
            } else {
                return;
            }
        }
    } else if (size == 18) {
        if (1 <= x and x <= size and 1 <= y and y <= size) {
            for (int i = 0; i < count; i++) {
                if (loc[i].x == x and loc[i].y == y)
                    return;
            }
            loc[count].x = x, loc[count].y = y;
            count++;
            sgrid_hard[x][y] = grid_hard[x][y];
            if (grid_hard[x][y] == 0) {
                check_blank(x, y + 1, count, 18);
                check_blank(x + 1, y, count, 18);
                check_blank(x - 1, y, count, 18);
                check_blank(x, y - 1, count, 18);
            } else {
                return;
            }
        }
    }
}

void Minesweeper::processInput() {
   int mode = select();
   srand(time(0));

   RenderWindow app(VideoMode(1024, 768), "Minesweeper!");
   t.loadFromFile("Minesweeper_images/tiles.jpg");
   Sprite s(t);

   if (mode==1) {
   	//mode1-easier
     for (int i = 1; i <= 10; i++)
       for (int j = 1; j <= 10; j++) {
         sgrid[i][j] = 10;
         if (rand() % 5 == 0)
           grid[i][j] = 9;
         else
           grid[i][j] = 0;
       }

     for (int i = 1; i <= 10; i++)
       for (int j = 1; j <= 10; j++) {
         int n = 0;
         if (grid[i][j] == 9)
           continue;
         if (grid[i + 1][j] == 9)
           n++;
         if (grid[i][j + 1] == 9)
           n++;
         if (grid[i - 1][j] == 9)
           n++;
         if (grid[i][j - 1] == 9)
           n++;
         if (grid[i + 1][j + 1] == 9)
           n++;
         if (grid[i - 1][j - 1] == 9)
           n++;
         if (grid[i - 1][j + 1] == 9)
           n++;
         if (grid[i + 1][j - 1] == 9)
           n++;
         grid[i][j] = n;
       }

     while (app.isOpen()) {
       Vector2i pos = Mouse::getPosition(app);
       int x = pos.x / w;
       int y = pos.y / w;

       Event e;
       while (app.pollEvent(e)) {
         if (e.type == Event::Closed)
           app.close();

         if (e.type == Event::MouseButtonPressed)
           if (e.key.code == Mouse::Left) {
             if (grid[x][y] != 0)
               sgrid[x][y] = grid[x][y];
             else {
               check_blank(x, y, 0, 10);
             }
           } else if (e.key.code == Mouse::Right) {
             sgrid[x][y] = 11;
             if (sgrid[x][y] == 11 and grid[x][y] == 9) {
               score += 5;
             } else if (sgrid[x][y] == 11 and grid[x][y] != 9) {
               score -= 3;
             }
           }
       }
       app.clear(Color::White);

       for (int i = 1; i <= 10; i++)
         for (int j = 1; j <= 10; j++) {
           if (sgrid[x][y] == 9)
             sgrid[i][j] = grid[i][j];
           s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
           s.setPosition(i * w, j * w);
           app.draw(s);
         }

       app.display();
       if (sgrid[x][y] == 9) {
         _sleep(1 * 1000);
         app.close();
         dead();
       }
     }
   } 
   else if (mode==2) {
   	//mode2--harder
     for (int i = 1; i <= 18; i++)
       for (int j = 1; j <= 18; j++) {
         sgrid_hard[i][j] = 10;
         if (rand() % 5 == 0)
           grid_hard[i][j] = 9;
         else
           grid_hard[i][j] = 0;
       }

     for (int i = 1; i <= 18; i++)
       for (int j = 1; j <= 18; j++) {
         int n = 0;
         if (grid_hard[i][j] == 9)
           continue;
         if (grid_hard[i + 1][j] == 9)
           n++;
         if (grid_hard[i][j + 1] == 9)
           n++;
         if (grid_hard[i - 1][j] == 9)
           n++;
         if (grid_hard[i][j - 1] == 9)
           n++;
         if (grid_hard[i + 1][j + 1] == 9)
           n++;
         if (grid_hard[i - 1][j - 1] == 9)
           n++;
         if (grid_hard[i - 1][j + 1] == 9)
           n++;
         if (grid_hard[i + 1][j - 1] == 9)
           n++;
         grid_hard[i][j] = n;
       }

     while (app.isOpen()) {
       Vector2i pos = Mouse::getPosition(app);
       int x = pos.x / w;
       int y = pos.y / w;

       Event e;
       while (app.pollEvent(e)) {
         if (e.type == Event::Closed)
           app.close();

         if (e.type == Event::MouseButtonPressed)
           if (e.key.code == Mouse::Left) {
             if (grid_hard[x][y] != 0)
               sgrid_hard[x][y] = grid_hard[x][y];
             else {
               check_blank(x, y, 0, 18);
             }
           } else if (e.key.code == Mouse::Right) {
             sgrid_hard[x][y] = 11;
             if (sgrid_hard[x][y] == 11 and grid_hard[x][y] == 9) {
               score += 5;
             } else if (sgrid_hard[x][y] == 11 and grid_hard[x][y] != 9) {
               score -= 3;
             }
           }
       }
       app.clear(Color::White);

       for (int i = 1; i <= 18; i++)
         for (int j = 1; j <= 18; j++) {
           if (sgrid_hard[x][y] == 9)
             sgrid_hard[i][j] = grid_hard[i][j];
           s.setTextureRect(IntRect(sgrid_hard[i][j] * w, 0, w, w));
           s.setPosition(i * w, j * w);
           app.draw(s);
         }

       app.display();
       if (sgrid_hard[x][y] == 9) {
         _sleep(1 * 1000);
         app.close();
         dead();
       }
     }
   }
   // harder version
}

void Minesweeper::run()
{
    processInput();
}

void Doodle::DoodleForOne::selectForOne()
{
    RenderWindow select(VideoMode(1024, 768), "Select!");
    Texture back;
    back.loadFromFile("Doodles_images/start game.png");
    Sprite selectCharacter(back);
    while (select.isOpen())
    {
        select.draw(selectCharacter);
        Event s; // declare event
        int ifSelect = 0; // record the selected character
        while (select.pollEvent(s))
        {
            if (s.type == Event::Closed)
                select.close();
            else if (s.type == sf::Event::KeyPressed)
            {
                Texture show;
                Sprite showCharacter;
                /*
                 press once: preview
                 press twice: select
                 */
                if (s.key.code == sf::Keyboard::Num1 and ifSelect == 0)
                {
                    show.loadFromFile("Doodles_images/190_142/1.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(427.f, 500.f); // show the character inside the oval below
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000); // use sleep to make sure that the preview works
                    ifSelect = 1;
                }
                // press twice: directly select
                else if (s.key.code == sf::Keyboard::Num1 and ifSelect == 1)
                {
                    character = "Doodles_images/1.png";
                    select.close();
                }
                else if (s.key.code == sf::Keyboard::Num2 and ifSelect == 0)
                {
                    show.loadFromFile("Doodles_images/190_142/2.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(420.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 2;
                }
                else if (s.key.code == sf::Keyboard::Num2 and ifSelect == 2)
                {
                    character = "Doodles_images/2.png";
                    select.close();
                }
                else if (s.key.code == sf::Keyboard::Num3 and ifSelect == 0)
                {
                    show.loadFromFile("Doodles_images/190_142/3.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(410.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 3;
                }
                else if (s.key.code == sf::Keyboard::Num3 and ifSelect == 3)
                {
                    character = "Doodles_images/3.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num4 and ifSelect == 0)
                {
                    show.loadFromFile("Doodles_images/190_142/4.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(415.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 4;
                }
                else if (s.key.code == sf::Keyboard::Num4 and ifSelect == 4)
                {
                    character = "Doodles_images/4.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num5 and ifSelect == 0)
                {
                    show.loadFromFile("Doodles_images/190_142/5.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(410.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 5;
                }
                else if (s.key.code == sf::Keyboard::Num5 and ifSelect == 5)
                {
                    character = "Doodles_images/5.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num6 and ifSelect == 0)
                {
                    show.loadFromFile("Doodles_images/190_142/6.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(420.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 6;
                }
                else if (s.key.code == sf::Keyboard::Num6 and ifSelect == 6)
                {
                    character = "Doodles_images/6.png";
                    select.close();
                }
            }
        }
        select.display();
    }
}
void Doodle::DoodleForOne::processInputOne()
{
    selectForOne();

    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    t1.loadFromFile("images/2.png"); // load background
    t2.loadFromFile("Doodles_images/step.png"); // load bricks
    t3.loadFromFile(character);// load the selected character

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    point plat[20]; // array for position of bricks
    int platOld=11;
        
	font.loadFromFile("arial.ttf");
	score_text.setFont(font);
	score_text.setFillColor(sf::Color::Black);
	
	buffer.loadFromFile("bgm/sound_jump.wav");
	sound.setBuffer(buffer);
    // randomly decide the position of the bricks
    for (int i=0;i<10;i++){
       plat[i].x=rand()%400;
       plat[i].y=rand()%533;
    }

    while (app.isOpen()){
        Event e; // declare event
        while (app.pollEvent(e)){
            if (e.type == Event::Closed)
                app.close();
        }
    // use keyboard to move left / right
    if (Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left)) x-=3;
    // increase the move of the character to avoid no bricks to step on
    dy+=0.2;
    y+=dy;
    if (y>500)  dy=-10;
    // if the brick is out of window, use rand to make a new one
    if (y<h)
    for (int i=0;i<10;i++)
    {
      y=h;
      plat[i].y=plat[i].y-dy;
      if (plat[i].y>533) {plat[i].y=0; plat[i].x=rand()%400;}
    }
    // decide the criteria of giving out points
    for (int i=0;i<10;i++)
     if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
      && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0)){
      	dy=-10;
      	sound.play();
      	if(i!=platOld){
      		score++;
      		score_text.setString("Score:"+std::to_string(score)); // show immediate score
      		platOld=i;
		  }
	  }  
    // dead condition: the character is out of window
    if(y>500){
    	_sleep(1*1000);
		app.close();
		dead();
	}
    // use setposition to change the position of the character everytime it leaps
    sPers.setPosition(x,y);

    app.draw(sBackground);
    app.draw(sPers);
    for (int i=0;i<10;i++){
    	sPlat.setPosition(plat[i].x,plat[i].y);
    	app.draw(sPlat);
    	app.draw(score_text);
    }
    app.display();
	}
}
// the select fuction of two-player mode is basicly the same as the single-player mode (except for the variable to record the character)
void Doodle::DoodleForTwo::selectForTwo1()
{
    RenderWindow select(VideoMode(1024, 768), "Select!");
    Texture back;
    back.loadFromFile("Doodles_images/start game.png");
    Sprite selectCharacter(back);
	int ifSelect = 0;
    while (select.isOpen())
    {
        select.draw(selectCharacter);
        Event s;
        while (select.pollEvent(s))
        {
            if (s.type == Event::Closed)
                select.close();
            else if (s.type == sf::Event::KeyPressed)
            {
                Texture show;
                Sprite showCharacter;
                if (s.key.code == sf::Keyboard::Num1 and ifSelect != 1)
                {
                    show.loadFromFile("Doodles_images/190_142/1.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(427.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 1;
                }
                else if (s.key.code == sf::Keyboard::Num1 and ifSelect == 1)
                {
                    character1 = "Doodles_images/1.png";
                    select.close();
                }
                else if (s.key.code == sf::Keyboard::Num2 and ifSelect != 2)
                {
                    show.loadFromFile("Doodles_images/190_142/2.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(420.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 2;
                }
                else if (s.key.code == sf::Keyboard::Num2 and ifSelect == 2)
                {
                    character1 = "Doodles_images/2.png";
                    select.close();
                }
                else if (s.key.code == sf::Keyboard::Num3 and ifSelect != 3)
                {
                    show.loadFromFile("Doodles_images/190_142/3.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(410.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 3;
                }
                else if (s.key.code == sf::Keyboard::Num3 and ifSelect == 3)
                {
                    character1 = "Doodles_images/3.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num4 and ifSelect != 4)
                {
                    show.loadFromFile("Doodles_images/190_142/4.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(415.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 4;
                }
                else if (s.key.code == sf::Keyboard::Num4 and ifSelect == 4)
                {
                    character1 = "Doodles_images/4.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num5 and ifSelect != 5)
                {
                    show.loadFromFile("Doodles_images/190_142/5.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(410.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 5;
                }
                else if (s.key.code == sf::Keyboard::Num5 and ifSelect == 5)
                {
                    character1 = "Doodles_images/5.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num6 and ifSelect != 6)
                {
                    show.loadFromFile("Doodles_images/190_142/6.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(420.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 6;
                }
                else if (s.key.code == sf::Keyboard::Num6 and ifSelect == 6)
                {
                    character1 = "Doodles_images/6.png";
                    select.close();
                }
            }
        }
        select.display();
    }
}
void Doodle::DoodleForTwo::selectForTwo2()
{
    RenderWindow select(VideoMode(1024, 768), "Select!");
    Texture back;
    back.loadFromFile("Doodles_images/start game 2.png");
    Sprite selectCharacter(back);
	int ifSelect = 0;
    while (select.isOpen())
    {
        select.draw(selectCharacter);
        Event s;
        while (select.pollEvent(s))
        {
            if (s.type == Event::Closed)
                select.close();
            else if (s.type == sf::Event::KeyPressed)
            {
                Texture show;
                Sprite showCharacter;
                if (s.key.code == sf::Keyboard::Num1 and ifSelect != 1)
                {
                    show.loadFromFile("Doodles_images/190_142/1-2.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(427.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 1;
                }
                else if (s.key.code == sf::Keyboard::Num1 and ifSelect == 1)
                {
                    character2 = "Doodles_images/1-1.png";
                    select.close();
                }
                else if (s.key.code == sf::Keyboard::Num2 and ifSelect != 2)
                {
                    show.loadFromFile("Doodles_images/190_142/2-2.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(420.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 2;
                }
                else if (s.key.code == sf::Keyboard::Num2 and ifSelect == 2)
                {
                    character2 = "Doodles_images/2-1.png";
                    select.close();
                }
                else if (s.key.code == sf::Keyboard::Num3 and ifSelect != 3)
                {
                    show.loadFromFile("Doodles_images/190_142/3-2.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(410.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 3;
                }
                else if (s.key.code == sf::Keyboard::Num3 and ifSelect == 3)
                {
                    character2 = "Doodles_images/3-1.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num4 and ifSelect != 4)
                {
                    show.loadFromFile("Doodles_images/190_142/4-2.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(415.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 4;
                }
                else if (s.key.code == sf::Keyboard::Num4 and ifSelect == 4)
                {
                    character2 = "Doodles_images/4-1.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num5 and ifSelect != 5)
                {
                    show.loadFromFile("Doodles_images/190_142/5-2.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(410.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 5;
                }
                else if (s.key.code == sf::Keyboard::Num5 and ifSelect == 5)
                {
                    character2 = "Doodles_images/5-1.png";
                    select.close();
                }
                if (s.key.code == sf::Keyboard::Num6 and ifSelect != 6)
                {
                    show.loadFromFile("Doodles_images/190_142/6-2.png");
                    showCharacter.setTexture(show);
                    showCharacter.setPosition(420.f, 500.f);
                    select.draw(showCharacter);
                    select.display();
                    _sleep(1 * 1000);
                    ifSelect = 6;
                }
                else if (s.key.code == sf::Keyboard::Num6 and ifSelect == 6)
                {
                    character2 = "Doodles_images/6-1.png";
                    select.close();
                }
            }
        }
        select.display();
    }
}
void Doodle::DoodleForTwo::processInputTwo()
{
    // choose character respectively
    selectForTwo1();
    selectForTwo2();
    
    int score2 = 0;
	sf::Text score_text2; // record the score of the second plyer
    srand(time(0));

    RenderWindow app(VideoMode(800, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    t1.loadFromFile("Doodles_images/double.png");
    t2.loadFromFile("Doodles_images/step.png");
    t3.loadFromFile(character1);
    t4.loadFromFile(character2);

    Sprite sBackground(t1), sPlat(t2), sPlat2(t2), sPers(t3), sPers2(t4);

    point plat[20];
    point plat2[20];
    int platOld1=21;
	int platOld2=21;

    // adjust the position of scoretext
    font.loadFromFile("arial.ttf");
    score_text.setFont(font);
    score_text.setFillColor(sf::Color::Black);
	score_text2.setFont(font);
    score_text2.setFillColor(sf::Color::Black);
    score_text2.setPosition(400,0);
    for (int i = 0; i < 10; i++)
    {
        plat[i].x = rand() % (400-68);
        plat2[i].x = plat[i].x + 400;
        plat[i].y = rand() % 533;
        plat2[i].y = plat[i].y;
    }
    // the two-player mode is basicly two times of the code of single-player mode
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
            x2 += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left))
            x2 -= 3;
        // add A & D to allow the second player to move the character
        if (Keyboard::isKeyPressed(Keyboard::D))
            x += 3;
        if (Keyboard::isKeyPressed(Keyboard::A))
            x -= 3;

        dy += 0.2;
        y += dy;
        dy2 += 0.2;
        y2 += dy2;
        if (y > 500)
            dy = -10;
        if (y2 > 500)
            dy2 = -10;

        if (y < h)
            for (int i = 0; i < 10; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533)
                {
                    plat[i].y = 0;
                    plat[i].x = rand() % (400-68);
                }
            }

        if (y2 < h)
            for (int i = 0; i < 10; i++)
            {
                y2 = h;
                plat2[i].y = plat2[i].y - dy2;
                if (plat2[i].y > 533)
                {
                    plat2[i].y = 0;
                    plat2[i].x = rand() % 400 + 400;
                }
            }
            
        if(x<20 or x>380){
        	x = 400-x;
		}
		
		if(x2<420 or x2>780){
			x2 = 1200-x2;
		}
		
        for (int i = 0; i < 10; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))
            {
                dy = -10;
                if(i!=platOld1){
                	score++;
                	score_text.setString("Score:" + std::to_string(score));
                	platOld1=i;
            	}
            }

        for (int i = 0; i < 10; i++)
            if ((x2 + 50 > plat2[i].x) && (x2 + 20 < plat2[i].x + 68) && (y2 + 70 > plat2[i].y) && (y2 + 70 < plat2[i].y + 14) && (dy2 > 0))
            {
                dy2 = -10;
                if(i!=platOld2){
                	score2++;
                	score_text2.setString("Score:" + std::to_string(score2));
                	platOld2=i;
            	}
            }
            
        if (y > 500){
        	y=700;
        	dy=0;
		}
		
		if (y2 > 500){
        	y2=700;
        	dy2=0;
		}

        if ((y > 500) and (y2 > 500))
        {
            _sleep(1 * 1000);
            app.close();
            dead();
        }

        sPers.setPosition(x, y);
        sPers2.setPosition(x2, y2);

        app.draw(sBackground);
        app.draw(sPers);
        app.draw(sPers2);
        for (int i = 0; i < 10; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            sPlat2.setPosition(plat2[i].x, plat2[i].y);
            app.draw(sPlat);
            app.draw(sPlat2);
            app.draw(score_text);
            app.draw(score_text2);
        }
        app.display();
    }
}

void Doodle::selectMode()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Mode_Select");
    sf::Texture texture;
    texture.loadFromFile("Doodles_images/mode_select.png");
    sf::Sprite sprite(texture);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                // press 1: single-player mode
                if (event.key.code == sf::Keyboard::Num1){
                	window.close();
                    DoodleForOne doodleForOne;
                    doodleForOne.processInputOne();
				}
                // press 2: two-player mode
                else if (event.key.code == sf::Keyboard::Num2){
                	window.close();
                    DoodleForTwo doodleForTwo;
                    doodleForTwo.processInputTwo();
				}
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
void Doodle::run()
{
    selectMode();
}

//Arkanoid: Game
void Arkanoid::processInput()
{
    srand(time(0));

    RenderWindow app(VideoMode(520, 480), "Arkanoid!");
    app.setFramerateLimit(60);

	t1.loadFromFile("Arkanoid_images/block.png");
    t2.loadFromFile("images/2.png");
    t3.loadFromFile("Arkanoid_images/ball.png");
    t4.loadFromFile("Arkanoid_images/paddle.png");

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(210,470);

    Sprite block[1000];
    
    font.loadFromFile("arial.ttf");
	score_text.setFont(font);
	score_text.setFillColor(sf::Color::Black);

    int n=0;
    for (int i=1;i<=10;i++)
    for (int j=2;j<=11;j++)
      {
         block[n].setTexture(t1);
         block[n].setPosition(i*43,j*20);
         n++;
         //the ball's position
      }

    float dx=0, dy=0;
    float x=250, y=455;

    while (app.isOpen())
    {
       Event e;
       while (app.pollEvent(e))
       {
        if (e.type == Event::Closed)
             app.close();
    	if (e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::Space){
    		dx=4;
			dy=3;
		}
       }

	//ball movement settings
    x+=dx;
    for (int i=0;i<n;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); dx=-dx; score++; score_text.setString("Score:"+std::to_string(score));}

    y+=dy;
    for (int i=0;i<n;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); dy=-dy; score++; score_text.setString("Score:"+std::to_string(score));}

    if (x<0 || x>520)  dx=-dx;
    if (y<0)  dy=-dy;

    if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6,0);

    if (FloatRect(x,y,12,12).intersects(sPaddle.getGlobalBounds())) dy=-(rand()%5+2);
    
    //game over
    if(y>480){
    	_sleep(1*1000);
		app.close();
    	dead();
	}

    sBall.setPosition(x,y);

    app.clear();
    app.draw(sBackground);
    app.draw(score_text);
    app.draw(sBall);
    app.draw(sPaddle);

    for (int i=0;i<n;i++)
     app.draw(block[i]);

    app.display();
    }
}

void Arkanoid::run()
{
    processInput();
}
