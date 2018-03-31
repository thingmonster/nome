#pragma once
#include <SFML/Graphics/Text.hpp>
#include <memory>  
#include <ecm.h>

using namespace sf;
using namespace std;

class TextComponent : public Component {
		
	public:
		TextComponent() = delete;
		explicit TextComponent(Entity* p, const std::string& str = "", const std::string& font = "");
		~TextComponent() override = default;
		
		sf::Text getText() const;
		void SetText(const std::string& str);
		void SetPosition(Vector2f pos);
		void setCharacterSize(float size);
		void setColor(sf::Color colour);
		
		void update(double dt) override;
		void render() override;

	protected:
		std::shared_ptr<sf::Font> _font;
		std::string _string;
		sf::Text _text;
};