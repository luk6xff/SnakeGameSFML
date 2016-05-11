#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Audio.hpp>




template <typename Resource, typename Identifier= int>
class ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager & operator =(const ResourceManager&) = delete;
	ResourceManager() = default;


	template<typename ... Args>
	void load(const Identifier& id, Args&& ... args);

	Resource& get(const Identifier& id)const;

private:
	std::unordered_map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};


template<typename Identifier>
class ResourceManager<sf::Music, Identifier> //partial specialization for sf::Music
{
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	ResourceManager() = default;

	template<typename ... Args>
	void load(const Identifier& id, Args&& ... args);

	sf::Music& get(const Identifier& id)const;

private:
	std::unordered_map<Identifier, std::unique_ptr<sf::Music>> mResourceMap;
};

//definitions
template <typename Resource, typename Identifier = int>
template<typename ... Args>
void ResourceManager<Resource, Identifier>::load(const Identifier& id, Args&& ...args)
{

	std::unique_ptr<Resource, Identifier> ptr(new Resource);
	if (not ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("Cannot load the file");
	mResourceMap.emplace(id, std::move(ptr));
}


template<typename RESOURCE, typename IDENTIFIER>
RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id)const
{
	return *mResourceMap.at(id);
}


template<typename Identifier>
template<typename ... Args>
void ResourceManager<sf::Music, Identifier>::load(const Identifier& id, Args&& ... args)
{
	std::unique_ptr<sf::Music> ptr(new sf::Music);

	if (not ptr->openFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("Impossible to load file");
	mResourceMap.emplace(id, std::move(ptr));
};

template<typename Identifier>
sf::Music& ResourceManager<sf::Music, Identifier>::get(const Identifier& id) const
{
	return *mResourceMap.at(id);
}