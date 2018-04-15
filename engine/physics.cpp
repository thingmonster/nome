#include "physics.h"

/*

the contents of this file is largely taken from the 
platformer engine source code with two modifications 
in the initialise and invert_height methods

*/

namespace Physics {
	
	static shared_ptr<b2World> world;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;

	void initialise() {
		// top down so no gravity
		b2Vec2 gravity(0.0f, 0.0f);
		world.reset(new b2World(gravity));
	}


	void shutdown() { 
		world.reset(); 
	}

	void update(const double& dt) {
		world->Step((float)dt, velocityIterations, positionIterations);
	}

	std::shared_ptr<b2World> GetWorld() { 
		return world; 
	}

	const Vector2f bv2_to_sv2(const b2Vec2& in, bool scale) {
		if (scale) {
			return Vector2f((in.x * physics_scale), (in.y * physics_scale));
		} else {
			return Vector2f(in.x, in.y);
		}
	}

	const b2Vec2 sv2_to_bv2(const Vector2f& in, bool scale) {
		if (scale) {
			return b2Vec2((in.x * physics_scale_inv), (in.y * physics_scale_inv));
		} else {
			return b2Vec2(in.x, in.y);
		}
	}

	const Vector2f invert_height(const Vector2f& in) {
		// y axis determined by window size
		return Vector2f(in.x, Renderer::getWindow().getSize().y - in.y);
	}

}