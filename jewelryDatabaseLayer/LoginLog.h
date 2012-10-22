#pragma once
#include "jewelrydatabaselayer_global.h"

class JEWELRYDATABASELAYER_EXPORT LoginLog
{
public:
	~LoginLog(void);
	static LoginLog& getInstance();
	bool insertNewItem(int staffID);

private:
	LoginLog(void);

private:
	static LoginLog* s_instance;
};
