#pragma once
#include"../core/base/type.h"
#include "../kserialize/namedatabase_generated.h"
namespace kengine {
	class NameService
	{
	public:
		NameService()
		{
		}

		~NameService()
		{
		}

		void init(BufferPtr buffer) {
			kserialize::NameDatabaseT database;
			kserialize::GetNameDatabase(buffer->data)->UnPackTo(&database);
			for (auto name : database.names) {
				add(name->id, name->str);
			}
		}

		void add(uint32 id, const string& str) {
			name_to_id[str] = id;
		}

		uint32 get_id(const string& str) {
			auto itr = name_to_id.find(str);
			if (itr == name_to_id.end()) {
				return 0;
			}
			else {
				return itr->second;
			}
		}
	private:
		std::unordered_map<string, uint32> name_to_id;
	};

}