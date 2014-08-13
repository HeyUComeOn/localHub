#include "cocos2d.h"
class CSVParser
{
public:
	CSVParser(void);
	~CSVParser(void);
	static cocos2d::__Array*parse(const char*filename);
};

