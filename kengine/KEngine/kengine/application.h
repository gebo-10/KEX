#pragma once
namespace kengine {
	class Application
	{
	public:
		Application()
		{
		}

		~Application()
		{

		}


		virtual void on_config() {

		}

		virtual void on_update() {

		}

		virtual void on_project_loaded()
		{

		}

		virtual void register_matedata()
		{
		}
	private:

	};


#define APP(NAME)\
Application * kengine::kengine_create_application() {\
	auto * app= new NAME; \
	return app; \
}

extern Application* kengine_create_application();
}
