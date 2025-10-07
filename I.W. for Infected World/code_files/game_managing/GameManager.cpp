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
	
	player.getPlayerDebug().dCollect = true;
	player.getPlayerDebug().dProtective = true;
	
	shotgun.setDebug(true);
	rifle.setDebug(true);
	handgun.setDebug(true);

	// Window

	window.setFramerateLimit(60);

		// View 
		gameView.setSize({ window.getDefaultView().getSize().x, window.getDefaultView().getSize().y });


	// Map

	map.loadCurrentZone();


	// Player

	player.setSpeed(50);

	player.setWeapon(rifle);

	player.teleport({100, 100});

	player.setRadiusProtectiveArea(50);
	player.setRadiusCollectCircle(20);

	// Enemies
	
	
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
				if (keyboard->scancode == sf::Keyboard::Scan::F1)
					addMonster();

				if (keyboard->scancode == sf::Keyboard::Scan::F2)
					for (auto& monster : monsters)
						monster.die();

				/*if (keyboard->scancode == sf::Keyboard::Scan::F3)*/
					

				if (keyboard->scancode == sf::Keyboard::Scan::Numpad0)
					gameView.zoom(0.5);

				if (keyboard->scancode == sf::Keyboard::Scan::Numpad1)
					gameView.zoom(1.5);
			}
		}


		if(!gamePaused)
		{

			// Map

			// Player
			updatePlayer(dTime);

			// Weapons
			player.getWeapon()->setTarget(static_cast<Vec2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

			// Bullets
			updateBullets(dTime);

			// Enemy
			for(auto& monster : monsters)
			{
				monster.setTarget(player.getCurrentPosition());
				monster.update(dTime);
				monster.updateHiting(player, bullets);
			}

			monsters.erase(std::remove_if(monsters.begin(), monsters.end(), [&](const Monster& ms) {
				
				if(ms.isDead())
				{
					Collectible coll{ base_collectible.getSharedTextures() };
					coll.teleport(ms.getCurrentPositionTextures());

					collectibles.push_back(std::move(coll));
				}

				return ms.isDead();
				}), monsters.end());

			// Collectibles
			for (auto& collect : collectibles)
				if (player.isWithinCollectCircle(collect.getPosition()))
					collect.collect();

			collectibles.erase(std::remove_if(collectibles.begin(), collectibles.end(), [](const Collectible& coll) {return coll.isCollected(); }), collectibles.end()); 
		}
		

		// Window
		updateView();


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

	if (event->getIf<sf::Event::Resized>())
	{
		gameView.setSize(Util::vec2_cast<float>(window.getSize()));
	}
}

void GameManager::retrieveUserInteractions()
{
}

void GameManager::updateView()
{
	gameView.setCenter(player.getCurrentPosition());
	window.setView(gameView);
}

void GameManager::draw()
{
	window.clear(); // Leaves the window in a fresh state
	

	// Map 
	window.draw(map);
	
	// Buildings/Gates

	// Collectibles
	for(const auto& collectible : collectibles)
		window.draw(collectible);

	// Player
	window.draw(player);

	// Weapons
	window.draw(*player.getWeapon());
		// Bullets
		for (const auto& i : bullets)
			window.draw(i);

	//Enemies
		for(const auto& monster : monsters)
			window.draw(monster);

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


		player.update(dt);
	}

	// BULLETS

	void GameManager::updateBullets(const Time& dt)
	{
		for (auto& bullet : bullets)
		{
			bullet.update(dt);
		}

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const Bullet& bull) {return bull.reachedTarget; }), bullets.end());
	}

	// MONSTERS

	void GameManager::addMonster()
	{
		Vec2f mTextSize{ Util::vec2_cast<float>(baseMonster.getCurrentTexture().getSize()) };

		if(Vec2f startingPos{Util::random_point<float>(map.getPosition(), map.getPosition_plus_Size() - mTextSize)};
			!player.isWithinProtectiveArea(startingPos) 
			&& !player.isWithinProtectiveArea(startingPos + mTextSize)
			&& !player.isWithinProtectiveArea({startingPos.x + mTextSize.x, startingPos.y})
			&& !player.isWithinProtectiveArea({startingPos.x, startingPos.y + mTextSize.y})
			
			)
		{

			Monster monster
			{
				baseMonster.getSharedInit()
			};

			monster.teleport(startingPos);

			monster.setSpeed(20);

			monster.set(Traits::Life, Specifier::Max, 50);
			monster.set(Traits::Life, Specifier::Current, 50);


			monsters.push_back(std::move(monster));
		}
	}

	
