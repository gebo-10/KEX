#pragma once
#include <unordered_map>
#include <kengine/core/base/base.h>
#include "asset.h"
#include "bundle/asset_bundle.h"
#include "loader/asset_loader.h"
namespace kengine
{
	class AssetsDatabase
	{
	public:
		//static AssetsDatabase & instance()
		//{
		//	static AssetsDatabase ad;
		//	return ad;
		//}
		//AssetLoader xxx;
		AssetsDatabase()
		{
			assets.clear();
			bundles.clear();
		}
		AssetPtr load_asset(string_view url) {}//根据url前缀判断位置和加载方式loader 根据后缀判断类型决定解析方式 不包含bundle

		AssetBundlePtr load_bundle(string_view url){
			auto bundle = std::make_shared<AssetBundle>(url);
			bundles[bundle->id] = bundle;
			return bundle;
		}
		void load_bundle(string_view url, std::function< void(AssetBundlePtr) >) {}
		void unload_bundle(AssetBundlePtr bundle) {}
		//void unload_bundle(string_view url) {}

		AssetPtr load_bundle_asset(AssetBundlePtr& bundle, PathID id) {
			auto asset = bundle->load_asset(id);
			assets[id] = asset;
			return asset;
		}
		std::vector<AssetPtr> load_all_bundle_asset(AssetBundlePtr& bundle) {
			auto as= bundle->load_all_asset();
			for (auto asset : as) {
				assets[asset->id] = asset;
			}
			return as;
		}

		void unload_bundlee_asset(AssetBundlePtr bundle, PathID id) {
			assets[id] = nullptr;
			bundle->unload_asset(id);
		}
		void unload_bundlee_asset(AssetBundlePtr bundle, AssetPtr asset) {
			unload_bundlee_asset(bundle, asset->id);
		}

		AssetPtr get_asset(PathID id){}
		void get_asset(PathID id, std::function< void(AssetPtr) >) {}


		template<typename R>
		shared_ptr<R> get_resource(PathID id) {
			auto itr = assets.find(id);
			if (itr == assets.end()) {
				return nullptr;
			}
			return std::dynamic_pointer_cast<R>(itr->second->default_resource);
		}

		template<typename R>
		shared_ptr<R> instaniate_resource(PathID id) {
			auto itr = assets.find(id);
			if (itr == assets.end()) {
				return nullptr;
			}
			return std::dynamic_pointer_cast<R>(itr->second->default_resource->clone());
		}

		bool add(AssetPtr& asset) {
			PathID id = asset->id;
			auto itr = assets.find(id);
			if (itr == assets.end()) {
				error("add same asset");
				return false;
			}
			itr->second = asset;
			return true;
		}
	private:
		std::unordered_map<PathID, AssetPtr> assets;
		std::unordered_map<UID, AssetBundlePtr> bundles;
	};
}
