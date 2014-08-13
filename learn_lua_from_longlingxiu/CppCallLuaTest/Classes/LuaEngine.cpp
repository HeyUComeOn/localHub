#include "LuaEngine.h"
#include <string>
#include <iostream>
USING_NS_CC;

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
    //创建一个新的状态，每次读取新的文件都要创建一个新的状态
	m_pluaState=luaL_newstate();
    //并打开所有系统提供的库
	luaL_openlibs(m_pluaState);
    
    //完整路径
    std::string fullPath=FileUtils::getInstance()->fullPathForFilename("config.lua");
    //读取文件
    luaL_dofile(m_pluaState, fullPath.c_str());
    //启动调用文件
    lua_pcall(m_pluaState, 0, 0, -1);
	
	lua_pushcfunction(m_pluaState, l_show);
	lua_setglobal(m_pluaState, "show");
}

void LuaEngine::configWindowsContentSize(int*pWidth ,int*pHeight)
{
    //调用lua中变量和函数(当然lua中函数也是变量)时，第一步
    lua_getglobal(m_pluaState, "width");
    //判断是否可以转换为数字类型，若可以则转换，不是判断是否为数字类型
    if(lua_isnumber(m_pluaState, -1))
    {
        int width=(int)lua_tonumber(m_pluaState, -1);
        log("width is :%d",width);
        *pWidth=width;
    }
    
    lua_getglobal(m_pluaState, "height");
    if(lua_isnumber(m_pluaState, -1))
    {
        int height =(int)lua_tonumber(m_pluaState, -1);
        log("height is %d",height);
        *pHeight=height;
    }

    //判断是否可以转换为数字类型，若可以则转换，不是判断是否为数字类型,比如可以尝试将name赋值为18来检测
    lua_getglobal(m_pluaState, "name");
    if(lua_isstring(m_pluaState, -1))
    {
        char* name =(char*)lua_tostring(m_pluaState, -1);
        log("name is %s",name);
        //*pHeight=height;
    }
}



/*
 读取调用lua中的函数
 */
void LuaEngine::callLuaFunction()
{
/*******************************************************/
    //1.此处init已经读取了文件，不用再次读取
    //2.准备调用函数test01
	lua_getglobal(m_pluaState,"test01");

    //3.调用函数test01，此处几个参数，几个结果一定要写对
    int err_rlt01=lua_pcall(m_pluaState, 0, 0, -1);
	CCASSERT(err_rlt01!=-1,"对不起，调用函数失败！");

/*******************************************************/
    lua_getglobal(m_pluaState,"test02");
    
    //压参数顺序和lua函数中参数顺序一样
    lua_pushnumber(m_pluaState, 20);
    lua_pushstring(m_pluaState,"has gotten the key." );
    
    int err_rlt02=lua_pcall(m_pluaState, 2, 0, -1);
	CCASSERT(err_rlt02!=-1,"对不起，调用函数失败！");
    
/*******************************************************/
    lua_getglobal(m_pluaState,"test03");
    
    int err_rlt03=lua_pcall(m_pluaState, 0, 2, -1);
    CCASSERT(err_rlt03!=-1,"对不起，调用函数失败！");


    char* rlt1 =(char*)lua_tostring(m_pluaState, -1);
    char* rlt2 =(char*)lua_tostring(m_pluaState, -2);
    log("%s",rlt1);//从结果可以看出，先把第一个返回值压入栈
    log("%s",rlt2);

}

/*
 lua_next() 这个函数的工作过程是：
 1) 先从栈顶弹出一个 key
 2) 从栈指定位置的 table 里取下一对 key-value，先将 key 入栈再将 value 入栈
 3) 如果第 2 步成功则返回非 0 值，否则返回 0，并且不向栈中压入任何值
 
 第 2 步中从 table 里取出所谓“下一对 key-value”是相对于第 1 步中弹出的 key 的。table 里第一对 key-value 的前面没有数据，所以先用 lua_pushnil() 压入一个 nil 充当初始 key。
 
 注意开始的时候先用 lua_gettop() 取了一下 table 在栈中的正索引（前面说过了，在进行这个 lua_next() 过程之前先将 table 入栈，所以栈大小就是 table 的正索引），后面的 lua_next() 过程中不断的有元素出入栈，所以使用正索引来定位 table 比较方便。
 
 到了 table 中已经没有 key-value 对时，lua_next() 先弹出最后一个 key，然后发现已经没有数据了会返回 0，while 循环结束。所以这个 lua_next() 过程结束以后 table 就又位于栈顶了。
 */
int table_next(lua_State *L,int i,char**k,char **v)
{
    if(lua_next(L , i )!=0)
    {
        // 现在栈顶（-1）是 value，-2 位置是对应的 key
        *k = (char*)lua_tostring(L , -2);
        *v = (char*)lua_tostring(L , -1);
        lua_pop(L , 1);//弹出 value，让 key 留在栈顶
        return 1;
    }
    else
        return 0;

}

//第二种遍历table的方式
void test()
{
    lua_State *L;
    int t_idx;
    char *k=NULL;
    char *v=NULL;
    
    std::string path=FileUtils::getInstance()->fullPathForFilename("configTab.lua");
    
    L=luaL_newstate();
    luaL_openlibs(L );
    luaL_dofile(L , path.c_str());
    lua_pcall(L , 0, 0, -1);
    
    lua_getglobal(L , "testtable");
    t_idx=lua_gettop(L );//返回栈顶元素的索引,即当前table所在的位置
    lua_pushnil(L );
    while (table_next(L , t_idx, &k, &v)!=0) {
        fprintf(stderr, "the key is %s=====the value is %s\n",k,v);
    }
    
    lua_close(L );
    L =NULL;
}

//第一种遍历table的方式
const char* getfiled(lua_State* L ,const char* key )
{
    char *rlt=NULL;
    lua_pushstring(L , key);
    //lua_gettable的作用就是以栈顶的值作为key来访问-2位置上的table
    lua_gettable(L , -2);//与test_read_table结合来看
    if (lua_isstring(L , -1)) {
        rlt =(char*)lua_tostring(L , -1);
        //把栈顶的值移出栈，保证栈顶是table以便遍历。
        lua_pop(L , 1);
        return rlt;
    }
    return "wrong";
}

void LuaEngine::test_read_table()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    
    std::string fullPath=FileUtils::getInstance()->fullPathForFilename("configTab.lua");
    luaL_dofile(L , fullPath.c_str());
    lua_pcall(L, 0, 0, -1);
    
    lua_getglobal(L, "application");
    if (lua_istable(L, -1)) {
        log("application is a table.");
    }
    const char*width = getfiled(L , "width");
    const char*height= getfiled(L , "height");
    log("table's width is : %s",width);
    log("table's height is : %s",height);
    //int nWidth  =   atoi(width);
    //int nHeight =   atoi(height);
    
    test();
    lua_close(L);
    L= NULL;

}