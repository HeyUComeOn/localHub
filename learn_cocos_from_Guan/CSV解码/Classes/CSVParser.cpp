#include "CSVParser.h"

USING_NS_CC;

CSVParser::CSVParser(void)
{
}


CSVParser::~CSVParser(void)
{
}

__Array*CSVParser::parse(const char*filename)
{
	auto fileutils	= FileUtils::getInstance();
	auto path		= fileutils->fullPathForFilename(filename);
	auto content	= fileutils->getStringFromFile(path);
	auto contentStr	= __String::create(content);
	//��ȡ�ļ�¼����
	auto rows		= contentStr->componentsSeparatedByString("\n");
	//���ظ���ʾ�������
	__Array* ret	= __Array::createWithCapacity(rows->count());
	Ref*obj=nullptr;
	CCARRAY_FOREACH(rows,obj)
	{
		//���磺1,2012/12/23, ����8�㵽��˾,x_mitsui
		auto row	= static_cast<__String*>(obj);

		//ÿһ��fields������4������
		__Array* fields	= row->componentsSeparatedByString(",");
		ret->addObject(fields);

	}
	return ret;

}