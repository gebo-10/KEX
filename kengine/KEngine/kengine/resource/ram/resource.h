#pragma once
#include "../../core/base/base.h"
namespace kengine {
	class Resource
	{
	public:
		//enum class ResourceType
		//{
		//	UNKNOW,
		//	TEXTURE,
		//	RENDER_TARGET,
		//	SHADER,
		//	MATERIAL,
		//	MODEL,
		//};
		//ResourceType resource_type;
		bool dirty=true;
		Resource(){}
		virtual ~Resource(){}
		virtual void clone(){}
	};
	typedef shared_ptr<Resource> ResourcePtr;
}
