#pragma once
#include <thread>
#define ZMQ_STATIC
#define ZMQ_USE_TWEETNACL
#include <zmq.h>
#include <assert.h>
#include "monitor_processor.h"
#include "test_processor.h"
#include <flatbuffers/flexbuffers.h>
namespace kengine {
	class Monitor
	{
	public:
		Work async_work;
		
		void* zmq_context;
		void* zmq_responder;

		BufferPtr recv_buffer;
		BufferPtr result_buffer;
		BufferPtr recv_buffer_view=nullptr;

		MonitorProcessor * processor[(int)MonitorCommandType::Num];
		Monitor()
		{
			async_work.clear = false;
			async_work.data = this;
			async_work.work = zmq_recv_work;
			async_work.complete = zmq_recv_complete;

			zmq_context = zmq_ctx_new();
			zmq_responder = zmq_socket(zmq_context, ZMQ_REP);
			int rc = zmq_bind(zmq_responder, "tcp://*:5555");
			assert(rc == 0);

			recv_buffer = std::make_shared<Buffer>(64 * 1024);
			result_buffer = std::make_shared<Buffer>(1 * 1024);

			init_processor();

			Env.async_service.work(&async_work);
		}

		~Monitor()
		{
			zmq_close(zmq_responder);
			zmq_ctx_destroy(zmq_context);
		}

		void init_processor() {
			processor[(int)MonitorCommandType::Test] = new TestProcessor();
		}

		static void zmq_recv_work(void * data) {
			Monitor* monitor =(Monitor*) data;
			int recv_count = zmq_recv(monitor->zmq_responder, monitor->recv_buffer->data, monitor->recv_buffer->size, 0);
			monitor->recv_buffer_view = monitor->recv_buffer->view(0, recv_count);
			info("recv monitor msg count ={}",recv_count);
		}

		static void zmq_recv_complete(int status, void* data) {
			Monitor* monitor = (Monitor*)data;

			auto root = flexbuffers::GetRoot((uint8_t *)monitor->recv_buffer_view->data, monitor->recv_buffer_view->size);
			auto v = root.AsVector();
			uint16 type = v[0].AsUInt16();

			BufferPtr result_buffer_view = monitor->result_buffer->view(0, 0);
			monitor->processor[type]->process(monitor->recv_buffer_view,result_buffer_view);

			zmq_send(monitor->zmq_responder, result_buffer_view->data, result_buffer_view ->size, 0);
			Env.async_service.work(&monitor->async_work);
		}

	};
};