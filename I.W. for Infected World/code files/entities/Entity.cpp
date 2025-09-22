// ===========================
// Author: Allosker
// --
// File Name: Entity.cpp
// --
// Description: This class acts as the very foundation of any entity of the game, from the simple shadows to the most complex monsters. 
// It manages all three most basic ressources that define an in - game entity :
// 
// A sprite and its textures.
// A sound and its buffers.
// A text and its strings(alongside the different fonts it can carry).
//
// The text is mainly here to later add 'nametags' or other features.
// However, it is not guaranteed that it will remain as it.
// ===========================



#include "Entity.h"


// Class -- Entity
/* ----------------------------------------------------------------------------- */ 


// Constructors



	Entity::Entity(const EntityInit& Einit)
		: textureW{ Einit.pathsTextures },
		sprite{ textureW.getTexture(0,0,0) },
		vecSoundBuffer{ converterSoundBuffers(Einit.pathsSounds) },
		sound{ vecSoundBuffer.at(0).at(0) },
		vecFonts{ std::move(converterFonts(Einit.pathsFonts)) },
		text{ vecFonts.at(0) }
	{
	}

	Vector<Font> Entity::converterFonts(const Vector<SystemPath>& pathsFonts)
	{
		Vector<Font> fonts;

		for (auto& pf : pathsFonts)
		{
			fonts.push_back(std::move(Font{ pf }));
		}
		return fonts;
	}

	Vector<Vector<SoundBuffer>> Entity::converterSoundBuffers(const Vector<Vector<SystemPath>>& pathsSoundBuffers)
	{
		Vector<Vector<SoundBuffer>> soundBuffs;

		size_t i{ 0 };
		for (auto& psb : pathsSoundBuffers)
		{
			soundBuffs.resize(pathsSoundBuffers.at(i).size());
			for (auto& path : psb)
			{
				soundBuffs.at(i).push_back(std::move(SoundBuffer{ path }));
			}
			i++;
		}
		return soundBuffs;
	}


// Getters



	// Textures Functions


		const Sprite& Entity::getSprite() const noexcept 
		{
			return sprite;
		}

		const Texture& Entity::getCurrentTexture() const noexcept
		{
			return sprite.getTexture();
		}

		TextureWrapper& Entity::getTextureWrapper() noexcept
		{
			return textureW;
		}

		const TextureWrapper& Entity::getTextureWrapper() const noexcept
		{
			return textureW;
		}

		const Vec3i& Entity::getCurrentIndexTextures() const noexcept
		{
			return currentIndexT;
		}

		const Vec2f& Entity::getOrigin() const noexcept
		{
			return sprite.getOrigin();
		}


	// Sound Functions


		const Sound& Entity::getSound() const noexcept
		{
			return sound;
		}

		Vector<Vector<SoundBuffer>>& Entity::getSoundBufferWrapper() noexcept
		{
			return vecSoundBuffer;
		}

		const Vector<Vector<SoundBuffer>>& Entity::getSoundBufferWrapper() const noexcept
		{
			return vecSoundBuffer;
		}

		const Vec2i& Entity::getCurrentIndexSounds() const noexcept
		{
			return currentIndexS;
		}


	// Text functions


		const Text& Entity::getText() const noexcept
		{
			return text;
		}

		Vector<Font>& Entity::getFontWrapper() noexcept
		{
			return vecFonts;
		}

		const Vector<Font>& Entity::getFontWrapper() const noexcept
		{
			return vecFonts;
		}

		const size_t& Entity::getCurrentIndexFonts() const noexcept
		{
			return currentIndexF;
		}

		const size_t& Entity::getCurrentIndexStrings() const noexcept
		{
			return currentIndexN;
		}


