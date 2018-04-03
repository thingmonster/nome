#pragma once
#include "ecm.h"
#include <unordered_map>
#include <string>
#include "../classes/steering.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_shape.h"


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
	
	public:
		SeekState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player)
			: _steering(owner.get(), player.get(), 50.0f) {}
		void execute(Entity*, double) noexcept override;
};

class FleeState : public State {
	
	private:
		FleeSteering _steering;
	
	public:
		FleeState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player)
			: _steering(owner.get(), player.get(), 50.0f) {}
		void execute(Entity*, double) noexcept override;
};

