#include "NoteDAO.h"

USING_NS_CC;
using namespace std;

NoteDAO::NoteDAO()
{
}

NoteDAO::~NoteDAO()
{
}

//获取数据库文件路径
string NoteDAO::dbDirectoryFile()
{
	string writablePath =FileUtils::getInstance()->getWritablePath();
	string fullPath = writablePath+"NotesList.sqlite3";//任何后缀名皆可以

	return fullPath;
}

//数据库初始化
int NoteDAO::initDB()
{
	sqlite3* db;
	string path =dbDirectoryFile();
	/*bool isExist =FileUtils::getInstance()->isFileExist(path);
	if(!isExist)
	{
	log("The NotesList.sqlite3 doesn't exist.");
	return -1;
	}*/


	if(sqlite3_open(path.c_str(),&db)!=SQLITE_OK)
	{
		sqlite3_close(db);
		CCASSERT(false,"DB open failure.");
	}
	else
	{
		char*err;
		string sql = "create table if not exists Note (cdate text primary key,content text)";//这一步格式很重要
		if(sqlite3_exec(db,sql.c_str(),NULL,NULL,&err)!=SQLITE_OK)
		{
			sqlite3_close(db);
			CCASSERT(false,"Create table failure.");
		}
		sqlite3_close(db);
	}

	return 0;
}

//插入Note函数
int NoteDAO::create(string pDate, string pContent)
{
	initDB();
	sqlite3 *db=NULL;
	ValueMap dict;

	string path = dbDirectoryFile();

	if(sqlite3_open(path.c_str(),&db)!=SQLITE_OK)
	{
		sqlite3_close(db);
		CCASSERT(false,"DB open failure.");
	}
	else
	{
		string sql = "insert into Note (cdate,content) values (?,?)";//这一步格式很重要
		sqlite3_stmt * statement;
		if(sqlite3_prepare_v2(db,sql.c_str(),-1,&statement,NULL)==SQLITE_OK)
		{
			sqlite3_bind_text(statement,1,pDate.c_str(),-1,NULL);
			sqlite3_bind_text(statement,2,pContent.c_str(),-1,NULL);

			if (sqlite3_step(statement)!=SQLITE_DONE)//重复插入会进入
			{
				sqlite3_finalize(statement);
				sqlite3_close(db);
				CCASSERT(false,"Insert data failure.");
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return 0;
}

//删除Note函数
int NoteDAO::remove(string pDate)
{
	initDB();
	sqlite3 *db=NULL;
	ValueMap dict;

	string path = dbDirectoryFile();

	if(sqlite3_open(path.c_str(),&db)!=SQLITE_OK)
	{
		sqlite3_close(db);
		CCASSERT(false,"DB open failure.");
	}
	else
	{
		
		string sql = "delete from Note where cdate=?";//这一步格式很重要
		sqlite3_stmt * statement;
		if(sqlite3_prepare_v2(db,sql.c_str(),-1,&statement,NULL)==SQLITE_OK)
		{
			sqlite3_bind_text(statement,1,pDate.c_str(),-1,NULL);

			if (sqlite3_step(statement)!=SQLITE_DONE)
			{
				sqlite3_finalize(statement);
				sqlite3_close(db);
				CCASSERT(false,"Remove data failure.");
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return 0;
}

//修改Note函数
int NoteDAO::modify(string pDate, string pContent)
{
	initDB();
	sqlite3 *db=NULL;
	ValueMap dict;

	string path = dbDirectoryFile();

	if(sqlite3_open(path.c_str(),&db)!=SQLITE_OK)
	{
		sqlite3_close(db);
		CCASSERT(false,"DB open failure.");
	}
	else
	{
		string sql = "update Note set content=? where cdate=?";//主键不修改，作为条件
		sqlite3_stmt * statement;
		if(sqlite3_prepare_v2(db,sql.c_str(),-1,&statement,NULL)==SQLITE_OK)
		{
			sqlite3_bind_text(statement,1,pContent.c_str(),-1,NULL);
			sqlite3_bind_text(statement,2,pDate.c_str(),-1,NULL);

			if (sqlite3_step(statement)!=SQLITE_DONE)
			{
				sqlite3_finalize(statement);
				sqlite3_close(db);
				CCASSERT(false,"Update data failure.");
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return 0;
}

//查询所有数据函数
ValueVector NoteDAO::findAll()
{
	initDB();
	sqlite3 *db=NULL;

	ValueVector listData;

	string path = dbDirectoryFile();

	if(sqlite3_open(path.c_str(),&db)!=SQLITE_OK)
	{
		sqlite3_close(db);
		CCASSERT(false,"DB open failure.");
		return ValueVector(0);
	}
	else
	{
		string sql = "select cdate,content from Note ";//这一步格式很重要
		//语句对象，负责将数据库发出指令SQL指令，
		sqlite3_stmt * statement;
		//预处理过程
		if(sqlite3_prepare_v2(db,sql.c_str(),-1,&statement,NULL)==SQLITE_OK)
		{
			 
			//执行
			while (sqlite3_step(statement)==SQLITE_ROW)
			{
				ValueMap dict;
				char*cdate =(char*)sqlite3_column_text(statement,0);//此处0代表第一个
				char*content =(char*)sqlite3_column_text(statement,1);//整数就_int、等等

				dict["date"] = Value(cdate);
				dict["content"] = Value(content);

				listData.push_back(Value(dict));
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
		return listData;
	}
}
//按照主键查询数据函数
ValueMap NoteDAO::findById(string pDate)
{
	initDB(); 
	sqlite3 *db=NULL;
	ValueMap dict;

	string path = dbDirectoryFile();

	if(sqlite3_open(path.c_str(),&db)!=SQLITE_OK)
	{
		sqlite3_close(db);
		CCASSERT(false,"DB open failure.");
	}
	else
	{
		
		string sql = "select cdate,content from Note where cdate = ?";//这一步格式很重要
		//语句对象，负责向数据库发送指令
		sqlite3_stmt * statement;
		//预处理过程
		if(sqlite3_prepare_v2(db,sql.c_str(),-1,&statement,NULL)==SQLITE_OK)
		{
			sqlite3_bind_text(statement,1,pDate.c_str(),-1,NULL);
			if (sqlite3_step(statement)==SQLITE_ROW)
			{
				char*cdate =(char*)sqlite3_column_text(statement,0);
				char*content =(char*)sqlite3_column_text(statement,1);

				dict["date"] = Value(cdate);
				dict["content"] = Value(content);
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}

	return dict;
}
