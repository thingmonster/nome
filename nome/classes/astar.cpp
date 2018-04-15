
#include "astar.h"
#include "levelsystem.h"
#include <array>
#include <queue>

using namespace std;
using namespace sf;

/*

functional but no opportunity to put it to use as yet

*/

class Node {
	
	private:
		Vector2i _pos;
		int _level;
		int _priority;
		
	public:
		Node() = default;
		Node(const Vector2i& pos, int level, int priority) : _pos(pos), _level(level), _priority(priority) {}
		
		const Vector2i& getPos() const {
			return _pos;
		}
		
		int getLevel() const {
			return _level;
		}
		
		int getPriority() const {
			return _priority;
		}
		
		unsigned int estimate(const Vector2i& dest) const {
			Vector2i delta = dest - _pos;
			return static_cast<unsigned int>(length(delta));
		}
		
		void updatePriority(const Vector2i& dest) {
			_priority = _level + estimate(dest) * 10;
		}
		
		void nextLevel() {
			_level += 10;
		}
		
		bool operator<(const Node& other) const {
			return _priority > other._priority;
		}
};


vector<Vector2i> pathFind(Vector2i start, Vector2i finish) {
	
	static std::array<sf::Vector2i, 4> directions = {
		Vector2i(1,0),Vector2i(0,1),Vector2i(-1,0),Vector2i(0,-1)
	};
	
	vector<vector<bool>> closed_nodes_map(ls::getWidth());	
	vector<vector<int>> open_nodes_map(ls::getWidth());	
	vector<vector<Vector2i>> directions_map(ls::getWidth());
	priority_queue<Node> queue[2];	
	size_t queue_index = 0;
	
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getHeight(); ++x) {
			closed_nodes_map[x].push_back(false);
			open_nodes_map[x].push_back(0);
			directions_map[x].push_back(Vector2i(0,0));
		}		
	}

	Node n0(start,0,0);
	n0.updatePriority(finish);
	queue[queue_index].push(n0);
	open_nodes_map[start.x][start.y] = n0.getPriority();
	
	while (!queue[queue_index].empty()) {
		auto tmp = queue[queue_index].top();
		n0 = Node(tmp.getPos(), tmp.getLevel(), tmp.getPriority());
		auto pos = n0.getPos();
		queue[queue_index].pop();
		open_nodes_map[pos.x][pos.y] = 0;
		closed_nodes_map[pos.x][pos.y] = true;
		
		if (pos == finish) {
			vector<Vector2i> path;
			while (!(pos == start)) {
				auto dir = directions_map[pos.x][pos.y];
				path.push_back(pos);
				pos += dir;
			}
			
			reverse(begin(path), end(path));
			
			return path;
		}
		
		for (auto& dir : directions) {
			auto next = pos + dir;
			if (!(
				next.x < 0 || 
				next.x > ls::getWidth() || 
				next.y < 0 ||  
				next.y > ls::getHeight() ||
				ls::getTile(Vector2ul(next.x, next.y)) == ls::WALL ||
				closed_nodes_map[next.x][next.y]
			)) {
				Node m0(next, n0.getLevel(), n0.getPriority());
				m0.nextLevel();
				m0.updatePriority(finish);
				
				if (open_nodes_map[next.x][next.y] == 0) {
					open_nodes_map[next.x][next.y] = m0.getPriority();
					queue[queue_index].push(m0);
					directions_map[next.x][next.y] = dir * -1;
				} else if (open_nodes_map[next.x][next.y] > m0.getPriority()) {
					open_nodes_map[next.x][next.y] = m0.getPriority();
					directions_map[next.x][next.y] = dir * -1;
					while (queue[queue_index].top().getPos() != next) {
						queue[1 - queue_index].push(queue[queue_index].top());
						queue[queue_index].pop();
					}
					queue[queue_index].pop();
					if (queue[queue_index].size() > queue[1 - queue_index].size()) {
						queue_index = 1 - queue_index;
					}
					while (!queue[queue_index].empty()) {
						queue[1 - queue_index].push(queue[queue_index].top());
						queue[queue_index].pop();
					}
					queue_index = 1 - queue_index;
					queue[queue_index].push(m0);
				}
			}
		}
	}
	return vector<Vector2i>();
}












