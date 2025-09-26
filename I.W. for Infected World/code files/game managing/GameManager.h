#pragma once // GameManager.h


// Memory/Umbrella
#include "memory Utils/VectorTextureWrapper.h"

#include "umbrella headers/memory.h"
#include "umbrella headers/sfml.h"

// Entities
#include "entities/Entity.h"
#include "entities/MoveableEntity.h"
#include "entities/LivingEntity.h"

#include "entities/monsters/Monster.h"

#include "entities/player/Player.h"

#include "entities/weapons/Bullet.h"

// weapons

#include "umbrella headers/GunComponents.h"

// Map
#include "map/sets/Tile.h"

using wEvent = const std::optional<sf::Event>&;

class GameManager
{
public:


	void initialize();

	void run();


	// Window

	void windowLogic(wEvent event);

	void retrieveUserInteractions();

	void updateView();

	void draw();


	// Entities


		// Player
		void retrievePlayerUses();

		void updatePlayer(const Time& dt);

		// Bullets

		void updateBullets(const Time& dt);

private:

	RenderWindow window{ sf::VideoMode({1600, 1200}), "I.W. for Infected World" };

	View gameView{};

	bool gamePaused{false};

	Vector<Bullet> bullets;

/*================================================*/

	// Map --------------------------------
	/*
	-------------------------------------------------------------------------
	* Default Zone : 
	-------------------------------------------------------------------------
	"assets/textures/map/default_zone/tile0Sp_blank01_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile1Sp_basic01_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile2Sp_basic02_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile3Sp_mud01_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile4Sp_green_grass01_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile5Sp_gravel01_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile6Sp_basic03_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile7Sp_basic04_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile8Sp_dried01_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile9Sp_basic05_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile10Sp_basic06_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile11Sp_basic07_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile12Sp_basic08_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile13Sp_green_grass02_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile14Sp_basic09_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile15Sp_purple_flower01_DEFAULT_175x175.png",
	"assets/textures/map/default_zone/tile16Sp_basic10_DEFAULT_175x175.png"
	-------------------------------------------------------------------------
	* === 
	-------------------------------------------------------------------------
	*/

	Map map
	{
		{
			{
				{
					/*"assets/textures/map/default_zone/tile0Sp_blank01_DEFAULT_175x175.png",*/
					"assets/textures/map/default_zone/tile1Sp_basic01_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile2Sp_basic02_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile3Sp_mud01_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile4Sp_green_grass01_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile5Sp_gravel01_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile6Sp_basic03_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile7Sp_basic04_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile8Sp_dried01_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile9Sp_basic05_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile10Sp_basic06_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile11Sp_basic07_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile12Sp_basic08_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile13Sp_green_grass02_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile14Sp_basic09_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile15Sp_purple_flower01_DEFAULT_175x175.png",
					"assets/textures/map/default_zone/tile16Sp_basic10_DEFAULT_175x175.png"
				}, {3, 3}, "zone"
			}
		}
	};

/*================================================*/

	// Player -----------------------------
	/*
		* Order -> Up, Down, Left, Right
		*
		-------------------------------------------------------------------------
		* Player Going Up
		-------------------------------------------------------------------------
		"assets/textures/player/default/up/playerSp_walking0_UP_22x34.png ",
		"assets/textures/player/default/up/playerSp_walking01_UP_22x35.png",
		"assets/textures/player/default/up/playerSp_walking02_UP_21x36.png",
		"assets/textures/player/default/up/playerSp_walking03_UP_22x35.png",
		"assets/textures/player/default/up/playerSp_walking04_UP_22x35.png",
		"assets/textures/player/default/up/playerSp_walking05_UP_21x36.png",
		"assets/textures/player/default/up/playerSp_walking06_UP_22x35.png"
		-------------------------------------------------------------------------
		* Player Going Down
		-------------------------------------------------------------------------
		"assets/textures/player/default/down/playerSp_walking0_DOWN_22x34.png ",
		"assets/textures/player/default/down/playerSp_walking01_DOWN_22x35.png",
		"assets/textures/player/default/down/playerSp_walking02_DOWN_21x36.png",
		"assets/textures/player/default/down/playerSp_walking03_DOWN_22x35.png",
		"assets/textures/player/default/down/playerSp_walking04_DOWN_22x35.png",
		"assets/textures/player/default/down/playerSp_walking05_DOWN_21x36.png",
		"assets/textures/player/default/down/playerSp_walking06_DOWN_22x35.png"
		-------------------------------------------------------------------------
		* Player Going Left
		-------------------------------------------------------------------------
		"assets/textures/player/default/left/playerSp_walking0_LEFT_20x33.png ",
		"assets/textures/player/default/left/playerSp_walking01_LEFT_20x33.png",
		"assets/textures/player/default/left/playerSp_walking02_LEFT_20x32.png",
		"assets/textures/player/default/left/playerSp_walking03_LEFT_20x33.png",
		"assets/textures/player/default/left/playerSp_walking04_LEFT_20x33.png",
		"assets/textures/player/default/left/playerSp_walking05_LEFT_20x32.png",
		"assets/textures/player/default/left/playerSp_walking06_LEFT_20x33.png"
		-------------------------------------------------------------------------
		* Player Going Right
		-------------------------------------------------------------------------
		"assets/textures/player/default/right/playerSp_walking0_RIGHT_20x33.png ",
		"assets/textures/player/default/right/playerSp_walking01_RIGHT_20x33.png",
		"assets/textures/player/default/right/playerSp_walking02_RIGHT_20x32.png",
		"assets/textures/player/default/right/playerSp_walking03_RIGHT_20x33.png",
		"assets/textures/player/default/right/playerSp_walking04_RIGHT_20x33.png",
		"assets/textures/player/default/right/playerSp_walking05_RIGHT_20x32.png",
		"assets/textures/player/default/right/playerSp_walking06_RIGHT_20x33.png"
		-------------------------------------------------------------------------
		*
	*/

