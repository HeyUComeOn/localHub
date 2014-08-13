#include "LuaEngine.h"
#include <string>
#include <iostream>
USING_NS_CC;
/*
	1.��lua��C/C++���Ի���C/C++����ͨ�Ź����У�ʵ���ϸ����ʱ����Ƕ�ջ����Ԫ�ؽ��в���
	2.��ջ�����¿�����Ӧ����-1��-2��-3
	3.��ջ�����Ͽ�����Ӧ����1��2��3
	4.����lua����C/C++����C/C++����lua������ֵ�������ȱ�ѹ��ջ���ģ������ֵ�ű�ѹ��ջ��
*/

/*
1.��windows����FileUtils::getInstance()->fullPathForFilename�޷����my.lua�е�print�Ľ��
�����D:Lua/test�п��Դ�ӡ���Ǹ���һ������̨����

2.���ڿ��ܲ��ǿ���̨�����ԭ��ɣ�
3.��δ�㶮luaջ�������


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
	//����һ��lua״̬��ָ��
	m_pluaState=luaL_newstate();
	luaL_openlibs(m_pluaState);
	
	lua_pushcfunction(m_pluaState, l_show);//����������Ϊlua���÷����
	lua_setglobal(m_pluaState, "show");
}

//���ʱ���
void LuaEngine::readVariable()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("my.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	log("%d,isExit",isExit);

	//int vvv=luaL_dofile(m_pluaState,"my.lua");//����win32�����ã�����Ϊ�˿�ƽ̨����Ҫ��������FileUtils
	int vvv=luaL_dofile(m_pluaState,path.c_str());
	log("zhan:%d",lua_gettop(m_pluaState));
	int err_rlt=lua_pcall(m_pluaState,0,0,-1);
	CCASSERT(err_rlt!=-1,"lua_pcall return -1");
	
	//��һ�δ���һ��
	lua_getglobal(m_pluaState,"username");//��ȫ�ֱ��� "username" ���ֵѹ���ջ
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
	CCASSERT(err_rlt!=-1,"read failed��");

	lua_getglobal(m_pluaState,"getrlt");//ִ����˲���������ջ��
	lua_pushnumber(m_pluaState,12 );//ִ����˲���12��ջ���������ڵڶ���λ�ã�-2��λ�ã�
	lua_pushnumber(m_pluaState,26 );
	err_rlt= lua_pcall(m_pluaState,2,2,-1);//ִ����˲�������ֵ��ջ��,������������������ֵ

	CCASSERT(err_rlt!=-1,"sorry,read failed.");

	int n_rlt1 =lua_tonumber(m_pluaState,-1);
	int n_rlt2 =lua_tonumber(m_pluaState,-2);
	log("the return num is %d",n_rlt1);
	log("the return num is %d",n_rlt2);
}