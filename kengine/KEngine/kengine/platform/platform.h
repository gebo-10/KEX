#pragma once
#include <map>
#include <string>
#include "../core/base/type.h"
namespace kengine{
    class Platform{
    public:
        //static Platform & instance(){
        //    static Platform platform;
        //    return platform;
        //}
        std::map<string, void *> system_object;
        bool set_object(string name, void * ptr){
            system_object.insert(make_pair(name,ptr));
            return true;
        }

        void * get_object(string name){
            return system_object.find(name)->second;
        }


        bool init();

    };
}