//
//  LuaEngine.cpp
//  testforLuaCallCpp
//
//  Created by Mitsui on 14-8-12.
//
//

#include "LuaEngine.h"
#include "string"
#include "cocos2d.h"
USING_NS_CC;
#if __cplusplus
extern "C" {
#endif
    #include "lsqlite/lsqlite3.h"
    
    static luaL_Reg mylibs[]={
    
        {"lsqlite3",luaopen_lsqlite3},
        {NULL,NULL}
    };
#if __cplusplus
}
#endif
LuaEngine* LuaEngine::i = nullptr;

LuaEngine::LuaEngine()
{
    
}

LuaEngine::~LuaEngine()
{
    if(m_pLuaState)
    {
        lua_close(m_pLuaState);
        m_pLuaState=nullptr;
    }
}

void LuaEngine::init()
{
    m_pLuaState=luaL_newstate();
    luaL_openlibs(m_pLuaState);
    
    luaL_Reg*libs = mylibs;
    
    lua_getglobal(m_pLuaState, "package");
    lua_getfield(m_pLuaState, -1, "preload");
    
    for (; libs->func; libs++) {
        lua_pushcfunction(m_pLuaState, libs->func);
        lua_setfield(m_pLuaState, -2, libs->name);
    }
    
    lua_pop(m_pLuaState, -2);//µ¯³öpackage.preload
    std::string path=FileUtils::getInstance()->fullPathForFilename("my.lua");
    
    luaL_dofile(m_pLuaState, path.c_str());
        
}

LuaEngine* LuaEngine::getInstance()
{
    if(!i)
    {
        i=new LuaEngine;
        i->init();
    }
    return i;
}

