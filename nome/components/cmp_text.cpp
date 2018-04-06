#include "cmp_text.h"
#include <system_resources.h>
#include <system_renderer.h>
#include <SFML/Graphics.hpp>
#include <memory>

TextComponent::TextComponent(Entity* const p, const std::string& str, const std::string& font)
 : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>(font);
  _text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}

sf::Text TextComponent::getText() const {
	return _text;
}

void TextComponent::setColor(sf::Color colour) {
  _text.setColor(colour);
}

void TextComponent::SetPosition(Vector2f pos) {
  _text.setPosition(pos);
}

void TextComponent::setCharacterSize(float size) {
  _text.setCharacterSize(size);
}

void TextComponent::setOrigin(float x, float y) {
  _text.setOrigin(x,y);
}

void TextComponent::setString(std::string s) {
	_text.setString(s);
}

void TextComponent::update(double dt) {
}

void TextComponent::render() {
	if (_parent->getVisible()) {
		Renderer::queue(&_text);
	}
}
