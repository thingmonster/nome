#pragma once
#include <unordered_map>
#include <string>
#include "engine.h"
#include "cmp_state_machine.h"
#include "cmp_shape.h"
#include "cmp_movement.h"
#include "../classes/steering.h"

/* 

this file contains definitions for the State class, 
StateMachineComponent class and the individual classes
for each state

*/


class State {
			
	public:
		virtual ~State() = default;
		virtual void execute(Entity*, double) noexcept = 0;

};
 

class StateMachineComponent : public Component {
	
	private:
		std::unordered_map<std::string, std::shared_ptr<State>> _states;
		std::shared_ptr<State> _current_state;
		std::string _current_state_name = "";
		
	public:
		void update(double) override;
		void render() override {}
		explicit StateMachineComponent(Entity *p);
		StateMachineComponent() = delete;
		void addState(const std::string&, std::shared_ptr<State>) noexcept;
		std::shared_ptr<State> getState(const std::string&) const noexcept;
		void removeState(const std::string&) noexcept;
		void changeState(const std::string&) noexcept;
		const std::string& currentState() const {
			return _current_state_name;
		}
		
};


class StationaryState : public State {
	
	public:
		StationaryState() = default;
		void execute(Entity*, double) noexcept override;
};

class SeekState : public State {
	
	private:
		SeekSteering _steering;
		float _speed;
	
	public:
		SeekState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player, float speed)
			: _speed(speed), _steering(owner.get(), player.get(), ls::getTileSize()) {}
		void execute(Entity*, double) noexcept override;
};

class FleeState : public State {
	
	private:
		FleeSteering _steering;
		float _speed;
	
	public:
		FleeState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player, float speed)
			: _speed(speed), _steering(owner.get(), player.get(), ls::getTileSize()) {}
		void execute(Entity*, double) noexcept override;
};

class WanderState : public State {
	
	private:
		WanderSteering _steering;
		float _speed;
	
	public:
		WanderState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player, float speed)
			: _speed(speed), _steering(owner.get(), player.get(), ls::getTileSize()) {}
		void execute(Entity*, double) noexcept override;
};

