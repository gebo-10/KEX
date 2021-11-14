#pragma once
#include "../../core/io/kengine_io.h"
#include "../../core/base/buffer.h"
#include <assert.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <android/log.h>
#define LOGI(...) __android_log_print( ANDROID_LOG_DEBUG, " keymatch", __VA_ARGS__)
namespace kengine{
class IOAndroid : public IO{
public:
    void set_manager(AAssetManager * m){
        mgr=m;
    }
    BufferPtr read_file(string name) override{
        AAsset* asset = AAssetManager_open(mgr, name.c_str(),AASSET_MODE_UNKNOWN);
        if(asset==NULL)
        {
            LOGI(" %s","asset==NULL");
            return nullptr;
        }
        /*获取文件大小*/
        uint32 bufferSize = (uint32)AAsset_getLength(asset);
        LOGI("file size         : %d\n",bufferSize);
        auto new_buf=std::make_shared<Buffer>(bufferSize+1);
        //char *buffer=(char *)malloc(bufferSize+1);
        new_buf->data[bufferSize]=0;
        LOGI("111111111");
        int numBytesRead = AAsset_read(asset, new_buf->data, bufferSize);
        LOGI("222222222222");
        LOGI(": %s",(char *)new_buf->data);
        //free(buffer);
        /*关闭文件*/
        AAsset_close(asset);
        return new_buf;
    }

private:
    AAssetManager* mgr;
};
}