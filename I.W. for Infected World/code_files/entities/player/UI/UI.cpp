#include "UI.h"

#include <sstream>
#include <iomanip>

#include <iostream>

UI::UI(const SystemPath& fontPath, Vector<Weapon*>& _weapons, const Util::DisplayBar& bar)
	: font{ fontPath },
	life{ font, "Life", size },
	money{ font, "Money: ", size },
	flesh{ font, "Flesh count: ", size },
	equipW{ font, "Weapons:", size},
	weapons{ _weapons },
	cWeapon{weapons.at(0)},
	lifeBar{bar}
{
	wNames.push_back({ font, "handgun", size });
	wNames.push_back({ font, "rifle", size });
	wNames.push_back({ font, "shotgun", size });

	wNames.at(0).setFillColor(Color::Red);
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

View& UI::getView() noexcept
{
	viewPos = uiView.getCenter();
	return uiView;
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



void UI::update(Player& player) noexcept
{
	
	

	u_int f{ player.getFleshCount() };
	float m{ player.getMoneyCount() };


	std::ostringstream os;
	os << "Money: " << std::fixed << std::setprecision(2) << m;

	money.setString(os.str());

	flesh.setString("Flesh count: " + std::to_string(f));

	// Update & Resize player bar
	player.getLifeBar().setSize(Util::vec2_cast<float>(Vec2u{ getLifeSizeC().x * 2, getLifeSizeC().y / 2 }));
	player.getLifeBar().update(player.get(Traits::Life, Specifier::Current), player.get(Traits::Life, Specifier::Max), life.getPosition() + Util::vec2_cast<float>(Vec2u{getLifeSizeC().x / 2, getLifeSizeC().x / 7}), Util::vec2_cast<float>(player.getCurrentTexture().getSize()));



	if (viewPos != uiView.getCenter())
	{
		const Vec2f& pos{ uiView.getCenter() };
		const Vec2f& viewSize{ uiView.getSize() };

		Vec2f posT{ viewSize.x / 2, viewSize.y / 2 };

		life.setPosition(pos + -posT);

		money.setPosition(pos + Vec2f{ -posT.x , -(posT.y - getLifeSizeC().y * 2) });

		flesh.setPosition(pos + Vec2f{ -posT.x, -(posT.y - getLifeSizeC().y * 4) });


		equipW.setPosition(pos + Vec2f{ (posT.x - getEquipedSizeC().x * 2), -posT.y });


		// Set space between each weapon's name
		u_int temp{ getEquipedSizeC().y };
		for (short i{}; i != weapons.size(); i++)
		{
			wNames.at(i).setPosition(pos + Vec2f{ (posT.x - getEquipedSizeC().x), -(posT.y - temp) });

			if (weapons.at(i)->isAvailable())
			{
				temp += wNames.at(i).getCharacterSize();
			}
		}
	}
}


void UI::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(life);
	target.draw(money);
	target.draw(flesh);
	target.draw(lifeBar);

	target.draw(equipW);
	for (short i{}; i != weapons.size(); i++)
	{
		if(weapons.at(i)->isAvailable())
			target.draw(wNames.at(i));
	}
}
