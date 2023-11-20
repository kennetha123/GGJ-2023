#pragma once
#include "Components.h"

class Collision : public Component
{
public:
	bool is_collide = false;
	bool is_interactable = false;
};