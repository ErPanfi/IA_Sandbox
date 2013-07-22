//qui mancavano le guardie! Non si fa! ;-)
#ifndef SANDBOX_FONTMANAGER_H
#define SANDBOX_FONTMANAGER_H

#include <SFML/Graphics/Font.hpp>
#include <map>
#include "FontEnum.h"

class FontManager
{
public:
	static FontManager* Istance()
	{
		static FontManager istance;
		return &istance;
	}

	void			Init();
	void			Destroy();

	const sf::Font*		GetFont(const FontEnum eFont) const;

private:
	typedef std::map<FontEnum, sf::Font>	FontMap;
	FontMap m_fonts;

protected:
	FontManager(){}
	virtual ~FontManager(){}
	
	FontManager(const FontManager&);
	FontManager& operator=(const FontManager&);
};

#endif