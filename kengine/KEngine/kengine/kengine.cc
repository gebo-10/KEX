#include <iostream>
#include "kengine.h"
#include "platform/platform.h"
#include "profiler/profiler.h"
#include "core/io/kengine_io.h"
//#define ZMQ_STATIC
//#define ZMQ_USE_TWEETNACL
//#include <zmq.h>

//#include "rapidjson/document.h"
//
//using namespace rapidjson;
using namespace kengine;
void KEngine::init() {
    //void* context = zmq_ctx_new();
    //void* responder = zmq_socket(context, ZMQ_REP);
    //int rc = zmq_bind(responder, "tcp://*:5555");
    //assert(rc == 0);

    //Document document;
    //document.Parse("{}");

    //ResourceManager.register_default();
    //ResourceManager.load_resource();
    //Platform::instance().init_platform();
    Env.init();
    auto vert_buff = Env.io->read_file("main/shader/default.vert.glsl");
    string file("main/shader/default.vert.glsl");
    auto b = Env.io->mmap_file(file);
    info(b->data());
    //auto bundle = Env.assets_database.load_bundle("test.bundle");
    //Env.assets_database.load_all_bundle_asset(bundle);
    //auto res = Env.assets_database.get_resource<Shader>(1);
    //info(res->vert_source);
    //res = Env.assets_database.get_resource<Shader>(0);
    //info(res->vert_source);
    auto name_buff = Env.io->read_file("name.db");
    Env.name_service.init(name_buff);
    
}

void KEngine::update()
{
    static int a = 0;
    a++;
    Env.time.update();
    info("fps:{}", Env.time.fps);

    //Env.profiler.fps_limit();
    //info("hello{}",a);

}

void KEngine::quit()
{
}


void KEngine::on_view_size(int width, int height)
{
	info("view size change {}{}", width, height);
}

//void load_resource() {
//    sol::table tb = Config::instacne().data["resource"];
//
//    for (auto package : tb) {
//        string name = package.second.as<string>();
//        load_package(name);
//    }

//}

kengine::KEngine& GetKEngineInstance()
{
    auto e= new KEngine();
    return *e;
}

