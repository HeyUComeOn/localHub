#include "LuaEngine.h"
#include <string>
#include <iostream>
USING_NS_CC;
/*
	1.在lua与C/C++语言或者C/C++语言通信过程中，实际上更多的时候就是对栈顶的元素进行操作
	2.从栈顶往下看索引应该是-1，-2，-3
	3.从栈底网上看索引应该是1，2，3
	4.无论lua调用C/C++还是C/C++调用lua，参数值都是最先被压人栈顶的，最后结果值才被压人栈顶
*/

/*
1.在windows下用FileUtils::getInstance()->fullPathForFilename无法输出my.lua中的print的结果
这个在D:Lua/test中可以打印，那个是一个控制台程序

2.由于可能不是控制台程序的原因吧，
3.还未搞懂lua栈这个东西


*/
LuaEngine* LuaEngine::i= NULL;

LuaEngine::LuaEngine()
{

}

LuaEngine::~LuaEngine()
{
	if(m_pluaState)
	{
		lua_close(m_pluaState);
		m_pluaState=NULL;
	}

}

LuaEngine* LuaEngine::getInstance(){
	if (!i)
	{
		i = new LuaEngine;
		i->init();
	}
	return i;
}

static int l_show(lua_State* L)
{
	lua_pushstring(L, "String from C/C++");

	return 1;
}
void LuaEngine::init()
{
	//创建一个lua状态的指针
	m_pluaState=luaL_newstate();
	luaL_openlibs(m_pluaState);
	
	lua_pushcfunction(m_pluaState, l_show);//这两步，是为lua调用服务的
	lua_setglobal(m_pluaState, "show");
}

//访问变量
void LuaEngine::readVariable()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("my.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	log("%d,isExit",isExit);

	//int vvv=luaL_dofile(m_pluaState,"my.lua");//这在win32下能用，但是为了跨平台的需要，必须用FileUtils
	int vvv=luaL_dofile(m_pluaState,path.c_str());
	log("zhan:%d",lua_gettop(m_pluaState));
	int err_rlt=lua_pcall(m_pluaState,0,0,-1);
	CCASSERT(err_rlt!=-1,"lua_pcall return -1");
	
	//读一次处理一次
	lua_getglobal(m_pluaState,"username");//把全局变量 "username" 里的值压入堆栈
	const char* rlt1=lua_tostring(m_pluaState,-1);
	log("rlt1 is :%s", rlt1);	
	lua_pop(m_pluaState,1);

	lua_getglobal(m_pluaState,"num");
	int rlt2=lua_tonumber(m_pluaState,-1);
	log("rlt2 is :%d", rlt2);	
	lua_pop(m_pluaState,1);

	lua_getglobal(m_pluaState,"bu");
	int rlt3=lua_toboolean(m_pluaState,-1);
	log("rlt3 is :%d", rlt3);	
	lua_pop(m_pluaState,1);
	
	
}

void LuaEngine::loadFunction()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("my.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	log("%d,isExit",isExit);

	int vvv=luaL_dofile(m_pluaState,path.c_str());
	log("zhan:%d",lua_gettop(m_pluaState));
	int err_rlt=lua_pcall(m_pluaState,0,0,-1);
	CCASSERT(err_rlt!=-1,"read failed。");

	lua_getglobal(m_pluaState,"getrlt");//执行完此步，函数在栈顶
	lua_pushnumber(m_pluaState,12 );//执行完此步，12在栈顶，函数在第二个位置（-2的位置）
	lua_pushnumber(m_pluaState,26 );
	err_rlt= lua_pcall(m_pluaState,2,2,-1);//执行完此步，返回值在栈顶,两个参数，两个返回值

	CCASSERT(err_rlt!=-1,"sorry,read failed.");

	int n_rlt1 =lua_tonumber(m_pluaState,-1);
	int n_rlt2 =lua_tonumber(m_pluaState,-2);
	log("the return num is %d",n_rlt1);
	log("the return num is %d",n_rlt2);
}