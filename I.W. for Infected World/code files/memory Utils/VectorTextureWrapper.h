#ifndef VECTOR_TEXTURE_WRAPPER_H
#define VECTOR_TEXTURE_WRAPPER_H

#include <vector>
#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"


class TextureWrapper
{
public:
	
	// Default constructor - no textures loaded
	TextureWrapper() = default;

	// Constructor that initializes the wrapper with specific sizes for animation types, object types, and direction frames
	TextureWrapper(std::size_t objectType_s, std::size_t animationType_s, std::size_t direction_s)
	{
		wrapper.resize(objectType_s);
		for (auto& animationType : wrapper)
		{
			animationType.resize(animationType_s);
			for (auto& direction : animationType)
			{
				direction.resize(direction_s);
			}
		}
	}

	// Constructor that initializes the wrapper with a vector of vectors of vectors of unique_ptrs to Texture
	TextureWrapper(std::vector<std::vector<std::vector<Texture>>>&& other)
	{
		for (size_t i{0}; i != other.size(); i++)
		{
			for (size_t j{0}; j != other.at(i).size(); j++)
			{
				for (size_t p{ 0 }; p != other.at(i).at(j).size(); p++)
				{
					wrapper.at(i).at(j).at(p) = std::make_unique<Texture>(other.at(i).at(j).at(p));
				}
			}
		}
	}



	// Constructor that initializes the wrapper with an initializer list of initializer lists of initializer lists of unique_ptrs to Texture
	TextureWrapper(const Vector<Vector<Vector<SystemPath>>>& init)
	{
		wrapper.resize(init.size());
		size_t i{ 0 };
		for (auto& oInit : init)
		{
			wrapper.at(i).resize(oInit.size());
			size_t j{ 0 };
			for(auto& oInitAn : oInit)
			{
				wrapper.at(i).at(j).resize(oInitAn.size());
				size_t p{ 0 };
				for (auto& path : oInitAn)
				{
					auto temp = std::make_unique<sf::Texture>();

					if (!temp->loadFromFile(path))
					{
						throw std::runtime_error{ "Could not open from file: " + path.string() };
					}
					wrapper.at(i).at(j).at(p) = std::move(temp);
					p++;
				}
				j++;
			}
			i++;
		}
	}

	// Move Constructor
	TextureWrapper(TextureWrapper&& other) noexcept
		: wrapper{std::move(other.wrapper)}
	{
	}

	// Move Assignment Operator
	TextureWrapper& operator=(TextureWrapper&& other) noexcept
	{
		if (this != &other)
		{
			wrapper = std::move(other.wrapper);
		}
		return *this;
	}

	// Disable copy constructor
	TextureWrapper(const TextureWrapper&) = delete;

	// Disable copy assignment operator
	TextureWrapper& operator=(const TextureWrapper&) = delete;


// Getters 


	// Function to get a texture from a specific object type, animation type
	// Accessed as: [objectType][animationType]
	Texture& getTexture(std::size_t objectType, std::size_t animationType, std::size_t direction)
	{
		return *wrapper.at(objectType).at(animationType).at(direction);
	}


	// Function to get the size of the wrapper
	std::size_t size() const
	{
		return wrapper.size();
	}

	// Function to get the size of a specific object type
	std::size_t size(std::size_t objectType) const
	{
		return wrapper.at(objectType).size();
	}


	// Function to get the size of a specific a,imationType
	std::size_t size(std::size_t objectType, std::size_t animationType) const
	{
		return wrapper.at(objectType).at(animationType).size();
	}

	// Checks if a specific texture exists
	bool thereExists(std::size_t objectType, std::size_t animationType, std::size_t direction)
	{
		if (typeid(wrapper.at(objectType).at(animationType).at(direction)) == typeid(Texture))
		{
			return true;
		}
		return false;
	}


// Setters


	// Function to add a specific texture
	void addFrame(std::size_t objectType, std::size_t animationType, std::size_t direction, Texture& texture)
	{
		wrapper.at(objectType).at(animationType).at(direction) = std::move(std::make_unique<Texture>(texture)); // Add the texture as a new frame
	}


private:

	// Wraps a unique_ptr to texture into two vectors so that for each object there is a vector of object types such as: running, standing, etc. And that for each of those types there is an animation type such as: down, up, right, left, etc
	// Accessed as: [objectType][animationType][direction]
	std::vector<std::vector<std::vector<std::unique_ptr<Texture>>>> wrapper;

};


#endif // VECTOR_TEXTURE_WRAPPER_H
