#include "LuaLime.h"

#include "Vector2D.h"
#include "Vector3D.h"
#include "Billboard.h"
#include "Camera3D.h"
#include "Material.h"
#include "StaticMesh.h"
#include "Texture.h"
#include "Warden.h"

#include <sol/sol.hpp>
#include <sstream>

int LuaLime::initLua(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver) {
	lua = new sol::state(); // maybe change heap alloc
	lua->open_libraries(sol::lib::base, sol::lib::string, sol::lib::os, sol::lib::coroutine, sol::lib::jit, sol::lib::utf8, sol::lib::io, sol::lib::math, sol::lib::table, sol::lib::package);

	// do binds
	sol::table application = lua->create_named_table("Lime");
	sol::table world = lua->create_named_table("World");
	sol::table sound = lua->create_named_table("Sound");
	sol::table gui = lua->create_named_table("GUI");
	sol::table input = lua->create_named_table("Input");

	// warden
	bindWarden(application, world, sound, gui, input);

	// objs
	bindVector2D();
	bindVector3D();
	bindBillboard();
	bindCamera3D();
	bindMaterial();
	bindStaticMesh();
	bindTexture();

	return 0;
}