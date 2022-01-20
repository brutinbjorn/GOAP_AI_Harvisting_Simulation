#pragma once
#include <string>
#include <vector>
#include "Resources.h"

struct Inventory
{
	std::vector<Resource> m_Resources;
	const int m_MaxSizeInventory = 10;
	std::string ToolType = "";
	int m_ToolHealth = 0;
};

