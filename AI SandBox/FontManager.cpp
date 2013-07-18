#include "FontManager.h"
#include <cassert>

void FontManager::Init()
{
	sf::Font font;
	font.loadFromFile("Graphic/Font/consola.ttf");  
	m_fonts.insert(std::pair<FontEnum, sf::Font>(FontEnum::Font_Consola, font));
}

void FontManager::Destroy()
{

}

const sf::Font* FontManager::GetFont(const FontEnum eFont) const
{
	FontMap::const_iterator font = m_fonts.find(eFont);
	assert( font != m_fonts.end() && "Fonts: GetFont < Font not found >" );

	return &font->second;
}
