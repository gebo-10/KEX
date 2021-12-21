#pragma once
#include <sol.hpp>
#include <kengine/core/base/base.h>
#include <kengine/resource/ram/material.h>
#include <fstream>
#include <kengine/core/io/mmap.h>
namespace kengine {
	class MatGLSLImport
	{
	public:
		static MaterialPtr import(const string & filename) {
			sol::state lua;
			lua.open_libraries(sol::lib::base);
			lua.new_enum("ShaderDataType",
				"INT", ShaderDataType::INT,
				"UINT", ShaderDataType::UINT,
				"FLOAT", ShaderDataType::FLOAT,
				"VEC2", ShaderDataType::VEC2,
				"VEC3", ShaderDataType::VEC3,
				"VEC4", ShaderDataType::VEC4,
				"MAT2", ShaderDataType::MAT2,
				"MAT3", ShaderDataType::MAT3,
				"MAT4", ShaderDataType::MAT4,
				"Color", ShaderDataType::Color
				);
			MapFile file(filename);
			string text(file.data(), file.size());
			ShaderPtr shader = nullptr;
			string decl;
			auto compute_pos = text.find("#compute");
			if (compute_pos != text.npos) {
				auto decl_pos = text.find("#decl");
				auto compute = text.substr(compute_pos + 10, decl_pos - compute_pos - 10);
				decl = text.substr(decl_pos + 7);
				shader = std::make_shared<Shader>(compute);
			}
			else {
				auto vert_pos = text.find("#vert");
				auto frag_pos = text.find("#frag");
				auto decl_pos = text.find("#decl");

				auto vert = text.substr(vert_pos + 7, frag_pos - vert_pos - 7);
				auto frag = text.substr(frag_pos + 7, decl_pos - frag_pos - 7);
				decl = text.substr(decl_pos + 7);

				shader = std::make_shared<Shader>(vert, frag);
			}

			auto material = std::make_shared<Material>(shader);
			sol::table uniforms = lua.do_string(decl);
			for (auto item : uniforms)
			{
				sol::table uniform = item.second;
				int location = uniform["location"];
				int count = uniform.get_or("count", 1);
				//int count = uniform["count"];
				ShaderDataType type = uniform["type"];

				sol::table value = uniform["value"];
				int value_size = value.size();
				switch (type)
				{
				case ShaderDataType::FLOAT: {
					auto data = (float)value[1];
					material->add_uniform(location, type, &data);
					break;
				}
				case ShaderDataType::VEC2:
				case ShaderDataType::Color:
				case ShaderDataType::VEC3: 
				case ShaderDataType::VEC4:
				case ShaderDataType::MAT2:
				case ShaderDataType::MAT3:
				case ShaderDataType::MAT4: {
					std::vector<float> data;
					data.clear();
					data.reserve(value_size);
					for (int i = 0; i < value_size; i++) {
						data.push_back((float)value[i + 1]);
					}
					material->add_uniform(location, type, nullptr, count);
					material->set_uniform(location, data.data(), data.size() * sizeof(float));
					break;
				}
				default:
					break;
				}
			}

			return material;
		}

	};

}