#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <ctime>
#include <windows.h>
bool Bdebug = false;
struct debug
{

    void printMousePosition(sf::RenderWindow& window)
    {
        std::cout << "x:" << sf::Mouse::getPosition(window).x << " === y:" << sf::Mouse::getPosition(window).y << '\n';
    }

}Debug;
struct characters
{
    sf::Vector2i position;
    int XorO = -1;//1 -> O -- X -> 2//d/&
};
struct SpriteNTextures
{
    sf::Texture gameField;
    sf::Texture TextureO;
    sf::Texture TextureX;
    sf::Sprite playerSprite;
    sf::Sprite gameFieldSprite;
}design;
class calc
{
private:
    int row = -1;
    int column = -1;
    int field = -1;
    int startup = 1;
    int fields[10][10];
    std::vector<int> filledFields;
public:
    int whatsnextfield = 0;
private:
    //Calculating current row or column
    int Row(sf::RenderWindow* window)
    {
        int MouseY = getMouseY(window);

        if (MouseY < 66 && MouseY > 0)
            row = 1;
        else if (MouseY < 135 && MouseY > 69)
            row = 2;
        else if (MouseY < 207 && MouseY > 139)
            row = 3;
        else if (MouseY < 321 && MouseY > 256)
            row = 4;
        else if (MouseY < 391 && MouseY > 325)
            row = 5;
        else if (MouseY < 463 && MouseY > 396)
            row = 6;
        else if (MouseY < 578 && MouseY > 510)
            row = 7;
        else if (MouseY < 647 && MouseY > 582)
            row = 8;
        else if (MouseY < 720 && MouseY > 650)
            row = 9;
        else
        {
            row = -1;
            return -1;
        }
        return row;
    }
    int Row(sf::Vector2i SpritePos)
    {
        int MouseY = SpritePos.y;

        if (MouseY < 66 && MouseY > 0)
            return 1;
        else if (MouseY < 135 && MouseY > 69)
            return 2;
        else if (MouseY < 207 && MouseY > 139)
            return 3;
        else if (MouseY < 321 && MouseY > 256)
            return 4;
        else if (MouseY < 391 && MouseY > 325)
            return 5;
        else if (MouseY < 463 && MouseY > 396)
            return 6;
        else if (MouseY < 578 && MouseY > 510)
            return 7;
        else if (MouseY < 647 && MouseY > 582)
            return 8;
        else if (MouseY < 720 && MouseY > 650)
            return 9;
        else
        {
            return -1;
        }
    }
    int Column(sf::RenderWindow* window)
    {
        int MouseX = getMouseX(window);
        if (MouseX < 66 && MouseX > 0)
            column = 1;
        else if (MouseX < 135 && MouseX > 69)
            column = 2;
        else if (MouseX < 207 && MouseX > 139)
            column = 3;
        else if (MouseX < 321 && MouseX > 256)
            column = 4;
        else if (MouseX < 391 && MouseX > 325)
            column = 5;
        else if (MouseX < 463 && MouseX > 396)
            column = 6;
        else if (MouseX < 578 && MouseX > 510)
            column = 7;
        else if (MouseX < 647 && MouseX > 582)
            column = 8;
        else if (MouseX < 720 && MouseX > 650)
            column = 9;
        else
        { 
            column = -1;
            return -1;
        }
        return column;


    }
    int Column(sf::Vector2i SpritePos)
    {
        int MouseX = SpritePos.x;
        if (MouseX < 66 && MouseX > 0)
            return 1;
        else if (MouseX < 135 && MouseX > 69)
            return 2;
        else if (MouseX < 207 && MouseX > 139)
            return 3;
        else if (MouseX < 321 && MouseX > 256)
            return 4;
        else if (MouseX < 391 && MouseX > 325)
            return 5;
        else if (MouseX < 463 && MouseX > 396)
            return 6;
        else if (MouseX < 578 && MouseX > 510)
            return 7;
        else if (MouseX < 647 && MouseX > 582)
            return 8;
        else if (MouseX < 720 && MouseX > 650)
            return 9;
        else
            return -1;
    }
    int checkError(sf::RenderWindow* window)//If clicked outside of play area
    {
        int nextField = whatsnextField(window);
        if ((row == -1) || (column == -1) || (field == -1) || (nextField == -1))
            return 1;
        else
            return 0;
    }
    int fieldNumber(sf::RenderWindow* window)
    {
        currentField(window);
        int nextField = whatsnextField(window);
        if (!checkError(window))
            return (nextField + 9 * (field - 1));
        else
            return -1;
    }

public:
    int whatsnextField(sf::RenderWindow* window)//Gets the field the next player has to play in 
    {
        std::cout << Row(window);
        std::cout << Column(window) << '\n';
        int nextField = 0;
        if (column == 1 || column == 4 || column == 7)
        {
            if (row == 1 || row == 4 || row == 7)
                nextField = 1;
            else if (row == 2 || row == 5 || row == 8)
                nextField = 4;
            else
                nextField = 7;

        }
        else if (column == 2 || column == 5 || column == 8)
        {
            if (row == 1 || row == 4 || row == 7)
                nextField = 2;
            else if (row == 2 || row == 5 || row == 8)
                nextField = 5;
            else
                nextField = 8;

        }
        else if (column == 3 || column == 6 || column == 9)
        {
            if (row == 1 || row == 4 || row == 7)
                nextField = 3;
            else if (row == 2 || row == 5 || row == 8)
                nextField = 6;
            else
                nextField = 9;

        }
        if (column == -1 || row == -1 || field == -1)
        {
            nextField = -1;
            return -1;
        }
        else
            return nextField;
    }
    int currentField(sf::RenderWindow* window)//Calculates field on which mouse cursor is clicking
    {
        int tempRow = Row(window);
        int tempColumn = Column(window);
        if (tempRow <= 3 && tempRow > 0)
        {
            if (tempColumn <= 3 && tempColumn > 0)
                field = 1;
            if (tempColumn <= 6 && tempColumn > 3)
                field = 2;
            if (tempColumn <= 9 && tempColumn > 6)
                field = 3;
        }
        if (tempRow <= 6 && tempRow > 3)
        {
            if (tempColumn <= 3 && tempColumn > 0)
                field = 4;
            if (tempColumn <= 6 && tempColumn > 3)
                field = 5;
            if (tempColumn <= 9 && tempColumn > 6)
                field = 6;
        }
        if (tempRow <= 9 && tempRow > 6)
        {
            if (tempColumn <= 3 && tempColumn > 0)
                field = 7;
            if (tempColumn <= 6 && tempColumn > 3)
                field = 8;
            if (tempColumn <= 9 && tempColumn > 6)
                field = 9;
        }
        if (tempRow == -1 || tempColumn == -1)
        {
            field = -1;
            return -1;
        }
        return field;
    }
    int getMouseX(sf::RenderWindow* window)
    {
        return sf::Mouse::getPosition(*window).x;
    }
    int getMouseY(sf::RenderWindow* window)
    {
        return sf::Mouse::getPosition(*window).y;
    }
    sf::Vector2i charPosition(sf::Vector2i position)//Calculates middle position of clicked field
    { 
            int lRow = Row(position);
            int lColumn = Column(position);
            int xpos = 0;
            int ypos = 0;
            if (lRow <= 3)
            {
                ypos = 70 * (lRow - 1);
            }
            else if (lRow < 7 && lRow > 3)
            {
                ypos = 70 * (lRow - 1) + 47;
            }
            else if (lRow > 6 && lRow <= 9)
            {
                ypos = 70 * (lRow - 1) + 94;
            }
            else
                return {-9999, -9999};

            if (lColumn <= 3)
            {
                xpos = 70 * (lColumn - 1);
            }
            else if (lColumn < 7 && lColumn > 3)
            {
                xpos = 70 * (lColumn - 1) + 47;
            }
            else if (lColumn > 6 && lColumn <= 9)
            {
                xpos = 70 * (lColumn - 1) + 94;
            }
            else
                return { -9999, -9999 };

                return {xpos, ypos};

    }
    int isFilled(sf::RenderWindow* window)
    {
        int checkNumber = fieldNumber(window);
        if (std::find(filledFields.begin(), filledFields.end(), checkNumber) == filledFields.end())
        {
            filledFields.push_back(fieldNumber(window));
            return 0;
        }
        else
            return 1;


    }
    void insertFields(sf::RenderWindow* window,int curPlayer)
    {
        int outerField = currentField(window);
        int innerField = whatsnextField(window);

        fields[outerField][innerField] = curPlayer;

        std::cout << outerField << "|" << innerField << ">>" << fields[outerField][innerField];
    }
    int rightField(sf::RenderWindow* window)
    {
        int nextField = 0;
        int curField = currentField(window);
        if (startup)
        {
            whatsnextfield = 5;
            startup = 0;
        }
        else
        std::cout << "Current Field: " << curField << " Next Field: " << whatsnextfield << '\n';

        if (curField == whatsnextfield)
        {
            std::cout << "Hello";
            whatsnextfield = whatsnextField(window);
            return 1;
        }
        else
            std::cout << "NoNo";


        
        return 0;
        
    }
    void checkWin(sf::RenderWindow* window, int curPlayer)//Sets the win state if player wins outer field
    {
        
        int globalField = currentField(window);

        if (globalField != -1)
        {
            if ((fields[globalField][1] == curPlayer && fields[globalField][2] == curPlayer && fields[globalField][3] == curPlayer) ||
                (fields[globalField][4] == curPlayer && fields[globalField][5] == curPlayer && fields[globalField][6] == curPlayer) ||
                (fields[globalField][7] == curPlayer && fields[globalField][8] == curPlayer && fields[globalField][9] == curPlayer) ||
                (fields[globalField][1] == curPlayer && fields[globalField][4] == curPlayer && fields[globalField][7] == curPlayer) ||
                (fields[globalField][2] == curPlayer && fields[globalField][5] == curPlayer && fields[globalField][8] == curPlayer) ||
                (fields[globalField][3] == curPlayer && fields[globalField][6] == curPlayer && fields[globalField][9] == curPlayer) ||
                (fields[globalField][1] == curPlayer && fields[globalField][5] == curPlayer && fields[globalField][9] == curPlayer) ||
                (fields[globalField][3] == curPlayer && fields[globalField][5] == curPlayer && fields[globalField][7] == curPlayer))
            {
                for (int i = 0; i < 9; i++)
                {
                    for (int y = 0; y < 9; y++)
                    {
                       std::cout << i << " " << y << " " << fields[i][y] << '\n';
                    }
                }
                fields[globalField][0] = curPlayer;//Assigns field to winning player
            }
        }
    }
    int isDone(sf::RenderWindow* window)//checks if outer field is already done
    {
        int field = currentField(window);
        if (fields[field][0] != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};
void init()
{
    design.TextureO.loadFromFile("TexturesUTTT/O.png");
    design.TextureX.loadFromFile("TexturesUTTT/X.png");
    design.gameField.loadFromFile("TexturesUTTT/GameField.png");
    design.gameFieldSprite.setTexture(design.gameField);

}
void drawCharacters(std::vector<characters>* chr, sf::RenderWindow* window)
{
    std::vector<characters>& chrRef = *chr;

    for (int i = 0; i < chrRef.size(); i++)
    {
        if (chrRef[i].XorO == 1)
            design.playerSprite.setTexture(design.TextureO);
        else if (chrRef[i].XorO == 2)
            design.playerSprite.setTexture(design.TextureX);

        design.playerSprite.setPosition(chrRef[i].position.x , chrRef[i].position.y);
        window->draw(design.playerSprite);
    }

}
int main()
{
    int curPlayer = 1;
    init();
    calc cal;
    sf::RenderWindow window(sf::VideoMode(design.gameField.getSize().x, design.gameField.getSize().y), "Ultimate Tic Tac Toe By Kian Devbuild", sf::Style::Titlebar | sf::Style::Close );
    std::vector<characters> charVector;//Vector that contains all filled squares
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouseCoords = { cal.getMouseX(&window), cal.getMouseY(&window) }; // Get current position of mouse cursor
                    if (!cal.isDone(&window) && cal.rightField(&window)&& !cal.isFilled(&window)) // Check if player plays in the correct field
                    {
                    sf::Vector2i charPos = cal.charPosition(mouseCoords); //Calculates position of Characters(X or O)
                    charVector.push_back({{charPos}, curPlayer});//Adds character to a Vector with all the squares that are already filled
                   cal.insertFields(&window, curPlayer);//Inserts the playerId(0 or 1) into an array at place[currentOuterField][currentInnerField]
                   cal.checkWin(&window, curPlayer);//Checks if whole outer field is done

                   //Switch players after move
                    if (curPlayer == 1)
                        curPlayer = 2;
                    else
                        curPlayer = 1;
                }
                    
                }
            }
        }
        //Things to display graphics
        window.draw(design.gameFieldSprite);
        drawCharacters(&charVector,  &window);
        window.display();
        window.clear();
        Sleep(1);
    }

   



     return 0;
}
        
       