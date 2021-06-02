#pragma once
#include "Entity.hpp"

class EntityData {
public:
	struct UnitData {

		std::string texname;
		int radius;

		UnitData(std::string str, int radius) : texname(str), radius(radius){}
	};

	struct BulletData {
		int speed;
		int dmg;
		std::string texname;
		std::string spezialattributs;

		BulletData(int speed, int dmg, std::string texname, std::string spezialattributs) : speed(speed), dmg(dmg), texname(texname), spezialattributs(spezialattributs){}
	};
private:
	
	static std::map<Entity::types, UnitData>& getUnit() {
		static std::map<Entity::types, UnitData>  unitlist;
		return unitlist;
	}

	static std::map<Entity::types, BulletData>& getBullet() {
		static std::map<Entity::types, BulletData>  bulletlist;
		return bulletlist;
	}

public:

	static UnitData* getUnitData(Entity::types etype) { 
		return &getUnit().at(etype); 
	}
	static void addUnitData(UnitData data, Entity::types type) {
		getUnit().insert(std::make_pair(type, data));
	}


	static BulletData* getBulletData(Entity::types etype) {
		if (getBullet().find(etype) != getBullet().end())
			return &getBullet().at(etype);
		else
			return nullptr;
	}
	static void addBulletData(BulletData data, Entity::types type) {
		getBullet().insert(std::make_pair(type, data));
	}
};