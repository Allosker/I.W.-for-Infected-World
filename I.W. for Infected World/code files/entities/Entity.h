#ifndef ENTITY_H
#define ENTITY_H
// ===========================
// Author: Allosker
// --
// File Name: Entity.h
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


#include "memory Utils/VectorTextureWrapper.h"


#include "umbrella headers/memory.h" 
#include "umbrella headers/sfml.h" 



struct EntityInit
{
	EntityInit(const Vector<Vector<Vector<SystemPath>>>& pathsText,
		const Vector<Vector<SystemPath>>& pathsSo, 
		const Vector<SystemPath>& pathsFo)
		: pathsTextures{pathsText},
		pathsSounds{pathsSo},
		pathsFonts{pathsFo}
	{}

	const Vector<Vector<Vector<SystemPath>>>& pathsTextures;

	const Vector<Vector<SystemPath>>& pathsSounds;

	const Vector<SystemPath>& pathsFonts;
};

// Entity acts as the very foundation of any entity of the game, from the simple shadows to the most complex monsters.
class Entity : public sf::Drawable
{
public:
// Concstructor & destructor



	Entity(const EntityInit& Einit);


	Entity(Entity&&) noexcept = default;

	Entity& operator=(Entity&&) noexcept = default;

	Entity(Entity&) = delete;

	Entity operator=(Entity&) = delete;


	virtual ~Entity() = default;


	Vector<Font> converterFonts(const Vector<SystemPath>& pathsFonts);

	Vector<Vector<SoundBuffer>> converterSoundBuffers(const Vector<Vector<SystemPath>>& pathsSoundBuffers);


// Getters



	// Textures

	const Sprite& getSprite() const noexcept;

	const Texture& getCurrentTexture() const noexcept;

	TextureWrapper& getTextureWrapper() noexcept;

	const TextureWrapper& getTextureWrapper() const noexcept;

	const Vec3i& getCurrentIndexTextures() const noexcept;

	const Vec2f& getOrigin() const noexcept;


	// Sounds

	const Sound& getSound() const noexcept;

	Vector<Vector<SoundBuffer>>& getSoundBufferWrapper() noexcept;

	const Vector<Vector<SoundBuffer>>& getSoundBufferWrapper() const noexcept;

	const Vec2i& getCurrentIndexSounds() const noexcept; 


	// Texts

	const Text& getText() const noexcept;

	Vector<Font>& getFontWrapper() noexcept;

	const Vector<Font>& getFontWrapper() const noexcept;

	const size_t& getCurrentIndexFonts() const noexcept;

	const size_t& getCurrentIndexStrings() const noexcept;


// Setters



	// Textures Functions

	void setTexture(size_t objectType = 0, size_t animationType = 0, size_t direction = 0, bool resetRect = true);

	void nextTexture();
	  
	void chooseTexture(size_t objectType = 0, size_t animationType = 0, size_t direction = 0);


	void draw(RenderTarget& target, RenderStates states) const override;


	// Sound Functions

	void setSound(size_t soundIndex = 0, size_t soundIndex2 = 0);

	void chooseIndexSound();
	
	void chooseSound(size_t soundIndex = 0, size_t soundIndex2 = 0);


	void playSound();

	void pauseSound();

	void stopSound();

	void setLoop(bool b);


	void setMinimumDistance(float miniDist);

	void setAttenuation(float att);
	

	// Text Functions

	
	// Fonts

		void chooseIndexFont();

		void chooseFont(size_t fontIndex);

		void setFont(size_t textIndex);


	void setString(size_t stringIndex);

	void nextString();

	void chooseString(size_t stringIndex);


	void editCurrentString(String&& newString);

	void addString(String&& newString);

	void editString(String&& newString, size_t stringIndex);



// Practical Functions



	void setDebug(bool b) noexcept;


	// Text
		

		// TODO: implement the logic to make the text float upon the sprite
		void nametagText(float offset = 0);

		void setTextOriginCenter();

		void setTextOrigin(const Vec2f& newOrigin);

		void setTextScale(const Vec2f& newScale);

		void setTextColor(const Color& newColor);

		void setTextStyle(const sf::Text::Style& style);


	// Sprite


		void setOrigin(const Vec2f& newOrigin) noexcept;

		void setOriginCenter();

		void setOriginCornerLeft();



protected:
// memebers
	


		// Textures
		TextureWrapper textureW;

		Sprite sprite;

		Vec3i currentIndexT{ 0, 0, 0 };


		// Sounds
		Vector<Vector<SoundBuffer>> vecSoundBuffer;

		Sound sound;

		Vec2i currentIndexS{ 0, 0 };


		// Fonts 
		Vector<Font> vecFonts;

		Text text;

		size_t currentIndexF{ 0 };


		// Strings 
		Vector<String> vecStrings;

		size_t currentIndexN{ 0 };


		bool debug_{ false };
};
#endif // ENTITY_H