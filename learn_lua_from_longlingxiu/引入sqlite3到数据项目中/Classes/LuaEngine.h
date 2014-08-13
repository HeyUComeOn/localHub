//
//  LuaEngine.h
//  testforLuaCallCpp
//
//  Created by Mitsui on 14-8-12.
//
//

#ifndef __testforLuaCallCpp__LuaEngine__
#define __testforLuaCallCpp__LuaEngine__
#include "lua.hpp"
class LuaEngine{
public:
    LuaEngine();
    ~LuaEngine();
    
    static LuaEngine* getInstance();
private:
    void init();
    static LuaEngine* i;
    lua_State* m_pLuaState;
};

#endif /* defined(__testforLuaCallCpp__LuaEngine__) */
