
#pragma once
#include "ecm.h"
#include "system_renderer.h"
#include <system_resources.h>

class ShapeComponent : public Component {
	
	protected:
		std::shared_ptr<sf::Shape> _shape;
		std::shared_ptr<sf::Texture> _texture;
	
	public:
		ShapeComponent() = delete;
		explicit ShapeComponent(Entity *p);
		
		void update(double dt) override;
		void render() override;
		sf::Shape &getShape() const;
		void setTexture(std::shared_ptr<sf::Texture> t, sf::IntRect r);
		void setRotation(float);
		
		template <typename T, typename... Targs>
		void setShape(Targs... params) {
			_shape.reset(new T(params...));
		}
};








