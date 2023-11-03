#include "Character.h"

class RandomNPC : public Character
{
public:
	RandomNPC(const std::string& image_path, const sf::Vector2i& sprite_size);
	~RandomNPC() = default;

	virtual void update(float dt) override;
	void handleMovement();
	void initKeyBindings();
	void initAnimation();

private:

	AnimationController controller;
	std::vector<std::vector<sf::IntRect>> frames_;
};