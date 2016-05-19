#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory> //unique ptr
#include <stdexcept> //runtime_error
#include <utility> //forward




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

//partial template specialization for sf::Music
template<typename Identifier>
class ResourceManager<sf::Music, Identifier> 
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

	std::unique_ptr<Resource> ptr(new Resource);
	if (!ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("Cannot load the file");
	mResourceMap.emplace(id, std::move(ptr));
}


template<typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(const Identifier& id)const
{
	return *mResourceMap.at(id);
}


template<typename Identifier>
template<typename ... Args>
void ResourceManager<sf::Music, Identifier>::load(const Identifier& id, Args&& ... args)
{
	std::unique_ptr<sf::Music> ptr(new sf::Music);

	if (!ptr->openFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("Impossible to load file");
	mResourceMap.emplace(id, std::move(ptr));
};

template<typename Identifier>
sf::Music& ResourceManager<sf::Music, Identifier>::get(const Identifier& id) const
{
	return *mResourceMap.at(id);
}