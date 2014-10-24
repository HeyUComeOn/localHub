#include "LuaEngine.h"
#include <string>
#include <iostream>
USING_NS_CC;
/*
	//字体：GB2312
	1.在lua与C/C++语言或者C/C++语言通信过程中，实际上更多的时候就是对栈顶的元素进行操作
	2.从栈顶往下看索引应该是-1，-2，-3
	3.从栈底网上看索引应该是1，2，3
	4.无论lua调用C/C++还是C/C++调用lua，参数值都是最先被压人栈顶的，最后返回值才被压人栈顶
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

//此函数用于lua调用
static int l_show(lua_State* L)
{
	lua_pushstring(L, "String from C/C++");

	return 1;
}
void LuaEngine::init()
{
	//创建一个lua状态的指针
	m_pluaState=luaL_newstate();
	//并打开所有系统提供的库
	luaL_openlibs(m_pluaState);
	
	std::string fullpath=FileUtils::getInstance()->fullPathForFilename("config.lua");
	luaL_dofile(m_pluaState,fullpath.c_str());
	lua_pcall(m_pluaState,0,0,-1);
}

//访问lua文件中变量
void LuaEngine::readVariable()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("my.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	log("%d,isExit",isExit);

	//int vvv=luaL_dofile(m_pluaState,"my.lua");////这在win32下能用，但是为了跨平台的需要，必须用FileUtils
	int vvv=luaL_dofile(m_pluaState,path.c_str());
	log("zhan:%d",lua_gettop(m_pluaState));
	int err_rlt=lua_pcall(m_pluaState,0,0,-1);
	CCASSERT(err_rlt!=-1,"lua_pcall return -1");
	
	//读一次处理一次，local变量是无法获取的
	lua_getglobal(m_pluaState,"username");//把全局变量 "username" 里的值压入栈顶
	if(lua_isstring(m_pluaState,-1))//功能是判断是否能转化成字符串,不是判断类型
	{
		const char* rlt1=lua_tostring(m_pluaState,-1);//对栈-1处的转换
		log("rlt1 is :%s", rlt1);
	}
	lua_pop(m_pluaState,1);//弹出栈顶值

	lua_getglobal(m_pluaState,"num");
	if(lua_isnumber(m_pluaState,-1))
	{
		int rlt2=lua_tonumber(m_pluaState,-1);
		log("rlt2 is :%d", rlt2);	
	}
	lua_pop(m_pluaState,1);

	lua_getglobal(m_pluaState,"bu");
	int rlt3=lua_toboolean(m_pluaState,-1);
	log("rlt3 is :%d", rlt3);	
	lua_pop(m_pluaState,1);
	
	
}

//访问lua文件中函数
void LuaEngine::loadFunction()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("my.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	log("%d,isExit",isExit);

	int vvv=luaL_dofile(m_pluaState,path.c_str());
	log("zhan:%d",lua_gettop(m_pluaState));
	int err_rlt=lua_pcall(m_pluaState,0,0,-1);
	CCASSERT(err_rlt!=-1,"call failed。");

	lua_getglobal(m_pluaState,"getrlt");//执行完此步，函数在栈顶
	//添加参数
	lua_pushnumber(m_pluaState,12 );//执行完此步，12在栈顶，函数在第二个位置（-2的位置）
	lua_pushstring(m_pluaState,"secondPara" );

	err_rlt= lua_pcall(m_pluaState,2,2,-1);//执行完此步，返回值在栈顶,中间两个参数代表getrlt函数含有两个参数，两个返回值，-1为错误返回值

	CCASSERT(err_rlt!=-1,"sorry,read failed.");

	std::string n_rlt1 =lua_tostring(m_pluaState,-1);
	int n_rlt2 =lua_tonumber(m_pluaState,-2);
	log("the return var1 is %s",n_rlt1.c_str());
	log("the return num2 is %d",n_rlt2);
}

const char*getFiled(lua_State*L, char*Key)
{
	const char* rlt = nullptr;
	const char* rlt2 = nullptr;

	lua_pushstring(L, Key);//推入键
	lua_gettable(L,-2);//以栈顶的字符串(key)为关键字，在栈索引位置( -2)的表(table)中查询该关键字的值(value)，然后将栈顶的key出栈，再将value压栈

	if(lua_isstring(L,-1))
	{
		rlt = lua_tostring(L,-1);//值自动返回到栈顶
		lua_pop(L,1);
		if(lua_istable(L,-1))
		{
			rlt2= lua_tostring(L,-1);
			log("xbxbxbxbxb===>%s",rlt2);
		}

		return rlt;
	}

	return "wrong";
}
//访问lua中的table
void LuaEngine::loadTable()
{
	lua_State*L=luaL_newstate();
	luaL_openlibs(L);
	std::string path = FileUtils::getInstance()->fullPathForFilename("configure.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	
	luaL_dofile(L,path.c_str());
	//启动 调用文件"configure.lua"
	lua_pcall(L,0,0,-1);

	lua_getglobal(L,"application");
	if(lua_istable(L,-1))
	{
		log("application is table");
		std::string width = getFiled(L,"width");
		std::string height = getFiled(L,"height");
		log("width is %s, height is %s .",width.c_str(),height.c_str());
		int mwidth = atoi(width.c_str());
		int mheight = atoi(height.c_str());
	}
}

int table_next(lua_State*L, int i, char **k, char **v)
{
	int nIndex = lua_gettop( L );//堆栈上的元素个数
	log("table_next==========>%d",nIndex);

	//从栈上弹出一个 key（键）， 然后把索引指定的表中 key-value（健值）对压入堆栈 （即指定 key 后面的下一 (next) 对）。
	//此处第一次即索引1指定的索引
	if (lua_next(L, i ) !=0)
	{
		*k = (char*)lua_tostring(L, -2);
		*v = (char*)lua_tostring(L, -1);
		lua_pop(L, 1);						//保留 'key' 做下一次迭代
		return 1;
	}
	else
		return 0;
}

void LuaEngine::loadAllTable()
{
	lua_State *L;
	char *k=nullptr;
	char *v=nullptr;

	std::string path = FileUtils::getInstance()->fullPathForFilename("configure.lua") ;

	L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L,path.c_str());
	lua_pcall(L,0,0,0);

	lua_getglobal(L,"hero");
	lua_pushnil(L);
	while (table_next(L,1,&k,&v)!= 0)
	{
		log("key is :%s ==== Value is %s",k,v);
	}

	lua_close(L);
}