	Player player
	{
		EntityInit{
			{
				{ // Default
					{
						// Up
						"assets/textures/player/default/up/playerSp_walking0_UP_22x34.png ",
						"assets/textures/player/default/up/playerSp_walking01_UP_22x35.png",
						"assets/textures/player/default/up/playerSp_walking02_UP_21x36.png",
						"assets/textures/player/default/up/playerSp_walking03_UP_22x35.png",
						"assets/textures/player/default/up/playerSp_walking04_UP_22x35.png",
						"assets/textures/player/default/up/playerSp_walking05_UP_21x36.png",
						"assets/textures/player/default/up/playerSp_walking06_UP_22x35.png"
					},

					{
						// Down
						"assets/textures/player/default/down/playerSp_walking0_DOWN_22x34.png ",
						"assets/textures/player/default/down/playerSp_walking01_DOWN_22x35.png",
						"assets/textures/player/default/down/playerSp_walking02_DOWN_21x36.png",
						"assets/textures/player/default/down/playerSp_walking03_DOWN_22x35.png",
						"assets/textures/player/default/down/playerSp_walking04_DOWN_22x35.png",
						"assets/textures/player/default/down/playerSp_walking05_DOWN_21x36.png",
						"assets/textures/player/default/down/playerSp_walking06_DOWN_22x35.png"
					},

					{
						// Left
						"assets/textures/player/default/left/playerSp_walking0_LEFT_20x33.png ",
						"assets/textures/player/default/left/playerSp_walking01_LEFT_20x33.png",
						"assets/textures/player/default/left/playerSp_walking02_LEFT_20x32.png",
						"assets/textures/player/default/left/playerSp_walking03_LEFT_20x33.png",
						"assets/textures/player/default/left/playerSp_walking04_LEFT_20x33.png",
						"assets/textures/player/default/left/playerSp_walking05_LEFT_20x32.png",
						"assets/textures/player/default/left/playerSp_walking06_LEFT_20x33.png"
					},

					{
						// Right
						"assets/textures/player/default/right/playerSp_walking0_RIGHT_20x33.png ",
						"assets/textures/player/default/right/playerSp_walking01_RIGHT_20x33.png",
						"assets/textures/player/default/right/playerSp_walking02_RIGHT_20x32.png",
						"assets/textures/player/default/right/playerSp_walking03_RIGHT_20x33.png",
						"assets/textures/player/default/right/playerSp_walking04_RIGHT_20x33.png",
						"assets/textures/player/default/right/playerSp_walking05_RIGHT_20x32.png",
						"assets/textures/player/default/right/playerSp_walking06_RIGHT_20x33.png"
					}
				}
			},
			{
				{
					"assets/sounds/beep.wav"
				}
			},
			{
				{
					"assets/fonts/arial.ttf"
				}
			}
		},

		map };

/*================================================*/

	// Weapons ----------------------------
		
		/*=================================*/

