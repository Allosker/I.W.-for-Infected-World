#pragma once // UI.h

#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"

#include "umbrella headers/GunComponents.h"

class UI
	: public sf::Drawable
{
public:

	UI(const SystemPath& fontPath,  Vector<Weapon*>& _weapons);


	void setViewSize(const Vec2f& nvs) noexcept;


	Vec2u getLifeSizeC() const noexcept;

	Vec2u getMoneySizeC() const noexcept;

	Vec2u getFleshSizeC() const noexcept;

	Vec2u getEquipedSizeC() const noexcept;


	Weapon* getCurrentWeapon() noexcept;

	void nextWeapon(bool up) noexcept;

	void setWeapons() noexcept;


	void update(const Vec2f& pPos, float m, u_int f) noexcept;


	void draw(RenderTarget& target, RenderStates states) const override;


private:

	Vec2f viewSize{};


	u_int size{30};

	sf::Font font{};

	sf::Text life;

	sf::Text money;

	sf::Text flesh;


	sf::Text equipW;

	Vector<sf::Text> wNames
	{};
	
	size_t wIndex{};
	
	 Vector<Weapon*>& weapons;
	
	 Weapon* cWeapon;

};
