#include "cocos2d.h"
#include "sqlite3.h"
#include "MyUtility.h"


class NoteDAO
{
public:
	NoteDAO();
	~NoteDAO();

	//插入Note函数
	static int create(std::string pData, std::string pContent);

	//删除Note函数
	static int remove(std::string pData);

	//修改Note函数
	static int modify(std::string pData, std::string pContent);

	//查询所有数据函数
	static cocos2d::ValueVector findAll();

	//按照主键查询数据函数
	static cocos2d::ValueMap findById(std::string pDate);

	//获取数据库文件路径
	static std::string dbDirectoryFile();

	//数据库初始化
	static int initDB();
private:
	
};

