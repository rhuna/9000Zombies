#pragma once
#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <map>


class TextureHolder{
public:
	TextureHolder();
	static sf::Texture& getTexture(std::string const& filename);


private:
	std::map<std::string,sf::Texture> m_textures;

	static TextureHolder* m_s_Instance;

};



#endif // !TEXTUREHOLDER_H

