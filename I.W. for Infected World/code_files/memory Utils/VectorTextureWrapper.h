#pragma once // VectorTextureWrapper.h


#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"


class TextureWrapper
{
public:
	
	
	TextureWrapper() = default;

	
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


	TextureWrapper(TextureWrapper&& other) noexcept
		: wrapper{std::move(other.wrapper)}
	{
	}


	TextureWrapper& operator=(TextureWrapper&& other) noexcept
	{
		if (this != &other)
		{
			wrapper = std::move(other.wrapper);
		}
		return *this;
	}

	
	TextureWrapper(const TextureWrapper&) = delete;


	TextureWrapper& operator=(const TextureWrapper&) = delete;


// Getters 


	Texture& getTexture(std::size_t objectType, std::size_t animationType, std::size_t direction)
	{
		return *wrapper.at(objectType).at(animationType).at(direction);
	}


	std::size_t size() const
	{
		return wrapper.size();
	}

	std::size_t size(std::size_t objectType) const
	{
		return wrapper.at(objectType).size();
	}


	std::size_t size(std::size_t objectType, std::size_t animationType) const
	{
		return wrapper.at(objectType).at(animationType).size();
	}

	bool thereExists(std::size_t objectType, std::size_t animationType, std::size_t direction)
	{
		if (typeid(wrapper.at(objectType).at(animationType).at(direction)) == typeid(Texture))
		{
			return true;
		}
		return false;
	}


// Setters


	void addFrame(std::size_t objectType, std::size_t animationType, std::size_t direction, Texture& texture)
	{
		wrapper.at(objectType).at(animationType).at(direction) = std::move(std::make_unique<Texture>(texture)); // Add the texture as a new frame
	}


private:


	std::vector<std::vector<std::vector<std::unique_ptr<Texture>>>> wrapper;

};