#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include "lua.hpp"
#include "string"
USING_NS_CC;

AppDelegate::AppDelegate() {
    init_lua();
}

AppDelegate::~AppDelegate() 
{
    if(m_pLuaState)
    {
        lua_close(m_pLuaState);
        m_pLuaState = NULL;
    }
    
}


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

//编写一个函数供lua使用
static int l_getName(lua_State*L)
{
    lua_pushstring(L,"第一个函数");
    
    //一个返回值
    return 1;
}

static int l_showOnePara( lua_State* L)
{
    const char* value= luaL_checkstring(L , -1);//Checks whether the function argument (which at -1) is a string and returns this string
    lua_pushstring(L , value);
    
    // 一个返回值
    return 1;
}

static int l_showThreeParas( lua_State* L)
{
    const char* value1= luaL_checkstring(L , -1);//检查传进来的参数是否能转化为字符串
    const char* value2= luaL_checkstring(L , -2);
    const char* value3= luaL_checkstring(L , -3);
    
    
    log("value1 is %s:",value1);
    log("value2 is %s:",value2);
    log("value3 is %s:",value3);
    // 一个返回值
    return 0;
}

/*没有返回值的函数*/
static int l_showReturn0(lua_State* L)
{
    log( "I'm a function without returns.");
    return 0;
}

/*一个返回值的函数*/
static int l_showReturn1(lua_State* L)
{
    log( "I'm a function with one returns.");
    lua_pushstring(L,"I'm the only one");
    return 1;
}

/*俩个返回值的函数*/
static int l_showReturn2(lua_State* L)
{
    log( "I'm a function with two returns.");
    lua_pushstring(L,"I'm the first one");
    lua_pushstring(L,"I'm the second one");
    return 2;
}

/*返回一个table,利用for循环*/

static int l_showTable1(lua_State*L)
{
    lua_newtable(L);
    char str[20]={0};
    for(int i=1; i<=10;i++)
    {
        lua_pushnumber(L ,i);//压入key
        sprintf(str, "num is :%i",i);
        lua_pushstring(L, str);//压入value
        lua_settable(L, -3);//将位置－3前面的key和value都压入到table 中保存完之后再把这两个值弹出，然后table还是在栈顶
    }
    
    return 1;
}

/*返回另一个table，利用while循环*/
static int l_showTable2(lua_State*L)
{
    lua_newtable(L);
    char str[20]={0};
    int looper =1;
    while(looper <=10)
    {
        sprintf(str, "key is :%i",looper);
        lua_pushstring(L, str);//压入key
        lua_pushstring(L, "x_mitsui");//压入value
        looper++;
        lua_settable(L, -3);//将位置－3前面的key和value都压入到table 中保存完之后再把这两个值弹出，然后table还是在栈顶
    }
    
    return 1;
}

static void register_my_functions(lua_State*L)
{
    //推入栈中，再加上个名字
    lua_pushcfunction(L , l_getName);
    lua_setglobal(L , "getMyName");
    
    lua_pushcfunction(L , l_showOnePara);
    lua_setglobal(L , "showOnePara");
    
    lua_pushcfunction(L , l_showThreeParas);
    lua_setglobal(L , "showThreeParas");
    
    lua_pushcfunction(L ,l_showReturn0);
    lua_setglobal(L, "showReturn0");
    
    lua_pushcfunction(L ,l_showReturn1);
    lua_setglobal(L, "showReturn1");
    
    lua_pushcfunction(L ,l_showReturn2);
    lua_setglobal(L, "showReturn2");
    
    lua_pushcfunction(L ,l_showTable1);
    lua_setglobal(L, "showTable1");
    
    lua_pushcfunction(L ,l_showTable2);
    lua_setglobal(L, "showTable2");
}

void AppDelegate::init_lua()
{
    m_pLuaState=luaL_newstate();
    luaL_openlibs(m_pLuaState);
    
    register_my_functions(m_pLuaState);
    
    // 接下来运行这几个函数
    std::string path= FileUtils::getInstance()->fullPathForFilename("my.lua");
    luaL_dofile(m_pLuaState, path.c_str());
    lua_pcall(m_pLuaState, 0, 0, -1);
    
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
