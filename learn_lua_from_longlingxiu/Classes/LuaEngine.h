#ifndef __TestLuaplugin__LuaEngine__
#define __TestLuaplugin__LuaEngine__
#include "cocos2d.h"
#include "lua/lua.hpp"

class LuaEngine {
public:
	LuaEngine();
	~LuaEngine();
	static LuaEngine*getInstance();
	void readVariable();
	void loadFunction();
private:
	static LuaEngine* i;
	void init();
private:
	lua_State* m_pluaState;
};
#endif
