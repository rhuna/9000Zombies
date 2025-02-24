#include "TextureHolder.h"
#include <assert.h>


TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
	std::cout << "textureholder created\n";
};
sf::Texture& TextureHolder::getTexture(std::string const& filename){
	//get a reference to m_textures using m_s_instance
	auto& m = m_s_Instance->m_textures;//auto here is used to create map<string,sf::texture>::iterator

	auto keyValuePair = m.find(filename);//auto here is used to create map<string,sf::texture>::iterator


	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}else{
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}


}