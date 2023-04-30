#include <string>
#include <vector>

namespace attribute
{
	struct attributes
	{
		int health;
		int magic;
		int attack;
		int defense;
		int spatk;
		int spdef;
		int speed;
	};


	struct relation
	{
		std::vector<std::string> close_to;
		std::vector<std::string> hate_to;
	};

	struct skill
	{

	};

	struct equipment
	{

	};

	enum element
	{
		fire,
		water,
		thunder,
		earth,
		nature,
		light,
		dark,
		normal
	};

	enum debuff
	{
		dead,
		poison,
		burn,
		stun,
		paralyze,
		bleed,
		frozen
	};

	enum buff
	{
		regen,
		attribute_buff,
		terrain_buff,
		chemistry_buff,
		item_buff
	};

	enum job
	{
		warrior,
		assassin,
		mage,
		divinity
	};

	struct player
	{
		std::string name;
		std::string full_name;
		std::string description;
		attributes attribute_;
		relation relation_;
		job job_;
		skill skill_;
		equipment equipment_;
		element element_;
	};

	struct monster
	{
		std::string name;
		std::string description;
		attributes attribute_;
		skill skill_;
		element element_;
	};
}