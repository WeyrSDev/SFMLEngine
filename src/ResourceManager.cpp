/* 
 * File:   ResourceManager.cpp
 * Author: iMer
 * 
 * Created on 3. Juli 2014, 14:47
 */

#include <iostream>

#include "ResourceManager.hpp"

namespace engine {

	ResourceManager::ResourceManager() {
		sf::Listener::setPosition(-1, -1, 0);
		// Create missing texture (pink, black checker pattern)
		sf::Image missing;
		missing.create(110, 110, sf::Color(255, 0, 220));
		bool checker = false;
		for (int x = 0; x < 11; x++) {
			for (int y = 0; y < 11; y++) {
				if (checker) {
					for (unsigned int x2 = 0; x2 < 10; x2++) {
						for (unsigned int y2 = 0; y2 < 10; y2++) {
							missing.setPixel(x * 10 + x2, y * 10 + y2, sf::Color(0, 0, 0));
						}
					}
				}
				checker = !checker;
			}
		}
		if (!m_textureMissing.loadFromImage(missing)) {
			std::cerr << "Couldn't loadFromImage missing texture" << std::endl;
		}
		m_textureMissing.setRepeated(true);
		m_textureMissing.setSmooth(false);
	}

	ResourceManager::~ResourceManager() {
		for (auto it = m_textures.begin(); it != m_textures.end(); it++) {
			delete it->second;
		}
		m_textures.clear();
		for (auto it = m_soundBuffers.begin(); it != m_soundBuffers.end(); it++) {
			delete it->second;
		}
		m_soundBuffers.clear();
	}

	sf::Texture* ResourceManager::GetTexture(std::string path) {
		auto it = m_textures.find(path);
		if (it != m_textures.end()) {
			return it->second;
		}
		sf::Texture* texture = new sf::Texture();
		if (texture->loadFromFile(path)) {
			m_textures.insert(std::make_pair(path, texture));
			return texture;
		}
		std::cerr << "Could not load texture from file (" << path << ")" << std::endl;
		// Couldn't load texture, clean up and return the missing one
		delete texture;
		// also insert it so we prevent trying to load each time it gets requested
		m_textures.insert(std::make_pair(path, &m_textureMissing));
		return &m_textureMissing;
	}

	sf::Sound* ResourceManager::MakeSound(std::string path) {
		auto it = m_soundBuffers.find(path);
		if (it != m_soundBuffers.end()) {
			return new sf::Sound(*it->second);
		}
		sf::SoundBuffer* sb = new sf::SoundBuffer();
		if (!sb->loadFromFile(path)) {
			return nullptr;
		}
		return new sf::Sound(*sb);
	}

}