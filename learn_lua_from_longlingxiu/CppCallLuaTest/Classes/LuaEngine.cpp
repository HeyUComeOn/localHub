#include "LuaEngine.h"
#include <string>
#include <iostream>
USING_NS_CC;
/*
	//���壺GB2312
	1.��lua��C/C++���Ի���C/C++����ͨ�Ź����У�ʵ���ϸ����ʱ����Ƕ�ջ����Ԫ�ؽ��в���
	2.��ջ�����¿�����Ӧ����-1��-2��-3
	3.��ջ�����Ͽ�����Ӧ����1��2��3
	4.����lua����C/C++����C/C++����lua������ֵ�������ȱ�ѹ��ջ���ģ���󷵻�ֵ�ű�ѹ��ջ��
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

//�˺�������lua����
static int l_show(lua_State* L)
{
	lua_pushstring(L, "String from C/C++");

	return 1;
}
void LuaEngine::init()
{
	//����һ��lua״̬��ָ��
	m_pluaState=luaL_newstate();
	//��������ϵͳ�ṩ�Ŀ�
	luaL_openlibs(m_pluaState);
	
	std::string fullpath=FileUtils::getInstance()->fullPathForFilename("config.lua");
	luaL_dofile(m_pluaState,fullpath.c_str());
	lua_pcall(m_pluaState,0,0,-1);
}

//����lua�ļ��б���
void LuaEngine::readVariable()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("my.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	log("%d,isExit",isExit);

	//int vvv=luaL_dofile(m_pluaState,"my.lua");////����win32�����ã�����Ϊ�˿�ƽ̨����Ҫ��������FileUtils
	int vvv=luaL_dofile(m_pluaState,path.c_str());
	log("zhan:%d",lua_gettop(m_pluaState));
	int err_rlt=lua_pcall(m_pluaState,0,0,-1);
	CCASSERT(err_rlt!=-1,"lua_pcall return -1");
	
	//��һ�δ���һ�Σ�local�������޷���ȡ��
	lua_getglobal(m_pluaState,"username");//��ȫ�ֱ��� "username" ���ֵѹ��ջ��
	if(lua_isstring(m_pluaState,-1))//�������ж��Ƿ���ת�����ַ���,�����ж�����
	{
		const char* rlt1=lua_tostring(m_pluaState,-1);//��ջ-1����ת��
		log("rlt1 is :%s", rlt1);
	}
	lua_pop(m_pluaState,1);//����ջ��ֵ

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

//����lua�ļ��к���
void LuaEngine::loadFunction()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("my.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	log("%d,isExit",isExit);

	int vvv=luaL_dofile(m_pluaState,path.c_str());
	log("zhan:%d",lua_gettop(m_pluaState));
	int err_rlt=lua_pcall(m_pluaState,0,0,-1);
	CCASSERT(err_rlt!=-1,"call failed��");

	lua_getglobal(m_pluaState,"getrlt");//ִ����˲���������ջ��
	//��Ӳ���
	lua_pushnumber(m_pluaState,12 );//ִ����˲���12��ջ���������ڵڶ���λ�ã�-2��λ�ã�
	lua_pushstring(m_pluaState,"secondPara" );

	err_rlt= lua_pcall(m_pluaState,2,2,-1);//ִ����˲�������ֵ��ջ��,�м�������������getrlt��������������������������ֵ��-1Ϊ���󷵻�ֵ

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

	lua_pushstring(L, Key);//�����
	lua_gettable(L,-2);//��ջ�����ַ���(key)Ϊ�ؼ��֣���ջ����λ��( -2)�ı�(table)�в�ѯ�ùؼ��ֵ�ֵ(value)��Ȼ��ջ����key��ջ���ٽ�valueѹջ

	if(lua_isstring(L,-1))
	{
		rlt = lua_tostring(L,-1);//ֵ�Զ����ص�ջ��
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
//����lua�е�table
void LuaEngine::loadTable()
{
	lua_State*L=luaL_newstate();
	luaL_openlibs(L);
	std::string path = FileUtils::getInstance()->fullPathForFilename("configure.lua");
	log("path:%s",path.c_str());
	bool isExit= FileUtils::getInstance()->isFileExist(path);
	
	luaL_dofile(L,path.c_str());
	//���� �����ļ�"configure.lua"
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
	int nIndex = lua_gettop( L );//��ջ�ϵ�Ԫ�ظ���
	log("table_next==========>%d",nIndex);

	//��ջ�ϵ���һ�� key�������� Ȼ�������ָ���ı��� key-value����ֵ����ѹ���ջ ����ָ�� key �������һ (next) �ԣ���
	//�˴���һ�μ�����1ָ��������
	if (lua_next(L, i ) !=0)
	{
		*k = (char*)lua_tostring(L, -2);
		*v = (char*)lua_tostring(L, -1);
		lua_pop(L, 1);						//���� 'key' ����һ�ε���
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