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

	player.setSpeed(10);

	player.setWeapon(handgun);

	player.teleport({-10, -10});

	// Enemy
}

// MAIN LOOP


void GameManager::run()
{
	initialize();

	while (window.isOpen())
	{
		updateDT();

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
		updatePlayer();

		// Weapons
		player.getWeapon()->setTarget(static_cast<Vec2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

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

void GameManager::updateDT()
{
	deltaTime.restart();
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

	void GameManager::updatePlayer()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			player.setTarget(static_cast<Vec2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
		}

		player.updateView();

		player.update(deltaTime);
	}

	
