#pragma once
#include <vector>
#include "Resources.h"

struct Inventory
{
	std::vector<Resource> m_Resources;
	const int m_MaxSizeInventory = 10;
	
};

