#include <SFML/Graphics.hpp>
#include <time.h>
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "Life Game"
#define CELL_SIZE 5
#define MAP_WIDTH WINDOW_WIDTH/CELL_SIZE
#define MAP_HEIGHT WINDOW_HEIGHT/CELL_SIZE
#define FPS 22

bool Generation[MAP_WIDTH][MAP_HEIGHT];
bool OldGeneration[MAP_WIDTH][MAP_HEIGHT];

void Generate()
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (rand() % 10 == 1)
            {
                Generation[x][y] = OldGeneration[x][y] = true;
            }
            else
            {
                Generation[x][y] = OldGeneration[x][y] = false;
            }
        }
    }
}

void UpdateOldGeneration()
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            OldGeneration[x][y] = Generation[x][y];
        }
    }
}

char GetCell(char x, char y)
{
    if ((x < 0) || (x > MAP_WIDTH - 1) || (y < 0) || (y > MAP_HEIGHT - 1))
    {
        return 0;
    }
    return (char)OldGeneration[x][y];
}

char GetCellsCount(char x, char y)
{
    return GetCell(x - 1, y) + GetCell(x - 1, y - 1) + GetCell(x, y - 1) + GetCell(x + 1, y - 1) +
        GetCell(x + 1, y) + GetCell(x + 1, y + 1) + GetCell(x, y + 1) + GetCell(x - 1, y + 1);
}

void Update()
{
    UpdateOldGeneration();
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            char cellsCount = GetCellsCount(x, y);
            if (OldGeneration[x][y] == false)
            {
                if (cellsCount == 3)
                {
                    Generation[x][y] = true;
                }
            }
            else
            {
                if ((cellsCount < 2) || (cellsCount > 3))
                {
                    Generation[x][y] = false;
                }
            }
        }
    }
}

void Draw(sf::RenderWindow* window, sf::RectangleShape* rectangle)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (Generation[x][y])
            {
                rectangle->setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window->draw(*rectangle);
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    window.setFramerateLimit(FPS);
    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color(250, 50, 50));
    rectangle.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    Generate();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            Generate();
        }
        Update();
        window.clear();
        Draw(&window, &rectangle);
        window.display();
    }
    return 0;
}