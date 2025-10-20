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


GameManager::GameManager()
	: weapons{ &handgun, &rifle, &shotgun }
{
	// Debug

/*player.getPlayerDebug().dCollect = true;*/
/*player.getPlayerDebug().dProtective = true;*/

	shotgun.setDebug(true);
	rifle.setDebug(true);
	handgun.setDebug(true);

	// Window

	window.setFramerateLimit(60);
	

	// View 
	gameView.setSize( Vec2f{ window.getDefaultView().getSize().x, window.getDefaultView().getSize().y } / 2.f);
	ui.getView().setSize({ window.getDefaultView().getSize().x, window.getDefaultView().getSize().y });
	ui.getView().setCenter({-3000, -3000});

	// Map

	map.loadCurrentZone();


	// Player

	player.setSpeed(50);

	player.teleport({ 100, 100 });

	player.setRadiusProtectiveArea(50);
	player.setRadiusCollectCircle(30);

	player.getLifeBar().setSize({ 300, 10 });

	// Enemies
}


// MAIN LOOP


void GameManager::run()
{
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
			{
				if (mouse->button == sf::Mouse::Button::Left)
					player.getWeapon()->setShootTarget(static_cast<Vec2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
			}

			if (auto mouse = event->getIf< sf::Event::MouseWheelScrolled>())
			{
				if (mouse->delta > 0)
					ui.nextWeapon(true);
				else
					ui.nextWeapon(false);
			}

			if(auto keyboard = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyboard->scancode == sf::Keyboard::Scan::F1)
					addMonster();

				if (keyboard->scancode == sf::Keyboard::Scan::F2)
					for (auto& monster : monsters)
						monster->die();

				/*if (keyboard->scancode == sf::Keyboard::Scan::F3)
					*/

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
			player.setWeapon(ui.getCurrentWeapon());

			updatePlayer(dTime);

			for (auto& monster : monsters)
				player.updateHitEntity(*monster);

			// Weapons
			player.getWeapon()->setTarget(static_cast<Vec2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

			// Bullets
			updateBullets(dTime);

			// Enemies
			for(auto& monster : monsters)
			{
				monster->retrievePlayerPosition(player.getCurrentPosition());
				monster->update(dTime);
				monster->updateHiting(player, bullets);
			}

			monsters.erase(std::remove_if(monsters.begin(), monsters.end(), [&](const std::unique_ptr<Monster>& ms) {
				
				if(ms->isDead())
				{
					Collectible coll{ base_collectible.getSharedTextures() };
					coll.teleport(ms->getCurrentPositionTextures());

					collectibles.push_back(std::move(coll));
				}

				return ms->isDead();
				}), monsters.end());

			// Collectibles
			for (auto& collect : collectibles)
				if (player.isWithinCollectCircle(collect.getPositionMiddle()))
					collect.collect();

			collectibles.erase(std::remove_if(collectibles.begin(), collectibles.end(), [&](const Collectible& coll) 
				{

					if (coll.isCollected())
						player.setFleshCount(player.getFleshCount() + 1);

				return coll.isCollected(); 
				}), collectibles.end()); 


			// UI

			
			ui.update(player);

		}
		

		// Window

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
		gameView.setSize(Util::vec2_cast<float>(window.getSize()) / 2.f);

		ui.seResize(true);
		ui.getView().setSize(gameView.getSize() * 2.f);
	}
}

void GameManager::retrieveUserInteractions()
{
}

void GameManager::draw()
{
	window.clear(); // Leaves the window in a fresh state
	
	gameView.setCenter(player.getCurrentPosition());
	window.setView(gameView);

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
			window.draw(*monster);

	// Menu
		window.setView(ui.getView());

		window.draw(ui);

	// Debug Menu



	window.display(); // Displays everything

	window.setView(gameView);
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

		player.setViewSize({ gameView.getSize().x - ui.getLifeSizeC().x, gameView.getSize().y - ui.getLifeSizeC().y });
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
		std::unique_ptr<Monster> temp;

		if (u_int random{ static_cast<u_int>(Util::random_number(100, 100)) };
			random >= 0 && random <= 40)
		{
			std::cout << "Corpse\n";
			temp = std::make_unique<Corpse_Lurker>(the_corpse_lurker.getSharedInit(), sf::FloatRect{ map.getPosition(), map.getPosition_plus_Size() });
		}
		else if (random > 40 && random <= 90)
		{
			std::cout << "Crooked\n";
			temp = std::make_unique<Crooked>(the_crooked_one.getSharedInit());
		}
		else
		{
			std::cout << "Puffer\n";
			temp = std::make_unique<Puffer>(the_puffer.getSharedInit(), map.getPosition(), map.getPosition_plus_Size());
		}

		Vec2f mTextSize{};

		if(temp)
		{
			mTextSize = Util::vec2_cast<float>(temp->getCurrentTexture().getSize());



			if (Vec2f startingPos{ Util::random_point<float>(map.getPosition(), map.getPosition_plus_Size() - mTextSize) };
				!player.isWithinProtectiveArea(startingPos)
				&& !player.isWithinProtectiveArea(startingPos + mTextSize)
				&& !player.isWithinProtectiveArea({ startingPos.x + mTextSize.x, startingPos.y })
				&& !player.isWithinProtectiveArea({ startingPos.x, startingPos.y + mTextSize.y })

				)
			{
				temp->teleport(startingPos);
				monsters.push_back(std::move(temp));
			}
		}
	}

	
