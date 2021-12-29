#include <iostream>
#include "kengine.h"
#include "platform/platform.h"
#include "profiler/profiler.h"
#include "core/io/kengine_io.h"
#include "gpgpu/gpgpu.h"


//#include "rapidjson/document.h"
//using namespace rapidjson;
using namespace kengine;
void KEngine::init(int width, int height) {

    //Document document;
    //document.Parse("{}");

    //ResourceManager.register_default();
    //ResourceManager.load_resource();
    //Platform::instance().init_platform();
    Screen::width = width;
    Screen::height = height;
    Env.init();
    auto name_buff = Env.io->read_file("name.db");
    Env.name_service.init(name_buff);

    auto bundle = Env.assets_database.load_bundle("test.bundle");
    Env.assets_database.load_all_bundle_asset(bundle);

    //Env.async_service.work(nullptr, 
    //    [](void* data) {
    //        info("work.............");
    //        uv_sleep(3000);
    //    }, 
    //    [](int status, void* data) {
    //        info("complete.............");
    //    });

    //auto vert_buff = Env.io->read_file("main/shader/default.vert.glsl");
    //string file("main/shader/default.vert.glsl");
    //auto b = Env.io->mmap_file(file);
    //info(b->data());

    
    //auto mat = Env.assets_database.get_resource<Material>(NAME("Assets/Bundle/cs1.material"));

    //info(shader->vert_source);
    //mat->gpucache();


    //GPGPU gpgpu;
    //gpgpu.set_material(mat);
    //auto ssbo = std::make_shared<GPUBuffer>(32*16*2 *sizeof(int), GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::DYNAMIC_DRAW);
    //gpgpu.attach_buffer(0,ssbo);
    //gpgpu.setup(2,1,1);
    //int* res =(int*) ssbo->map(GPUBufferHit::READ_ONLY);
    //
    //for (int i = 0; i < 32 * 16 * 2; i++)
    //{
    //    std::cout << res[i] << " ";
    //}

    //auto mesh = Env.assets_database.get_resource<Mesh>(NAME("Assets/Bundle/box.fbx"));
    //mesh->gpucache();

    //res = Env.assets_database.get_resource<Shader>(0);
    //info(res->vert_source);
    
    /*glDisable(GL_SCISSOR_TEST);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilMask(0xFFFFFFFF);*/

    render.init();
    scene_manager.init();
    on_view_size(width, height);
}

void KEngine::update()
{
    Env.update();
    ui.new_frame();

    Env.event_service.dispatch(EventType::OnUpdate, nullptr);

    render.update(*scene_manager.scene);

    ui.end_frame();
}

void KEngine::quit()
{
}


void KEngine::on_view_size(int width, int height)
{
	info("view size change {} * {}", width, height);
    if (width == 0 || height == 0) return;
    Screen::width = width;
    Screen::height = height;
    OnViewSize e;
    e.width = width;
    e.height = height;
    Env.event_service.dispatch(EventType::OnViewSize, &e);
}


kengine::KEngine& GetKEngineInstance()
{
    auto e= new KEngine();
    return *e;
}

