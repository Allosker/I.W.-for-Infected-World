#include "GameManager.h"

#include <iostream>
static std::ostream& operator<<(std::ostream& out, const Vec2f& v)
{
	out << v.x;
	out << ' ';
	out << v.y;
	out << '\n';
	return out;
}


// INITIALIZATION


void GameManager::initialize()
{
	// Debug
	
	player.setDebug(true);
	

	// Window

	window.setFramerateLimit(60);


	// Map

	map.loadCurrentZone();


	// Player

	player.setViewSize({ window.getDefaultView().getSize().x, window.getDefaultView().getSize().y });

	player.setSpeed(50);

	/*player.setWeapon(handgun);*/

	player.teleport({10, 10});

	// Enemy
}

// MAIN LOOP


void GameManager::run()
{
	initialize();

	Clock clock;
	Time dTime;
	while (window.isOpen())
	{
		dTime = clock.restart();

		// Event If-Statement
		while (auto event = window.pollEvent())
		{
			windowLogic(event);

			if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>())
				if (mouse->button == sf::Mouse::Button::Left)
					player.getWeapon()->setShootTarget(static_cast<Vec2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

			if(auto keyboard = event->getIf<sf::Event::KeyPressed>())
			{
				/*if (keyboard->scancode == sf::Keyboard::Scan::F1)
					*/

				if (keyboard->scancode == sf::Keyboard::Scan::Numpad0)
					player.zoomView(0.5);

				if (keyboard->scancode == sf::Keyboard::Scan::Numpad1)
					player.zoomView(1.5);
			}
		}

		// Window

		updateView();
		
		// Map

		// Player
		updatePlayer(dTime);

		// Weapons
		player.getWeapon()->setTarget(static_cast<Vec2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

			// Bullets
			updateBullets(dTime);

		// Enemy

		draw();

	}
}


// WINDOW



void GameManager::windowLogic(wEvent event)
{
	if (event->getIf<sf::Event::Closed>())
	{
		window.close();
	}
}

void GameManager::retrieveUserInteractions()
{
}

void GameManager::updateView()
{
	window.setView(player.getView());
}

void GameManager::draw()
{
	window.clear(); // Leaves the window in a fresh state
	

	// Map 
	window.draw(map);
	
	// Buildings/Gates

	// Player
	window.draw(player);

	// Weapons
	window.draw(*player.getWeapon());
		// Bullets
		for (const auto& i : bullets)
			window.draw(i);

	//Enemies

	// Menu

	// Debug Menu


	window.display(); // Displays everything
}


// ENTITIES



	// PLAYER

	void GameManager::retrievePlayerUses()
	{
		// Sets the target of the player for it to go there
		
	}

	void GameManager::updatePlayer(const Time& dt)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			player.setTarget(static_cast<Vec2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
		}

		player.updateView();

		player.update(dt);
	}

	// BULLETS

	void GameManager::updateBullets(const Time& dt)
	{
		for (auto& bullet : bullets)
		{
			bullet.update(dt);
			/*std::cout << "Current: " << bullet.current;*/
		}

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const Bullet& bull) {return bull.reachedTarget; }), bullets.end());
	}

	
