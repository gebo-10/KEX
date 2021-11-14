#pragma once
#include "../base/base.h"

#include <mio.h>
namespace kengine
{
	typedef mio::mmap_source MapFile;
	typedef shared_ptr<MapFile> MapFilePtr;
}
