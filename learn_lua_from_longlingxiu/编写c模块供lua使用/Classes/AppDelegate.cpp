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

static void register_my_functions(lua_State*L)
{

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
