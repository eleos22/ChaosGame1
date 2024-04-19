// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>


// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Timber Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    sf::Font font;
    sf::Text text;
    sf::Text text1;
    if (!font.loadFromFile("Arial.ttf"))
    {
        // error..
    }
    text.setFont(font);
    text1.setFont(font);
    text.setString("Please pick three verticies that form a triangle!");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        text1.setString("\n Please pick the first point between the triangle!");
                        text1.setCharacterSize(20);
                        text1.setFillColor(sf::Color::Blue);
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        cout << "This is the size of the points vector" << points.size() << endl;;
                    }
                }
            }
        }



        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.

            // more points
            int maxPoints =2;               // not sure how many points but this should maybe be fine
            for (int i = 0; i < maxPoints; i++)
            {
                int randomIndex = rand() % vertices.size(); // generate random index in range of vertices vector
                Vector2f randomVertex = vertices[randomIndex]; // use randomIndex to get random vertex from vertices vector

                // mid point calc of random vertex and last point in points vector
                Vector2f lastPoint = points.back(); // last point in the vector
                Vector2f midPoint; // to hold the midpoint
                midPoint.x = (randomVertex.x + lastPoint.x) / 2; // calc x coord of midpoint
                midPoint.y = (randomVertex.y + lastPoint.y) / 2; // calc y coord of midpoint

                // push back newly generated coordinate
                points.push_back(midPoint);
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();
        window.draw(text);
        for (int i = 0; i < vertices.size(); i++)
        {

            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
        window.draw(text1);
        for (int i = 0; i < points.size(); i++)
        {

            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }


        window.display();
    }
}