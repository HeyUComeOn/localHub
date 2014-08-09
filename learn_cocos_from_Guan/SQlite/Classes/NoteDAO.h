#include "cocos2d.h"
#include "sqlite3.h"
#include "MyUtility.h"


class NoteDAO
{
public:
	NoteDAO();
	~NoteDAO();

	//����Note����
	static int create(std::string pData, std::string pContent);

	//ɾ��Note����
	static int remove(std::string pData);

	//�޸�Note����
	static int modify(std::string pData, std::string pContent);

	//��ѯ�������ݺ���
	static cocos2d::ValueVector findAll();

	//����������ѯ���ݺ���
	static cocos2d::ValueMap findById(std::string pDate);

	//��ȡ���ݿ��ļ�·��
	static std::string dbDirectoryFile();

	//���ݿ��ʼ��
	static int initDB();
private:
	
};

