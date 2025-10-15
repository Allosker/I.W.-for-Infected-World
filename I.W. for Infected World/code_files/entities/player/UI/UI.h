#pragma once // UI.h

#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"

#include "umbrella headers/GunComponents.h"

#include "Utilities/visual_effects/DisplayBar.h"

#include "entities/player/Player.h"

class UI
	: public sf::Drawable
{
public:

	UI(const SystemPath& fontPath,  Vector<Weapon*>& _weapons, const Util::DisplayBar& bar);


	void setViewSize(const Vec2f& nvs) noexcept;


	Vec2u getLifeSizeC() const noexcept;

	Vec2u getMoneySizeC() const noexcept;

	Vec2u getFleshSizeC() const noexcept;

	Vec2u getEquipedSizeC() const noexcept;

	Weapon* getCurrentWeapon() noexcept;

	View& getView() noexcept;


	void nextWeapon(bool up) noexcept;

	void setWeapons() noexcept;


	void update( Player& player) noexcept;


	void draw(RenderTarget& target, RenderStates states) const override;


private:


	u_int size{40};

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

	 const Util::DisplayBar& lifeBar;

	 sf::View uiView{};

	 Vec2f viewPos{};

};
