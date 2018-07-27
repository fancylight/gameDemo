#pragma once
#include <string>
#include <ostream>

struct spriteData
{
	std::string className;
	int level;

	friend std::ostream& operator<<(std::ostream& os, const spriteData& obj)
	{
		return os
			<< "className: " << obj.className
			<< " level: " << obj.level;
	}
};
struct plistData
{
	std::string plist;
	std::string png;
	std::string spriteName[2];
	std::string spriteBack[2];

	friend std::ostream& operator<<(std::ostream& os, const plistData& obj)
	{
		return os
			<< "plist: " << obj.plist
			<< " png: " << obj.png;
	}
};