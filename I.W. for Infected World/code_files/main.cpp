#include <iostream>


#include "memory Utils/VectorTextureWrapper.h"

#include "umbrella headers/sfml.h"

#include "entities/Entity.h"
#include "entities/MoveableEntity.h"
#include "entities/LivingEntity.h"
#include "entities/player/Player.h"

#include "map/sets/Zone.h"
#include "map/sets/Tile.h"

#include "game_managing/GameManager.h"


//#include <iostream>
//
//
//static std::ostream& operator<<(std::ostream& out, const Vec2f& v)
//{
//	out << v.x;
//	out << ' ';
//	out << v.y;
//	out << '\n';
//	return out;
//}

int main()
{

	try
	{
		GameManager gm;

		gm.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what();
	}

	return 0;
}