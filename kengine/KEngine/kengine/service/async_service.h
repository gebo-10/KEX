#pragma once
#include<uv.h>
namespace kengine {
	struct AsyncWork {
		bool clear=true;
		void* data=nullptr;
		std::function<void(void*)> work = [](void * data) {};
		std::function<void(int, void*)> complete=[](int status,void* data) {};
	};
	class AsyncService
	{
	public:
		uv_loop_t loop;
		AsyncService()
		{
			uv_loop_init(&loop);
		}

		~AsyncService()
		{
			uv_loop_close(&loop);
		}

		void update() {
			uv_run(&loop, UV_RUN_NOWAIT);
		}

		void work(void * data, std::function<void(void*)> w, std::function<void(int,void*)> complete) {
			AsyncWork* work = new AsyncWork();
			work->data = data;
			work->work = w;
			work->complete = complete;
			uv_work_t* req=new uv_work_t();
			req->data = work;
			uv_queue_work(&loop, req, work_cb, after_work_cb);
		}

		void work(AsyncWork *work) {
			uv_work_t* req = new uv_work_t();
			req->data = work;
			uv_queue_work(&loop, req, work_cb, after_work_cb);
		}

		static void  work_cb(uv_work_t* req) {
			AsyncWork* work =(AsyncWork*) req->data;
			work->work(work->data);
		}
		static void  after_work_cb(uv_work_t* req,int status) {
			AsyncWork* work = (AsyncWork*)req->data;
			work->complete(status, work->data);
			if (work->clear) {
				delete work;
			}
			delete req;
		}
	private:

	};

}