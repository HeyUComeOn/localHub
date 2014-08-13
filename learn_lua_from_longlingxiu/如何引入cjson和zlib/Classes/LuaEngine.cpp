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
    #include"cjson/lua_cjson.h"
    #include "zlib/lua_zlib.h"
    
    static luaL_Reg mylibs[]={
    
        {"lsqlite3",luaopen_lsqlite3},
        {"zlib",luaopen_zlib},
        {"cjson",luaopen_cjson_safe},
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

/*
 编写供lua使用的c函数
 */

static int l_getFullPath(lua_State*L)
{
    
    std::string writePath= FileUtils::getInstance()->getWritablePath();
    lua_pushstring(L, writePath.c_str());
    return 1;
}
void LuaEngine::init()
{
    m_pLuaState=luaL_newstate();
    luaL_openlibs(m_pLuaState);
    
    luaL_Reg*libs = mylibs;
    
    lua_getglobal(m_pLuaState, "package");
    //table的设置方法
    lua_getfield(m_pLuaState, -1, "preload");
    
    for (; libs->func; libs++) {
        lua_pushcfunction(m_pLuaState, libs->func);
        lua_setfield(m_pLuaState, -2, libs->name);
    }
    
    lua_pop(m_pLuaState, -2);
    
    lua_pushcfunction(m_pLuaState,l_getFullPath);
    //普通函数的设置方法，与table设置有区别
    lua_setglobal(m_pLuaState, "getFullPath");
    
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

