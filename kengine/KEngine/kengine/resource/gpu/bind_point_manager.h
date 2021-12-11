#pragma once
//#include "gpu_resource.h"
#include"gpu_object.h"
#include "gpu_texture.h"
namespace kengine {
	enum class BindPointType
	{
		VAO,
		Texture,
		SSBO,
		UBO,
		MAX,
	};

	//class BindPoint
	//{
	//public:
	//	bool ditry = true;
	//	GPUID gpu_id;
	//	BindPoint()
	//	{
	//	}

	//	~BindPoint()
	//	{
	//	}
	//	void set(GPUID id){
	//		if (id == gpu_id) return;
	//		gpu_id = id;
	//		ditry = true;
	//	}
	//	void clear() {
	//		if (gpu_id == -1)return;
	//		gpu_id = -1;
	//		ditry = true;
	//	}
	//};

	class BindPointManager
	{
	public:
		GPUID bind_points[(int)BindPointType::MAX][64];
		BindPointManager()
		{
		}

		~BindPointManager()
		{
		}

		void bind(BindPointType type, int point, GPUID id) {
			auto& gpu_id = bind_points[(int)type][point];
			if (id == gpu_id) {
				return;
			}
			else {
				gpu_id = id;
				switch (type)
				{
				case kengine::BindPointType::VAO:
					glBindVertexArray(gpu_id);
					//bind();
					break;
				case kengine::BindPointType::Texture:
					glActiveTexture(GL_TEXTURE0 + index);
					glBindTexture((GLenum)m_desc.type, gpu_id);
					//bind(point);
					break;
				case kengine::BindPointType::SSBO:
					glBindBufferBase((int)type, point, gpu_id);
					//bind_to_point(int binding_point)
					break;
				case kengine::BindPointType::UBO:
					glBindBufferBase((int)type, point, gpu_id);
					//bind_to_point(int binding_point)
					break;
				case kengine::BindPointType::MAX:
					break;
				default:
					break;
				}
			}

		}
	private:

	};

}