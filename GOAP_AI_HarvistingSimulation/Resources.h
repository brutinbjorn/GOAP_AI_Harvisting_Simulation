#pragma once
enum class ResourceType
{
	invalid = -1,

	wood	= 1,
	stone	= 2,
	coal	= 3,

	copper	= 4,
	iron	= 5
};


class Resource
{
public:
	Resource(ResourceType type) :m_resource(type) {};

private:
	ResourceType m_resource;
};

