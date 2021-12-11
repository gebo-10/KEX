#pragma once
#include"../component.h"
namespace kengine {
	enum class CameraType {
		ORTHO,
		PERSPECTIVE,
	};
	class Camera :public Component {
	public:
		CameraType type = CameraType::PERSPECTIVE;
		//int width = 100;
		//int height = 100;

		Rectf view_rect;
		float fov = 60.f;
		float znear = 0.1f;
		float zfar = 1000.f;

		mat4 projection{ 1.f };
		bool dirty = true;

		Color clear_color;

		int event_id;
		Camera() :Component(ComponentType::CAMERA) {
			set_view_rect(0, 0, 1, 1);
			Env.event_setvice.listen(EventType::OnViewSize, [this](Event* e) {
				//OnViewSize* event = (OnViewSize*)e;
				//width = event->width;
				//height = event->height;
				dirty = true;
			});
		}
		~Camera() {
			Env.event_setvice.unlisten(EventType::OnViewSize, event_id);
		}

		mat4 get_p() {
			if (dirty) {
				update_matrix();
			}
			return projection;
		}

		Rectf get_view_port() {
			return view_rect;//Rect(view_rect.x * width, view_rect.y * height, view_rect.w * width, view_rect.h * height);
		}

		void update_matrix() {
			float aspect = (view_rect.w * Screen::width)/ (view_rect.h * Screen::height);
			if (type == CameraType::ORTHO) {
				projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, znear, zfar);
			}
			else {
				projection = glm::perspective(glm::radians(fov), aspect, znear, zfar);
			}
			dirty = false;
		}

		void set_fov(float fov) {
			this->fov = fov;
			dirty = true;
		}

		void set_view_rect(float x, float y, float w, float h) {
			view_rect.x = x;
			view_rect.y = y;
			view_rect.w = w;
			view_rect.h = h;
			dirty = true;
		}

		void set_type(CameraType type) {
			this->type = type;
			dirty = true;
		}

		void set_near(float in_near) {
			this->znear = in_near;
			dirty = true;
		}

		void set_far(float in_far) {
			this->zfar = in_far;
			dirty = true;
		}

		void set_clear_color(Color color) {
			clear_color = color;
		}
	};
	typedef shared_ptr<Camera> CameraPtr;
}