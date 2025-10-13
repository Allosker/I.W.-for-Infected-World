#include "UI.h"

#include <sstream>
#include <iomanip>

#include <iostream>

UI::UI(const SystemPath& fontPath, Vector<Weapon*>& _weapons)
	: font{ fontPath },
	life{ font, "Life:", size },
	money{ font, "Money: ", size },
	flesh{ font, "Flesh count: ", size },
	equipW{ font, "Weapons:", size},
	weapons{ _weapons },
	cWeapon{weapons.at(0)}
{
	wNames.push_back({ font, "handgun", size });
	wNames.push_back({ font, "rifle", size });
	wNames.push_back({ font, "shotgun", size });

	wNames.at(0).setFillColor(Color::Red);
}

void UI::setViewSize(const Vec2f& nvs) noexcept
{
	viewSize = nvs;
}



Vec2u UI::getLifeSizeC() const noexcept
{
	return { life.getCharacterSize() * static_cast<unsigned int>(life.getString().getSize()), life.getCharacterSize() / 2 };
}

Vec2u UI::getMoneySizeC() const noexcept
{
	return { money.getCharacterSize() * static_cast<unsigned int>(money.getString().getSize()), money.getCharacterSize() / 2 };
}

Vec2u UI::getFleshSizeC() const noexcept
{
	return { flesh.getCharacterSize() * static_cast<unsigned int>(flesh.getString().getSize()), flesh.getCharacterSize() / 2 };
}

Vec2u UI::getEquipedSizeC() const noexcept
{
	return { equipW.getCharacterSize() * static_cast<unsigned int>(equipW.getString().getSize()), equipW.getCharacterSize() / 2 };
}

Weapon* UI::getCurrentWeapon() noexcept
{
	return cWeapon;
}

void UI::nextWeapon(bool up) noexcept
{
	for(short i{}; i != weapons.size(); i++)
	{
		if (!up)
			wIndex = (wIndex + 1) % weapons.size();
		else
			wIndex = (wIndex + weapons.size() - 1) % weapons.size();

		Weapon* tPtr = weapons.at(wIndex);

		if (tPtr->isAvailable())
		{
			cWeapon = tPtr;
			for (auto& w : wNames)
				w.setFillColor(Color::White);
			wNames.at(wIndex).setFillColor(Color::Red);

			break;
		}
	}
}

void UI::setWeapons() noexcept
{
	cWeapon = weapons.at(0);
}



void UI::update(const Vec2f& pPos, float m, u_int f) noexcept
{
	life.setPosition(pPos + Vec2f{ -(viewSize.x / 2), -(viewSize.y / 2)});

	std::ostringstream os;
	os << "Money: " << std::fixed << std::setprecision(2) << m;
	money.setString(os.str());

	flesh.setString("Flesh count: " + std::to_string(f));

	money.setPosition(pPos + Vec2f{ -(viewSize.x / 2) , -(viewSize.y / 2 - getLifeSizeC().y * 2) });

	flesh.setPosition(pPos + Vec2f{ -(viewSize.x / 2), -(viewSize.y / 2 - getLifeSizeC().y * 4) });


	equipW.setPosition(pPos + Vec2f{ (viewSize.x / 2 - getEquipedSizeC().x * 2), -(viewSize.y / 2) });

	// Set space between each weapon's name
	u_int temp{ getEquipedSizeC().y };
	for (short i{}; i != weapons.size(); i++)
	{
		wNames.at(i).setPosition(pPos + Vec2f{ (viewSize.x / 2 - getEquipedSizeC().x), -(viewSize.y / 2 - temp) });

		if(weapons.at(i)->isAvailable())
		{
			temp += wNames.at(i).getCharacterSize();
		}
	}
}


void UI::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(life);
	target.draw(money);
	target.draw(flesh);

	target.draw(equipW);
	for (short i{}; i != weapons.size(); i++)
	{
		if(weapons.at(i)->isAvailable())
			target.draw(wNames.at(i));
	}
}