// Setters


	
	// Textures Functions


	void Entity::setTexture(size_t objectType, size_t animationType, size_t direction, bool resetRect)
		{
			sprite.setTexture(textureW.getTexture(objectType, animationType, direction), resetRect);
			currentIndexT.x = objectType;
			currentIndexT.y = animationType;
			currentIndexT.z = direction;
		}

	void Entity::nextTexture()
	{
		sprite.setTexture(textureW.getTexture(currentIndexT.x, currentIndexT.y, currentIndexT.z));
		currentIndexT.z = (currentIndexT.z + 1) % textureW.size(currentIndexT.x, currentIndexT.y);
	}

	void Entity::chooseTexture(size_t objectType, size_t animationType, size_t direction)
	{
		sprite.setTexture(textureW.getTexture(objectType, animationType, direction));
	}


	void Entity::draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(sprite);
	}


	// Sound Functions


	void Entity::setSound(size_t soundIndex, size_t soundIndex2)
	{
		if (soundIndex >= vecSoundBuffer.size())
			throw std::out_of_range{ "Index out of range in Entity, method setIndexSound()" };
		currentIndexS.x = soundIndex;
		currentIndexS.y = soundIndex2;
		sound.setBuffer(vecSoundBuffer.at(currentIndexS.x).at(currentIndexS.y));
	}

	void Entity::chooseIndexSound()
	{
		sound.setBuffer(vecSoundBuffer.at(currentIndexS.x).at(currentIndexS.y));
	}

	void Entity::chooseSound(size_t soundIndex, size_t soundIndex2)
	{
		sound.setBuffer(vecSoundBuffer.at(soundIndex).at(soundIndex2));
		currentIndexS.x = soundIndex;
		currentIndexS.y = soundIndex2;
	}
	

	void Entity::playSound()
	{
		sound.play();
	}

	void Entity::pauseSound()
	{
		sound.pause();
	}

	void Entity::stopSound()
	{
		sound.stop();
	}

	void Entity::setLoop(bool b)
	{
		sound.setLooping(b);
	}


	void Entity::setMinimumDistance(float miniDist)
	{
		if (miniDist <= 0)
			miniDist = 1;
		sound.setMinDistance(miniDist);
	}

	void Entity::setAttenuation(float att)
	{
		if (att <= -1)
			att = 0;
		sound.setAttenuation(att);
	}

	
	// Text Functions
	
		
		// Fonts

		void Entity::setFont(size_t textIndex)
		{
			if (textIndex >= vecFonts.size())
				throw std::out_of_range{ "Index out of range in Entity, method setIndexText()" };
			currentIndexF = textIndex;
			text.setFont(vecFonts.at(currentIndexF));
		}

		void Entity::chooseIndexFont()
		{
			text.setFont(vecFonts.at(currentIndexF));
		}

		void Entity::chooseFont(size_t textIndex)
		{
			text.setFont(vecFonts.at(textIndex));
		}

		
	void Entity::setString(size_t stringIndex)
	{
		if (stringIndex >= vecStrings.size())
			throw std::out_of_range{ "Index out of range in Entity, method setIndexString()" };
		currentIndexN = stringIndex; 
		text.setString(vecStrings.at(currentIndexN));
	}

	void Entity::nextString()
	{
		text.setString(vecStrings.at(currentIndexN));
		currentIndexN = (currentIndexN + 1) % vecStrings.size();
	}

	void Entity::chooseString(size_t stringIndex)
	{
		text.setString(vecStrings.at(stringIndex));
	}

	
	void Entity::editCurrentString(String&& newString)
	{
		vecStrings.at(currentIndexN) = newString;
	}

	void Entity::addString(String&& newString)
	{
		vecStrings.push_back(newString);
	}

	void Entity::editString(String&& newString, size_t stringIndex)
	{
		vecStrings.at(stringIndex) = newString;
	}


// Position



	void Entity::setDebug(bool b) noexcept
	{
		debug_ = b;
	}


		// Text 


		void Entity::nametagText(float offset)
		{
		}

		void Entity::setTextOriginCenter()
		{
			text.setOrigin({ text.getLocalBounds().size.x / 2, text.getLocalBounds().size.y / 2 });
		}

		void Entity::setTextOrigin(const Vec2f& newOrigin)
		{
			text.setOrigin(newOrigin);
		}

		void Entity::setTextScale(const Vec2f& newScale)
		{
			text.setScale(newScale); 
		}

		void Entity::setTextColor(const Color& newColor)
		{
			text.setFillColor(newColor);
		}

		void Entity::setTextStyle(const sf::Text::Style& style)
		{
			text.setStyle(style);
		}


		// Sprite


		void Entity::setOrigin(const Vec2f& newOrigin) noexcept
		{
			sprite.setOrigin(newOrigin);
		}

		void Entity::setOriginCenter()
		{
			sprite.setOrigin({ static_cast<float>(sprite.getTexture().getSize().x / 2), static_cast<float>(sprite.getTexture().getSize().x / 2) });
		}

		void Entity::setOriginCornerLeft()
		{
			sprite.setOrigin({ 0,0 });
		}