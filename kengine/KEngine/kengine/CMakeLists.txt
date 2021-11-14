cmake_minimum_required (VERSION 3.8)

add_subdirectory ("external/spdlog")
add_subdirectory ("external/glm")
add_subdirectory ("external/rapidjson")

include_directories(external/rapidjson/include)

include_directories(external/zmq_prebuild/win64_debug)
FIND_LIBRARY(zmq libzmq-v142-mt-sgd-4_3_4.lib external/zmq_prebuild/win64_debug)


add_library(kengine STATIC kengine.cc "geometry/cube.h" "geometry/plane.h" "resource/component/mesh.h" "resource/resource_manager.h" "resource/resource.h" "scene/3d/light.h"  "core/base/uid.h" "resource/loader/file_loader.h" "resource/loader/network_loader.h" "resource/loader/kbf_loader.h" "resource/component/script.h" "resource/component/prefab.h" "resource/component/animation.h" "application.h" "system/render_system.h" "system/physics_system.h" "assets/assets.h" "assets/assets_database.h" "resource/loader/assets_loader.h" "resource/loader/resource_loader.h" "assets/bundle.h" "system/logic_system.h" "core/graphics/gpu_image.h" "core/graphics/gpu_object.h" "core/graphics/gpu_shader.h" "core/graphics/gpu_resource.h" "resource/component/model.h" "core/graphics/gpu_target.h" "core/graphics/gpu_type.h")
target_link_libraries(kengine spdlog glm ${zmq} wsock32.lib ws2_32.lib Iphlpapi.lib)

