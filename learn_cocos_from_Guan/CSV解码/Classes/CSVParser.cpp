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
	//截取的记录集合
	auto rows		= contentStr->componentsSeparatedByString("\n");
	//返回给表示层的数据
	__Array* ret	= __Array::createWithCapacity(rows->count());
	Ref*obj=nullptr;
	CCARRAY_FOREACH(rows,obj)
	{
		//例如：1,2012/12/23, 早上8点到公司,x_mitsui
		auto row	= static_cast<__String*>(obj);

		//每一个fields都包含4个数据
		__Array* fields	= row->componentsSeparatedByString(",");
		ret->addObject(fields);

	}
	return ret;

}