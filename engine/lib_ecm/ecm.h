#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;



class Entity;
class Scene;



// ======================== ENTITY MANAGER ======================== //
	
struct EntityManager {
  std::vector<std::shared_ptr<Entity>> list;
  void update(double dt);
  void render();
  std::vector<std::shared_ptr<Entity>> find(const std::string& tag) const;
  std::vector<std::shared_ptr<Entity>>
  find(const std::vector<std::string>& tags) const;
};



// ======================== ENTITY ======================== //
	

class Entity {
	
	protected:
		sf::Vector2f _position;
		bool _fordeletion;
		
	public:
		Entity(Scene* s);
		~Entity() = default;
		Scene* const scene;
		void update(const double dt);
		void render();
		std::vector<std::shared_ptr<Component>> _components;
		
	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}

	template <typename T>
	const std::vector<std::shared_ptr<T>> getComponents() const {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (const auto c : _components) {
			if (typeid(*c) == typeid(T)) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return std::move(ret);
	}
	
	template <typename T>
	const std::vector<std::shared_ptr<T>> GetCompatibleComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (auto c : _components) {
			auto dd = dynamic_cast<T*>(&(*c));
			if (dd) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return ret;
	}
};
