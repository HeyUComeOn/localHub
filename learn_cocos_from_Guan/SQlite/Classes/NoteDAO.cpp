#include "NoteDAO.h"

USING_NS_CC;
using namespace std;

NoteDAO::NoteDAO()
{
}

NoteDAO::~NoteDAO()
{
}

//��ȡ���ݿ��ļ�·��
string NoteDAO::dbDirectoryFile()
{
	string writablePath =FileUtils::getInstance()->getWritablePath();
	string fullPath = writablePath+"NotesList.sqlite3";//�κκ�׺���Կ���

	return fullPath;
}

//���ݿ��ʼ��
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
		string sql = "create table if not exists Note (cdate text primary key,content text)";//��һ����ʽ����Ҫ
		if(sqlite3_exec(db,sql.c_str(),NULL,NULL,&err)!=SQLITE_OK)
		{
			sqlite3_close(db);
			CCASSERT(false,"Create table failure.");
		}
		sqlite3_close(db);
	}

	return 0;
}

//����Note����
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
		string sql = "insert into Note (cdate,content) values (?,?)";//��һ����ʽ����Ҫ
		sqlite3_stmt * statement;
		if(sqlite3_prepare_v2(db,sql.c_str(),-1,&statement,NULL)==SQLITE_OK)
		{
			sqlite3_bind_text(statement,1,pDate.c_str(),-1,NULL);
			sqlite3_bind_text(statement,2,pContent.c_str(),-1,NULL);

			if (sqlite3_step(statement)!=SQLITE_DONE)//�ظ���������
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

//ɾ��Note����
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
		
		string sql = "delete from Note where cdate=?";//��һ����ʽ����Ҫ
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

//�޸�Note����
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
		string sql = "update Note set content=? where cdate=?";//�������޸ģ���Ϊ����
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

//��ѯ�������ݺ���
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
		string sql = "select cdate,content from Note ";//��һ����ʽ����Ҫ
		//�����󣬸������ݿⷢ��ָ��SQLָ�
		sqlite3_stmt * statement;
		//Ԥ�������
		if(sqlite3_prepare_v2(db,sql.c_str(),-1,&statement,NULL)==SQLITE_OK)
		{
			 
			//ִ��
			while (sqlite3_step(statement)==SQLITE_ROW)
			{
				ValueMap dict;
				char*cdate =(char*)sqlite3_column_text(statement,0);//�˴�0�����һ��
				char*content =(char*)sqlite3_column_text(statement,1);//������_int���ȵ�

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
//����������ѯ���ݺ���
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
		
		string sql = "select cdate,content from Note where cdate = ?";//��һ����ʽ����Ҫ
		//�����󣬸��������ݿⷢ��ָ��
		sqlite3_stmt * statement;
		//Ԥ�������
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
