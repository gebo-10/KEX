#pragma once
#include <kengine/core/base/base.h>
#include"../asset_common.h"
namespace kengine {
	struct AssetItem {
		PathID id;
		AssetType type;
		int offset;
		int size;
		BufferPtr buffer;
		AssetPtr assets;
	};
}