		// Handgun ------------------------
		/*
		* Order -> Standing, Animation
		*
		-------------------------------------------------------------------------
		* Gun Standing
		-------------------------------------------------------------------------
		"assets/textures/weapons/guns/handgun/HandgunSp_standing01_11x7.png"
		-------------------------------------------------------------------------
		* Gun Animation
		-------------------------------------------------------------------------
		"assets/textures/weapons/guns/handgun/HandgunSp_shooting01_19x12.png",
		"assets/textures/weapons/guns/handgun/HandgunSp_shooting02_23x12.png",
		"assets/textures/weapons/guns/handgun/HandgunSp_shooting03_24x13.png"
		-------------------------------------------------------------------------
		* ===
		*/
		
		HandGun handgun
		{
			GunInit{
				EntityInit{
					{
						{
							{
								"assets/textures/weapons/guns/handgun/HandgunSp_standing01_11x7.png"
							},
							{
								"assets/textures/weapons/guns/handgun/anims/HandgunSp_shooting01_19x12.png",
								"assets/textures/weapons/guns/handgun/anims/HandgunSp_shooting02_23x12.png",
								"assets/textures/weapons/guns/handgun/anims/HandgunSp_shooting03_24x13.png"
							}
						}
					},
					{
						{
							"assets/sounds/beep.wav"
						}
					},
					{
						"assets/fonts/arial.ttf"
					}
				},
				player, bullets, 3, 5, 400, 1, 40, 0.5, 1
			}
		};
		


		// Rifle --------------------------
		/*
		* Order -> Standing, Animation
		*
		-------------------------------------------------------------------------
		* Gun Standing
		-------------------------------------------------------------------------
		"assets/textures/weapons/guns/rifle/RifleSp_standing01_37x8.png"
		-------------------------------------------------------------------------
		* Gun Animation
		-------------------------------------------------------------------------
		"assets/textures/weapons/guns/rifle/anims/RifleSp_shooting01_43x10.png",
		"assets/textures/weapons/guns/rifle/anims/RifleSp_shooting02_46x10.png",
		"assets/textures/weapons/guns/rifle/anims/RifleSp_shooting03_49x11.png"
		-------------------------------------------------------------------------
		* ===
		*/

		Rifle rifle
		{
			GunInit{
				EntityInit{
					{
						{
							{
								"assets/textures/weapons/guns/rifle/RifleSp_standing01_37x8.png"
							},
							{
								"assets/textures/weapons/guns/rifle/anims/RifleSp_shooting01_43x10.png",
								"assets/textures/weapons/guns/rifle/anims/RifleSp_shooting02_46x10.png",
								"assets/textures/weapons/guns/rifle/anims/RifleSp_shooting03_49x11.png"
							}
						}
					},
					{
						{
							"assets/sounds/beep.wav"
						}
					},
					{
						"assets/fonts/arial.ttf"
					}
				},
				player, bullets, 6, 20, 600, 1, 30, 10, 8
			}
		};



		// ShotGun ------------------------
		/*
		* Order -> Standing, Animation
		*
		-------------------------------------------------------------------------
		* Gun Standing
		-------------------------------------------------------------------------
		"assets/textures/weapons/guns/shotgun/ShotgunSp_standing01_25x7.png"
		-------------------------------------------------------------------------
		* Gun Animation
		-------------------------------------------------------------------------
		"assets/textures/weapons/guns/shotgun/anims/ShotgunSp_shooting01_38x11.png",
		"assets/textures/weapons/guns/shotgun/anims/ShotgunSp_shooting02_41x11.png",
		"assets/textures/weapons/guns/shotgun/anims/ShotgunSp_shooting03_44x11.png"
		-------------------------------------------------------------------------
		* ===
		*/
		
		ShotGun shotgun
		{
			GunInit{
				EntityInit{
					{
						{
							{
								"assets/textures/weapons/guns/shotgun/ShotgunSp_standing01_25x7.png"
							},
							{
								"assets/textures/weapons/guns/shotgun/anims/ShotgunSp_shooting01_38x11.png",
								"assets/textures/weapons/guns/shotgun/anims/ShotgunSp_shooting02_41x11.png",
								"assets/textures/weapons/guns/shotgun/anims/ShotgunSp_shooting03_44x11.png"
							}
						}
					},
					{
						{
							"assets/sounds/beep.wav"
						}
					},
					{
						"assets/fonts/arial.ttf"
					}
				},
				player, bullets, 2, 50, 200, 5, 10, 0.01, 4
			}
		};


/*================================================*/

	// Monster ----------------------------
	/*
	-------------------------------------------------------------------------

	-------------------------------------------------------------------------
	* ===
	*/

	Monster monster
	{
		EntityInit
		{
			{
				{
					{
						"assets/textures/tile.png"
					}
				}

			},

			{
				{
					"assets/sounds/beep.wav"
				}
			},

			{
				{
					"assets/fonts/arial.ttf"
				}
			}
		}, map, bullets, &player

	};


};