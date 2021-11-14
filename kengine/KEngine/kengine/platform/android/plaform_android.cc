#include "../platform.h"
#include "io_android.h"

using namespace kengine;
IO* IO::instance_;
bool Platform::init_platform(){
    AAssetManager *mgr=(AAssetManager *)get_object("AssetManager");
    if(mgr==NULL)
    {
        LOGI(" %s","AAssetManager==NULL");
        return false;
    }
    auto instance= new IOAndroid();
    instance->set_manager(mgr);
    IO::set_instance(instance);
    return true;
}