
#include <iostream>
#include <SFML/graphics.hpp>
#include <cstdlib>
#include <cmath>
using namespace std;

int main()
{
	sf::Color Brown(165, 80, 80);
	srand(static_cast<unsigned int>(std::time(NULL)));
	const float pi = 3.14159f;
	const float gravityAcc = 0.001f;
	const float WIDTH = 900;
	const float HEIGHT = 600;
	bool quit = false;
	while (!quit)
	{
	bool p1Turn = true;
	bool turnDone = false;
	bool gameDone = false;	

	float windFric = (rand() % 20000) / 1000000 - 0.0001;

		if (rand() % 2 == 1) { p1Turn = false; }

		sf::RenderWindow WORCHBOUND(sf::VideoMode(WIDTH, HEIGHT, 32), "Worchbound", sf::Style::Titlebar | sf::Style::Close);
		WORCHBOUND.setVerticalSyncEnabled(true);

		sf::Vector2f playerSize(40, 40);
		sf::Vector2f playerRad(playerSize.x / 2, playerSize.y / 2);
		float playerArea = playerSize.x * playerSize.y;
		float bulletToPlayerSizeRatio = 1 / 20.f;
		float bulletRad = sqrt(playerArea * bulletToPlayerSizeRatio / pi);
		float lineAngle = 3 * pi / 2;
		float bulletSpeed = 1.f;
		float bulletSpeedx = 0;
		float bulletSpeedy = 0;
		sf::Vector2f p1PlatformSize(80, rand() % 300 + 50);
		sf::Vector2f p2PlatformSize(80, rand() % 300 + 50);
		sf::Vector2f lineOrigin;


		sf::RectangleShape p1;
		p1.setSize(playerSize);
		p1.setFillColor(sf::Color::Red);
		p1.setOrigin(playerSize / 2.f);

		sf::RectangleShape p2;
		p2.setSize(playerSize);
		p2.setFillColor(sf::Color::Blue);
		p2.setOrigin(playerSize / 2.f);

		sf::RectangleShape p1Platform;
		p1Platform.setSize(p1PlatformSize);
		p1Platform.setFillColor(Brown);
		p1Platform.setOrigin(p1PlatformSize.x / 2, p1PlatformSize.y);

		sf::RectangleShape p2Platform;
		p2Platform.setSize(p2PlatformSize);
		p2Platform.setFillColor(Brown);
		p2Platform.setOrigin(p2PlatformSize.x / 2, p2PlatformSize.y);

		sf::RectangleShape powerBar;
		powerBar.setSize(sf::Vector2f(30, 240));
		powerBar.setFillColor(sf::Color::Green);


		p1Platform.setPosition(p1PlatformSize.x / 2, HEIGHT);
		p2Platform.setPosition(WIDTH - p2PlatformSize.x / 2, HEIGHT);
		p1.setPosition(p1Platform.getPosition().x, HEIGHT - p1PlatformSize.y - playerRad.y);
		p2.setPosition(p2Platform.getPosition().x, HEIGHT - p2PlatformSize.y - playerRad.y);

		sf::CircleShape bullet;
		bullet.setRadius(bulletRad);
		bullet.setFillColor(sf::Color::White);
		bullet.setOrigin(bulletRad, bulletRad);

		int count = 0;

		sf::Clock clock;

		while ((WORCHBOUND.isOpen()) && (!gameDone))
		{

			sf::Event event;
			while (WORCHBOUND.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					WORCHBOUND.close();
			}
			float gameTime = clock.restart().asMilliseconds();

			if (p1Turn)
			{
				lineOrigin = p1.getPosition();
				if (count != 1)
				{
					count = +1;
					cout << "Player 1's turn!\nGive your best shot!\n";
					bullet.setPosition(lineOrigin);
				}
			}
			else
			{
				lineOrigin = p2.getPosition();
				if (count != 1)
				{
					count = +1;
					cout << "Player 2's turn!\nGive your best shot!\n";
					bullet.setPosition(lineOrigin);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				lineAngle = lineAngle - .001f * gameTime;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				lineAngle = lineAngle + .001f * gameTime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				turnDone = true;
			}

			if (!turnDone)
			{
				bulletSpeedx = bulletSpeed * cos(lineAngle);
				bulletSpeedy = bulletSpeed * sin(lineAngle);
			}
			else
			{
				bulletSpeedx = bulletSpeedx + windFric * gameTime;
				bulletSpeedy = bulletSpeedy + gravityAcc * gameTime;
				bullet.move(bulletSpeedx * gameTime, bulletSpeedy * gameTime);
				if (p1Turn)
				{
					if ((abs(bullet.getPosition().x - p2.getPosition().x) < bulletRad + playerRad.x) &&
						(abs(bullet.getPosition().y - p2.getPosition().y) < bulletRad + playerRad.y))
					{
						gameDone = true;
						cout << "\nPlayer 1 wins\n";
						WORCHBOUND.close();
					}
					else if (bullet.getPosition().y > HEIGHT)
					{
						count = 0;
						lineOrigin = p2.getPosition();
						lineAngle = 3 * pi / 2;
						bullet.setPosition(lineOrigin);
						turnDone = false;
						p1Turn = false;
					}

				}
				else
				{
					if ((abs(bullet.getPosition().x - p1.getPosition().x) < bulletRad + playerRad.x) &&
						(abs(bullet.getPosition().y - p1.getPosition().y) < bulletRad + playerRad.y))
					{
						gameDone = true;
						cout << "\nPlayer 2 wins\n";
						WORCHBOUND.close();
					}
					else if (bullet.getPosition().y > HEIGHT)
					{
						count = 0;
						p1Turn = true;
						lineOrigin = p1.getPosition();
						lineAngle = 3*pi/2;
						bullet.setPosition(lineOrigin);
						turnDone = false;
					}
				}
			}
			sf::Vector2f lineLength(sqrt(playerArea) * (3 / 2) * cos(lineAngle), sqrt(playerArea) * (3 / 2) * sin(lineAngle));
			sf::Vertex line[] =
			{
				sf::Vertex(lineOrigin),
				sf::Vertex(lineOrigin + lineLength)
			};
			WORCHBOUND.clear();
			WORCHBOUND.draw(line, 2, sf::Lines);
			WORCHBOUND.draw(p1);
			WORCHBOUND.draw(p2);
			WORCHBOUND.draw(p1Platform);
			WORCHBOUND.draw(p2Platform);
			WORCHBOUND.draw(bullet);
			WORCHBOUND.display();
		}

		cout << "\nPlay again? [y or n]";
		string answer;
		cin >> answer;
		if (answer != "y")
			quit = true;
	}
	return 0;
}

