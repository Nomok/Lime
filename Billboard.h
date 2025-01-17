#pragma once

#include "irrlicht.h"
#include "IrrManagers.h"
#include "Material.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "LuaLime.h"

class Billboard
{
public:
	irr::scene::IBillboardSceneNode* bb;
	irr::video::SMaterial myMaterial;

	Billboard() {
		bb = smgr->addBillboardSceneNode();
	}
	Billboard(const Billboard& other) {
		bb = smgr->addBillboardSceneNode();
		bb = other.bb;
		myMaterial = other.myMaterial;
		bb->getMaterial(0) = other.myMaterial;
	}
	Billboard(const Material& material) {
		bb = smgr->addBillboardSceneNode();
		loadMaterial(material);
	}

	Vector3D getPosition() {
		return Vector3D(bb->getPosition().X, bb->getPosition().Y, bb->getPosition().Z);
	}

	void setPosition(const Vector3D& pos) {
		bb->setPosition(irr::core::vector3df(pos.x, pos.y, pos.z));
	}

	Vector2D getSize() {
		return Vector2D(bb->getSize().Width, bb->getSize().Height);
	}

	void setSize(const Vector2D& size) {
		bb->setSize(irr::core::vector2df(size.x, size.y));
	}

	bool loadMaterial(const Material& material) {
		myMaterial = material.mat;
		bb->getMaterial(0) = myMaterial;
		return true;
	}

	Vector3D getRotLock() {
		return Vector3D(bb->getRotLock().X, bb->getRotLock().Y, bb->getRotLock().Z);
	}

	void setRotLock(const Vector3D& rot) {
		bb->setRotLock(irr::core::vector3d<bool>(rot.x, rot.y, rot.z));
	}

	irr::f32 getYPivot() {
		return bb->getPivotY();
	}

	void setYPivot(float y) {
		bb->setPivotY(y);
	}

	void destroy() {
		if (bb)
			bb->remove();
	}
};

void bindBillboard() {
	sol::usertype<Billboard> bind_type = lua->new_usertype<Billboard>("Billboard",
		sol::constructors<Billboard(), Billboard(const Billboard& other), Billboard(const Material& material)>(),

		"position", sol::property(&Billboard::getPosition, &Billboard::setPosition),
		"size", sol::property(&Billboard::getSize, &Billboard::setSize),
		"yPivot", sol::property(&Billboard::getYPivot, &Billboard::setYPivot),
		"lockAxis", sol::property(&Billboard::getRotLock, &Billboard::setRotLock)
	);

	bind_type["loadMaterial"] = &Billboard::loadMaterial;
	bind_type["destroy"] = &Billboard::destroy;
}