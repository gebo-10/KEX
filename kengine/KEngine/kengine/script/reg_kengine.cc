#include "auto_registe.h"
#include <kengine/kengine.h>
namespace kengine {
void reg_kengine(sol::table& lua) {
	{
		sol::usertype<kengine::Application> type = lua.new_usertype<kengine::Application>("Application"
			,sol::constructors <
			kengine::Application ()
			> ()
		);
        type["on_config"] = &kengine::Application::on_config;
        type["on_update"] = &kengine::Application::on_update;
        type["on_project_loaded"] = &kengine::Application::on_project_loaded;
        type["register_matedata"] = &kengine::Application::register_matedata;
	}
	{
		sol::usertype<kengine::Config> type = lua.new_usertype<kengine::Config>("Config"
			,sol::constructors <
			kengine::Config ()
			> ()
		);
        type["fps_limit"] = &kengine::Config::fps_limit;
        type["lua"] = &kengine::Config::lua;
        type["data"] = &kengine::Config::data;
        type["init"] = &kengine::Config::init;
	}
	{
		sol::usertype<kengine::Buffer> type = lua.new_usertype<kengine::Buffer>("Buffer"
			,sol::constructors <
			kengine::Buffer (),
			kengine::Buffer (void *, uint32, bool),
			kengine::Buffer (uint32)
			> ()
		);
        type["malloced"] = &kengine::Buffer::malloced;
        type["data"] = &kengine::Buffer::data;
        type["size"] = &kengine::Buffer::size;
        type["malloc"] = &kengine::Buffer::malloc;
        type["free"] = &kengine::Buffer::free;
	}
	{
		sol::usertype<kengine::RGBA> type = lua.new_usertype<kengine::RGBA>("RGBA"
			,sol::constructors <
			kengine::RGBA ()
			> ()
		);
        type["r"] = &kengine::RGBA::r;
        type["g"] = &kengine::RGBA::g;
        type["b"] = &kengine::RGBA::b;
        type["a"] = &kengine::RGBA::a;
        type["i"] = &kengine::RGBA::i;
	}
	{
		sol::usertype<kengine::Color> type = lua.new_usertype<kengine::Color>("Color"
			,sol::constructors <
			kengine::Color (),
			kengine::Color (float, float, float, float),
			kengine::Color (float, float, float)
			> ()
		);
        type["r"] = &kengine::Color::r;
        type["g"] = &kengine::Color::g;
        type["b"] = &kengine::Color::b;
        type["a"] = &kengine::Color::a;
        type["operator=="] = &kengine::Color::operator==;
        type["operator!="] = &kengine::Color::operator!=;
        type["operator*"] = &kengine::Color::operator*;
        type["to_hsl"] = &kengine::Color::to_hsl;
        type["get_component"] = &kengine::Color::get_component;
	}
	{
		sol::usertype<kengine::Memery> type = lua.new_usertype<kengine::Memery>("Memery"
			,sol::constructors <
			kengine::Memery ()
			> ()
		);
        type["endian"] = &kengine::Memery::endian;
        type["ntohs"] = &kengine::Memery::ntohs;
        type["ntohi"] = &kengine::Memery::ntohi;
	}
	{
		sol::usertype<kengine::Profiler> type = lua.new_usertype<kengine::Profiler>("Profiler"
			,sol::constructors <
			kengine::Profiler ()
			> ()
		);
        type["init"] = &kengine::Profiler::init;
	}
	{
		sol::usertype<kengine::Time> type = lua.new_usertype<kengine::Time>("Time"
		);
        type["elapsed"] = &kengine::Time::elapsed;
        type["now"] = &kengine::Time::now;
        type["frame_count"] = &kengine::Time::frame_count;
        type["fps_sample"] = &kengine::Time::fps_sample;
        type["init"] = &kengine::Time::init;
        type["update"] = &kengine::Time::update;
        type["limit"] = &kengine::Time::limit;
        type["fps"] = &kengine::Time::fps;
	}
	{
		sol::usertype<kengine::Platform> type = lua.new_usertype<kengine::Platform>("Platform"
		);
        type["set_object"] = &kengine::Platform::set_object;
        type["get_object"] = &kengine::Platform::get_object;
        type["init"] = &kengine::Platform::init;
	}
	{
		sol::usertype<kengine::IO> type = lua.new_usertype<kengine::IO>("IO"
		);
        type["read_file"] = &kengine::IO::read_file;
        type["mmap_file"] = &kengine::IO::mmap_file;
	}
	{
		sol::usertype<kengine::Resource> type = lua.new_usertype<kengine::Resource>("Resource"
			,sol::constructors <
			kengine::Resource ()
			> ()
		);
        type["dirty"] = &kengine::Resource::dirty;
	}
	{
		sol::usertype<kengine::Shader> type = lua.new_usertype<kengine::Shader>("Shader"
			,sol::constructors <
			kengine::Shader (),
			kengine::Shader (string &, string &),
			kengine::Shader (string &)
			> ()
			,sol::base_classes, sol::bases<kengine::Resource>()
		);
        type["gpu_shader"] = &kengine::Shader::gpu_shader;
        type["vert_source"] = &kengine::Shader::vert_source;
        type["frag_source"] = &kengine::Shader::frag_source;
        type["compute_source"] = &kengine::Shader::compute_source;
        type["gpucache"] = &kengine::Shader::gpucache;
        type["uncache"] = &kengine::Shader::uncache;
        type["bind"] = &kengine::Shader::bind;
        type["unbind"] = &kengine::Shader::unbind;
        type["sync"] = &kengine::Shader::sync;
        type["set_uniform"] = &kengine::Shader::set_uniform;
        type["get_uniform"] = &kengine::Shader::get_uniform;
	}
	{
		sol::usertype<kengine::Mesh> type = lua.new_usertype<kengine::Mesh>("Mesh"
			,sol::base_classes, sol::bases<kengine::Resource>()
		);
        type["gpu_object"] = &kengine::Mesh::gpu_object;
        type["primitive"] = &kengine::Mesh::primitive;
        type["indices_buffer"] = &kengine::Mesh::indices_buffer;
        type["gpucache"] = &kengine::Mesh::gpucache;
        type["uncache"] = &kengine::Mesh::uncache;
        type["add_buffer"] = &kengine::Mesh::add_buffer;
        type["get_buffer"] = &kengine::Mesh::get_buffer;
        type["set_indices"] = &kengine::Mesh::set_indices;
        type["set_position"] = &kengine::Mesh::set_position;
        type["set_normal"] = &kengine::Mesh::set_normal;
        type["set_tangent"] = &kengine::Mesh::set_tangent;
        type["set_color"] = &kengine::Mesh::set_color;
        type["set_uv"] = &kengine::Mesh::set_uv;
        type["set_bone_data"] = &kengine::Mesh::set_bone_data;
        type["draw"] = &kengine::Mesh::draw;
	}
	{
		sol::usertype<kengine::Material> type = lua.new_usertype<kengine::Material>("Material"
			,sol::constructors <
			kengine::Material (int),
			kengine::Material (const kengine::Material &)
			> ()
			,sol::base_classes, sol::bases<kengine::Resource>()
		);
        type["shader"] = &kengine::Material::shader;
        type["bind"] = &kengine::Material::bind;
        type["set_dirty"] = &kengine::Material::set_dirty;
        type["attach_uniform"] = &kengine::Material::attach_uniform;
        type["set_shader"] = &kengine::Material::set_shader;
        type["set_model_matrix"] = &kengine::Material::set_model_matrix;
        type["set_uniform"] = &kengine::Material::set_uniform;
        type["add_uniform"] = &kengine::Material::add_uniform;
        type["get_uniform"] = &kengine::Material::get_uniform;
        type["set_uniforms"] = &kengine::Material::set_uniforms;
        type["add_texture"] = &kengine::Material::add_texture;
        type["add_textures"] = &kengine::Material::add_textures;
        type["add_buffer"] = &kengine::Material::add_buffer;
        type["add_buffers"] = &kengine::Material::add_buffers;
	}
	{
		sol::usertype<kengine::Asset> type = lua.new_usertype<kengine::Asset>("Asset"
		);
        type["type"] = &kengine::Asset::type;
        type["cache_type"] = &kengine::Asset::cache_type;
        type["memery_type"] = &kengine::Asset::memery_type;
        type["id"] = &kengine::Asset::id;
        type["default_resource"] = &kengine::Asset::default_resource;
        type["instaniate"] = &kengine::Asset::instaniate;
        type["serialize"] = &kengine::Asset::serialize;
        type["deserialize"] = &kengine::Asset::deserialize;
        type["deserialize_shader"] = &kengine::Asset::deserialize_shader;
        type["deserialize_mesh"] = &kengine::Asset::deserialize_mesh;
        type["deserialize_material"] = &kengine::Asset::deserialize_material;
	}
	{
		sol::usertype<kengine::AccessLoader> type = lua.new_usertype<kengine::AccessLoader>("AccessLoader"
			,sol::constructors <
			kengine::AccessLoader ()
			> ()
		);
        type["bundle_size"] = &kengine::AccessLoader::bundle_size;
        type["get_info_buffer"] = &kengine::AccessLoader::get_info_buffer;
        type["load_asset"] = &kengine::AccessLoader::load_asset;
        type["unload_asset"] = &kengine::AccessLoader::unload_asset;
	}
	{
		sol::usertype<kengine::FileAccessLoader> type = lua.new_usertype<kengine::FileAccessLoader>("FileAccessLoader"
			,sol::constructors <
			kengine::FileAccessLoader (string_view)
			> ()
			,sol::base_classes, sol::bases<kengine::AccessLoader>()
		);
        type["file"] = &kengine::FileAccessLoader::file;
        type["get_info_buffer"] = &kengine::FileAccessLoader::get_info_buffer;
        type["load_asset"] = &kengine::FileAccessLoader::load_asset;
        type["unload_asset"] = &kengine::FileAccessLoader::unload_asset;
	}
	{
		sol::usertype<kengine::MemeryAccessLoader> type = lua.new_usertype<kengine::MemeryAccessLoader>("MemeryAccessLoader"
			,sol::constructors <
			kengine::MemeryAccessLoader (int)
			> ()
			,sol::base_classes, sol::bases<kengine::AccessLoader>()
		);
        type["buffer"] = &kengine::MemeryAccessLoader::buffer;
        type["get_info_buffer"] = &kengine::MemeryAccessLoader::get_info_buffer;
        type["load_asset"] = &kengine::MemeryAccessLoader::load_asset;
        type["unload_asset"] = &kengine::MemeryAccessLoader::unload_asset;
	}
	{
		sol::usertype<kengine::AssetBundle> type = lua.new_usertype<kengine::AssetBundle>("AssetBundle"
			,sol::constructors <
			kengine::AssetBundle (string_view, kengine::AssetBundle::FileAccessType)
			> ()
		);
        type["file_access_type"] = &kengine::AssetBundle::file_access_type;
        type["id"] = &kengine::AssetBundle::id;
        type["access_loader"] = &kengine::AssetBundle::access_loader;
        type["size"] = &kengine::AssetBundle::size;
        type["serialize"] = &kengine::AssetBundle::serialize;
        type["deserialize_info"] = &kengine::AssetBundle::deserialize_info;
        type["load_asset"] = &kengine::AssetBundle::load_asset;
	}
	{
		sol::usertype<kengine::AssetLoader> type = lua.new_usertype<kengine::AssetLoader>("AssetLoader"
			,sol::constructors <
			kengine::AssetLoader ()
			> ()
		);
        type["load"] = &kengine::AssetLoader::load;
        type["load_async"] = &kengine::AssetLoader::load_async;
	}
	{
		sol::usertype<kengine::PlaneMesh> type = lua.new_usertype<kengine::PlaneMesh>("PlaneMesh"
			,sol::constructors <
			kengine::PlaneMesh ()
			> ()
			,sol::base_classes, sol::bases<kengine::Mesh>()
		);
        type["position"] = &kengine::PlaneMesh::position;
        type["position1"] = &kengine::PlaneMesh::position1;
        type["color"] = &kengine::PlaneMesh::color;
        type["uv"] = &kengine::PlaneMesh::uv;
        type["normal"] = &kengine::PlaneMesh::normal;
        type["indices"] = &kengine::PlaneMesh::indices;
	}
	{
		sol::usertype<kengine::AssetsDatabase> type = lua.new_usertype<kengine::AssetsDatabase>("AssetsDatabase"
			,sol::constructors <
			kengine::AssetsDatabase ()
			> ()
		);
        type["default_resource"] = &kengine::AssetsDatabase::default_resource;
        type["load_asset"] = &kengine::AssetsDatabase::load_asset;
        type["load_bundle"] = &kengine::AssetsDatabase::load_bundle;
        type["unload_bundle"] = &kengine::AssetsDatabase::unload_bundle;
        type["load_bundle_asset"] = &kengine::AssetsDatabase::load_bundle_asset;
	}
	{
		sol::usertype<kengine::NameService> type = lua.new_usertype<kengine::NameService>("NameService"
			,sol::constructors <
			kengine::NameService ()
			> ()
		);
        type["init"] = &kengine::NameService::init;
        type["add"] = &kengine::NameService::add;
        type["get_id"] = &kengine::NameService::get_id;
        type["get_str"] = &kengine::NameService::get_str;
	}
	{
		sol::usertype<kengine::AsyncService> type = lua.new_usertype<kengine::AsyncService>("AsyncService"
			,sol::constructors <
			kengine::AsyncService ()
			> ()
		);
        type["loop"] = &kengine::AsyncService::loop;
        type["update"] = &kengine::AsyncService::update;
        type["work"] =sol::overload(
			sol::resolve <void (void *, int)>(&kengine::AsyncService::work)
			sol::resolve <void (kengine::AsyncWork *)>(&kengine::AsyncService::work)
        );
        type["work_cb"] = &kengine::AsyncService::work_cb;
        type["after_work_cb"] = &kengine::AsyncService::after_work_cb;
	}
	{
		sol::usertype<kengine::EventService> type = lua.new_usertype<kengine::EventService>("EventService"
			,sol::constructors <
			kengine::EventService ()
			> ()
		);
        type["listen"] = &kengine::EventService::listen;
        type["unlisten"] = &kengine::EventService::unlisten;
        type["dispatch"] = &kengine::EventService::dispatch;
	}
	{
		sol::usertype<kengine::Environment> type = lua.new_usertype<kengine::Environment>("Environment"
		);
        type["config"] = &kengine::Environment::config;
        type["time"] = &kengine::Environment::time;
        type["profiler"] = &kengine::Environment::profiler;
        type["platform"] = &kengine::Environment::platform;
        type["io"] = &kengine::Environment::io;
        type["name_service"] = &kengine::Environment::name_service;
        type["async_service"] = &kengine::Environment::async_service;
        type["event_service"] = &kengine::Environment::event_service;
        type["assets_database"] = &kengine::Environment::assets_database;
        type["instance"] = &kengine::Environment::instance;
        type["init"] = &kengine::Environment::init;
        type["update"] = &kengine::Environment::update;
	}
	{
		sol::usertype<kengine::TypeInfo> type = lua.new_usertype<kengine::TypeInfo>("TypeInfo"
		);
        type["gpu_type_size"] = &kengine::TypeInfo::gpu_type_size;
        type["shader_data_type_info"] = &kengine::TypeInfo::shader_data_type_info;
	}
	{
		sol::usertype<kengine::PipelineState> type = lua.new_usertype<kengine::PipelineState>("PipelineState"
			,sol::constructors <
			kengine::PipelineState (),
			kengine::PipelineState (kengine::PipelineStateType)
			> ()
		);
        type["type"] = &kengine::PipelineState::type;
        type["set"] = &kengine::PipelineState::set;
        type["setup"] = &kengine::PipelineState::setup;
	}
	{
		sol::usertype<kengine::DepthTest> type = lua.new_usertype<kengine::DepthTest>("DepthTest"
			,sol::constructors <
			kengine::DepthTest (bool, kengine::CompareFunc)
			> ()
			,sol::base_classes, sol::bases<kengine::PipelineState>()
		);
        type["enable"] = &kengine::DepthTest::enable;
        type["compare_func"] = &kengine::DepthTest::compare_func;
        type["set"] = &kengine::DepthTest::set;
        type["setup"] = &kengine::DepthTest::setup;
	}
	{
		sol::usertype<kengine::StencilTest> type = lua.new_usertype<kengine::StencilTest>("StencilTest"
			,sol::constructors <
			kengine::StencilTest (bool)
			> ()
			,sol::base_classes, sol::bases<kengine::PipelineState>()
		);
        type["enable"] = &kengine::StencilTest::enable;
        type["set"] = &kengine::StencilTest::set;
        type["setup"] = &kengine::StencilTest::setup;
	}
	{
		sol::usertype<kengine::ClearValue> type = lua.new_usertype<kengine::ClearValue>("ClearValue"
			,sol::constructors <
			kengine::ClearValue (kengine::Color, float, int)
			> ()
			,sol::base_classes, sol::bases<kengine::PipelineState>()
		);
        type["clear_color"] = &kengine::ClearValue::clear_color;
        type["clear_depth"] = &kengine::ClearValue::clear_depth;
        type["clear_stencil"] = &kengine::ClearValue::clear_stencil;
        type["set"] = &kengine::ClearValue::set;
        type["setup"] = &kengine::ClearValue::setup;
	}
	{
		sol::usertype<kengine::ViewPortState> type = lua.new_usertype<kengine::ViewPortState>("ViewPortState"
			,sol::constructors <
			kengine::ViewPortState (int)
			> ()
			,sol::base_classes, sol::bases<kengine::PipelineState>()
		);
        type["view_port"] = &kengine::ViewPortState::view_port;
        type["set"] = &kengine::ViewPortState::set;
        type["setup"] = &kengine::ViewPortState::setup;
	}
	{
		sol::usertype<kengine::ScissorState> type = lua.new_usertype<kengine::ScissorState>("ScissorState"
			,sol::constructors <
			kengine::ScissorState (bool, int)
			> ()
			,sol::base_classes, sol::bases<kengine::PipelineState>()
		);
        type["enable"] = &kengine::ScissorState::enable;
        type["rect"] = &kengine::ScissorState::rect;
        type["set"] = &kengine::ScissorState::set;
        type["setup"] = &kengine::ScissorState::setup;
	}
	{
		sol::usertype<kengine::RenderBuffer> type = lua.new_usertype<kengine::RenderBuffer>("RenderBuffer"
			,sol::constructors <
			kengine::RenderBuffer (int, int, kengine::RenderBufferFormat, int)
			> ()
		);
        type["gpu_id"] = &kengine::RenderBuffer::gpu_id;
        type["width"] = &kengine::RenderBuffer::width;
        type["height"] = &kengine::RenderBuffer::height;
	}
	{
		sol::usertype<kengine::Attachment> type = lua.new_usertype<kengine::Attachment>("Attachment"
			,sol::constructors <
			kengine::Attachment ()
			> ()
		);
        type["type"] = &kengine::Attachment::type;
        type["attachment_point"] = &kengine::Attachment::attachment_point;
        type["width"] = &kengine::Attachment::width;
        type["height"] = &kengine::Attachment::height;
        type["texture"] = &kengine::Attachment::texture;
        type["render_buffer"] = &kengine::Attachment::render_buffer;
        type["attach"] = &kengine::Attachment::attach;
	}
	{
		sol::usertype<kengine::RenderTarget> type = lua.new_usertype<kengine::RenderTarget>("RenderTarget"
			,sol::constructors <
			kengine::RenderTarget ()
			> ()
		);
        type["gpu_id"] = &kengine::RenderTarget::gpu_id;
        type["check_attachment_size"] = &kengine::RenderTarget::check_attachment_size;
        type["get_texture"] = &kengine::RenderTarget::get_texture;
        type["bind"] = &kengine::RenderTarget::bind;
        type["check_complete"] = &kengine::RenderTarget::check_complete;
	}
	{
		sol::usertype<kengine::CommonUniform> type = lua.new_usertype<kengine::CommonUniform>("CommonUniform"
		);
        type["time"] = &kengine::CommonUniform::time;
        type["camears"] = &kengine::CommonUniform::camears;
        type["lights"] = &kengine::CommonUniform::lights;
        type["uniform_buffer"] = &kengine::CommonUniform::uniform_buffer;
        type["sync"] = &kengine::CommonUniform::sync;
	}
	{
		sol::usertype<kengine::BindPointManager> type = lua.new_usertype<kengine::BindPointManager>("BindPointManager"
			,sol::constructors <
			kengine::BindPointManager ()
			> ()
		);
        type["shader_bind_point"] = &kengine::BindPointManager::shader_bind_point;
        type["vao_bind_point"] = &kengine::BindPointManager::vao_bind_point;
        type["ubo_bind_point"] = &kengine::BindPointManager::ubo_bind_point;
        type["ssbo_bind_point"] = &kengine::BindPointManager::ssbo_bind_point;
        type["texture_bind_point"] = &kengine::BindPointManager::texture_bind_point;
        type["bind_shader"] = &kengine::BindPointManager::bind_shader;
        type["bind_vao"] = &kengine::BindPointManager::bind_vao;
        type["bind_ubo"] = &kengine::BindPointManager::bind_ubo;
        type["bind_ssbo"] = &kengine::BindPointManager::bind_ssbo;
        type["bind_texture"] = &kengine::BindPointManager::bind_texture;
	}
	{
		sol::usertype<kengine::Pipeline> type = lua.new_usertype<kengine::Pipeline>("Pipeline"
			,sol::constructors <
			kengine::Pipeline ()
			> ()
		);
        type["bind_point_manager"] = &kengine::Pipeline::bind_point_manager;
        type["common_uniform"] = &kengine::Pipeline::common_uniform;
        type["states"] = &kengine::Pipeline::states;
        type["target"] = &kengine::Pipeline::target;
        type["material"] = &kengine::Pipeline::material;
        type["draw"] = &kengine::Pipeline::draw;
        type["set_target"] = &kengine::Pipeline::set_target;
        type["use_material"] = &kengine::Pipeline::use_material;
        type["set_state"] = &kengine::Pipeline::set_state;
        type["sync_common_uniform"] = &kengine::Pipeline::sync_common_uniform;
	}
	{
		sol::usertype<kengine::Pass> type = lua.new_usertype<kengine::Pass>("Pass"
			,sol::constructors <
			kengine::Pass ()
			> ()
		);
        type["exec"] = &kengine::Pass::exec;
	}
	{
		sol::usertype<kengine::ClearPass> type = lua.new_usertype<kengine::ClearPass>("ClearPass"
			,sol::constructors <
			kengine::ClearPass (bool, bool, bool)
			> ()
			,sol::base_classes, sol::bases<kengine::Pass>()
		);
        type["clear_mask"] = &kengine::ClearPass::clear_mask;
        type["exec"] = &kengine::ClearPass::exec;
	}
	{
		sol::usertype<kengine::StatePass> type = lua.new_usertype<kengine::StatePass>("StatePass"
			,sol::constructors <
			kengine::StatePass ()
			> ()
			,sol::base_classes, sol::bases<kengine::Pass>()
		);
        type["exec"] = &kengine::StatePass::exec;
	}
	{
		sol::usertype<kengine::DrawPass> type = lua.new_usertype<kengine::DrawPass>("DrawPass"
			,sol::base_classes, sol::bases<kengine::Pass>()
		);
        type["target"] = &kengine::DrawPass::target;
        type["camera_id"] = &kengine::DrawPass::camera_id;
        type["exec"] = &kengine::DrawPass::exec;
	}
	{
		sol::usertype<kengine::FencePass> type = lua.new_usertype<kengine::FencePass>("FencePass"
			,sol::constructors <
			kengine::FencePass ()
			> ()
			,sol::base_classes, sol::bases<kengine::Pass>()
		);
        type["exec"] = &kengine::FencePass::exec;
	}
	{
		sol::usertype<kengine::CopyFrameBufferPass> type = lua.new_usertype<kengine::CopyFrameBufferPass>("CopyFrameBufferPass"
			,sol::constructors <
			kengine::CopyFrameBufferPass ()
			> ()
			,sol::base_classes, sol::bases<kengine::Pass>()
		);
        type["src"] = &kengine::CopyFrameBufferPass::src;
        type["dist"] = &kengine::CopyFrameBufferPass::dist;
        type["src_region"] = &kengine::CopyFrameBufferPass::src_region;
        type["dist_region"] = &kengine::CopyFrameBufferPass::dist_region;
        type["component"] = &kengine::CopyFrameBufferPass::component;
        type["filter"] = &kengine::CopyFrameBufferPass::filter;
        type["exec"] = &kengine::CopyFrameBufferPass::exec;
	}
	{
		sol::usertype<kengine::BlitPass> type = lua.new_usertype<kengine::BlitPass>("BlitPass"
			,sol::constructors <
			kengine::BlitPass ()
			> ()
			,sol::base_classes, sol::bases<kengine::Pass>()
		);
        type["render_target"] = &kengine::BlitPass::render_target;
        type["material"] = &kengine::BlitPass::material;
        type["plane"] = &kengine::BlitPass::plane;
        type["exec"] = &kengine::BlitPass::exec;
	}
	{
		sol::usertype<kengine::LambdaPass> type = lua.new_usertype<kengine::LambdaPass>("LambdaPass"
			,sol::constructors <
			kengine::LambdaPass ()
			> ()
			,sol::base_classes, sol::bases<kengine::Pass>()
		);
        type["exec"] = &kengine::LambdaPass::exec;
	}
	{
		sol::usertype<kengine::RenderGraph> type = lua.new_usertype<kengine::RenderGraph>("RenderGraph"
			,sol::constructors <
			kengine::RenderGraph ()
			> ()
		);
        type["pipeline"] = &kengine::RenderGraph::pipeline;
        type["exec"] = &kengine::RenderGraph::exec;
	}
	{
		sol::usertype<kengine::Render> type = lua.new_usertype<kengine::Render>("Render"
			,sol::constructors <
			kengine::Render ()
			> ()
		);
        type["init"] = &kengine::Render::init;
        type["update"] = &kengine::Render::update;
	}
	{
		sol::usertype<kengine::MonitorProcessor> type = lua.new_usertype<kengine::MonitorProcessor>("MonitorProcessor"
			,sol::constructors <
			kengine::MonitorProcessor ()
			> ()
		);
        type["process"] = &kengine::MonitorProcessor::process;
	}
	{
		sol::usertype<kengine::TestProcessor> type = lua.new_usertype<kengine::TestProcessor>("TestProcessor"
			,sol::constructors <
			kengine::TestProcessor ()
			> ()
			,sol::base_classes, sol::bases<kengine::MonitorProcessor>()
		);
        type["process"] = &kengine::TestProcessor::process;
	}
	{
		sol::usertype<kengine::Monitor> type = lua.new_usertype<kengine::Monitor>("Monitor"
			,sol::constructors <
			kengine::Monitor ()
			> ()
		);
        type["async_work"] = &kengine::Monitor::async_work;
        type["zmq_context"] = &kengine::Monitor::zmq_context;
        type["zmq_responder"] = &kengine::Monitor::zmq_responder;
        type["recv_buffer"] = &kengine::Monitor::recv_buffer;
        type["recv_buffer_view"] = &kengine::Monitor::recv_buffer_view;
        type["processor"] = &kengine::Monitor::processor;
        type["init_processor"] = &kengine::Monitor::init_processor;
        type["zmq_recv_work"] = &kengine::Monitor::zmq_recv_work;
        type["zmq_recv_complete"] = &kengine::Monitor::zmq_recv_complete;
	}
	{
		sol::usertype<kengine::KEngine> type = lua.new_usertype<kengine::KEngine>("KEngine"
			,sol::constructors <
			kengine::KEngine ()
			> ()
		);
        type["app"] = &kengine::KEngine::app;
        type["render"] = &kengine::KEngine::render;
        type["scene_manager"] = &kengine::KEngine::scene_manager;
        type["ui"] = &kengine::KEngine::ui;
        type["monitor"] = &kengine::KEngine::monitor;
        type["lua_engine"] = &kengine::KEngine::lua_engine;
        type["init"] = &kengine::KEngine::init;
        type["update"] = &kengine::KEngine::update;
        type["quit"] = &kengine::KEngine::quit;
        type["on_view_size"] = &kengine::KEngine::on_view_size;
	}
	{
		lua.new_enum("Endian"
		,"Little", kengine::Endian::Little
		,"Big", kengine::Endian::Big
		);
	}
	{
		lua.new_enum("AssetType"
		,"TEXTURE", kengine::AssetType::TEXTURE
		,"SHADER", kengine::AssetType::SHADER
		,"MATERIAL", kengine::AssetType::MATERIAL
		,"MESH", kengine::AssetType::MESH
		,"MODEL", kengine::AssetType::MODEL
		,"PREFABS", kengine::AssetType::PREFABS
		);
	}
	{
		lua.new_enum("EventType"
		,"OnViewSize", kengine::EventType::OnViewSize
		,"OnUpdate", kengine::EventType::OnUpdate
		);
	}
	{
		lua.new_enum("GPUType"
		,"BYTE", kengine::GPUType::BYTE
		,"UNSIGNED_BYTE", kengine::GPUType::UNSIGNED_BYTE
		,"SHORT", kengine::GPUType::SHORT
		,"UNSIGNED_SHORT", kengine::GPUType::UNSIGNED_SHORT
		,"INT", kengine::GPUType::INT
		,"UNSIGNED_INT", kengine::GPUType::UNSIGNED_INT
		,"FLOAT", kengine::GPUType::FLOAT
		,"HALF_FLOAT", kengine::GPUType::HALF_FLOAT
		,"FIXED", kengine::GPUType::FIXED
		,"INT_2_10_10_10_REV", kengine::GPUType::INT_2_10_10_10_REV
		,"UNSIGNED_INT_2_10_10_10_REV", kengine::GPUType::UNSIGNED_INT_2_10_10_10_REV
		);
	}
	{
		lua.new_enum("PrimitiveType"
		,"POINTS", kengine::PrimitiveType::POINTS
		,"LINES", kengine::PrimitiveType::LINES
		,"LINE_LOOP", kengine::PrimitiveType::LINE_LOOP
		,"LINE_STRIP", kengine::PrimitiveType::LINE_STRIP
		,"TRIANGLES", kengine::PrimitiveType::TRIANGLES
		,"TRIANGLE_STRIP", kengine::PrimitiveType::TRIANGLE_STRIP
		,"QUADS", kengine::PrimitiveType::QUADS
		,"QUAD_STRIP", kengine::PrimitiveType::QUAD_STRIP
		,"PRIMITIVE_MAX", kengine::PrimitiveType::PRIMITIVE_MAX
		);
	}
	{
		lua.new_enum("ShaderDataType"
		,"INT", kengine::ShaderDataType::INT
		,"UINT", kengine::ShaderDataType::UINT
		,"FLOAT", kengine::ShaderDataType::FLOAT
		,"VEC2", kengine::ShaderDataType::VEC2
		,"VEC3", kengine::ShaderDataType::VEC3
		,"VEC4", kengine::ShaderDataType::VEC4
		,"MAT2", kengine::ShaderDataType::MAT2
		,"MAT3", kengine::ShaderDataType::MAT3
		,"MAT4", kengine::ShaderDataType::MAT4
		,"Color", kengine::ShaderDataType::Color
		,"MAX", kengine::ShaderDataType::MAX
		);
	}
	{
		lua.new_enum("PipelineStateType"
		,"CULL_FACE", kengine::PipelineStateType::CULL_FACE
		,"POLYGON_OFFSET_FILL", kengine::PipelineStateType::POLYGON_OFFSET_FILL
		,"LINE_WIDTH", kengine::PipelineStateType::LINE_WIDTH
		,"SCISSOR_STATE", kengine::PipelineStateType::SCISSOR_STATE
		,"SAMPLE_COVERAGE", kengine::PipelineStateType::SAMPLE_COVERAGE
		,"BLEND_MODE", kengine::PipelineStateType::BLEND_MODE
		,"DEPRH_TEST", kengine::PipelineStateType::DEPRH_TEST
		,"STENCIL_TEST", kengine::PipelineStateType::STENCIL_TEST
		,"DITHER", kengine::PipelineStateType::DITHER
		,"CLEAR_VALUE", kengine::PipelineStateType::CLEAR_VALUE
		,"FRAMEBUFFER_MASK", kengine::PipelineStateType::FRAMEBUFFER_MASK
		,"DEPTH_RANGE", kengine::PipelineStateType::DEPTH_RANGE
		,"VIEW_PORT", kengine::PipelineStateType::VIEW_PORT
		,"PIPELINE_STATE_TYPE_NUM", kengine::PipelineStateType::PIPELINE_STATE_TYPE_NUM
		);
	}
	{
		lua.new_enum("Face"
		,"NONE", kengine::Face::NONE
		,"FRONT", kengine::Face::FRONT
		,"BACK", kengine::Face::BACK
		,"FRONT_AND_BACK", kengine::Face::FRONT_AND_BACK
		);
	}
	{
		lua.new_enum("CompareFunc"
		,"NONE", kengine::CompareFunc::NONE
		,"NEVER", kengine::CompareFunc::NEVER
		,"ALWAYS", kengine::CompareFunc::ALWAYS
		,"LESS", kengine::CompareFunc::LESS
		,"GREATER", kengine::CompareFunc::GREATER
		,"EQUAL", kengine::CompareFunc::EQUAL
		,"LEQUAL", kengine::CompareFunc::LEQUAL
		,"GEQUAL", kengine::CompareFunc::GEQUAL
		,"NOTEQUAL", kengine::CompareFunc::NOTEQUAL
		);
	}
	{
		lua.new_enum("RenderBufferFormat"
		,"R8", kengine::RenderBufferFormat::R8
		,"R8I", kengine::RenderBufferFormat::R8I
		,"R8UI", kengine::RenderBufferFormat::R8UI
		,"R16I", kengine::RenderBufferFormat::R16I
		,"R16UI", kengine::RenderBufferFormat::R16UI
		,"R32I", kengine::RenderBufferFormat::R32I
		,"R32UI", kengine::RenderBufferFormat::R32UI
		,"RG8", kengine::RenderBufferFormat::RG8
		,"RG8I", kengine::RenderBufferFormat::RG8I
		,"RG8UI", kengine::RenderBufferFormat::RG8UI
		,"RG16I", kengine::RenderBufferFormat::RG16I
		,"RG16UI", kengine::RenderBufferFormat::RG16UI
		,"RG32I", kengine::RenderBufferFormat::RG32I
		,"RG32UI", kengine::RenderBufferFormat::RG32UI
		,"RGB8", kengine::RenderBufferFormat::RGB8
		,"RGB565", kengine::RenderBufferFormat::RGB565
		,"RGB_A1", kengine::RenderBufferFormat::RGB_A1
		,"RGB_A2", kengine::RenderBufferFormat::RGB_A2
		,"RGB", kengine::RenderBufferFormat::RGB
		,"RGB10_A2UI", kengine::RenderBufferFormat::RGB10_A2UI
		,"RGBA", kengine::RenderBufferFormat::RGBA
		,"RGBA4", kengine::RenderBufferFormat::RGBA4
		,"RGBA8", kengine::RenderBufferFormat::RGBA8
		,"RGBA8I", kengine::RenderBufferFormat::RGBA8I
		,"RGBA8UI", kengine::RenderBufferFormat::RGBA8UI
		,"RGBA16I", kengine::RenderBufferFormat::RGBA16I
		,"RGBA16UI", kengine::RenderBufferFormat::RGBA16UI
		,"RGBA32I", kengine::RenderBufferFormat::RGBA32I
		,"RGBA32UI", kengine::RenderBufferFormat::RGBA32UI
		,"SRGB8_ALPHA8", kengine::RenderBufferFormat::SRGB8_ALPHA8
		,"STENCIL_INDEX8", kengine::RenderBufferFormat::STENCIL_INDEX8
		,"DEPTH24_STENCIL8", kengine::RenderBufferFormat::DEPTH24_STENCIL8
		,"DEPTH32F_STENCIL8", kengine::RenderBufferFormat::DEPTH32F_STENCIL8
		,"DEPTH_COMPONENT", kengine::RenderBufferFormat::DEPTH_COMPONENT
		,"DEPTH_COMPONENT16", kengine::RenderBufferFormat::DEPTH_COMPONENT16
		,"DEPTH_COMPONENT24", kengine::RenderBufferFormat::DEPTH_COMPONENT24
		,"DEPTH_COMPONENT32F", kengine::RenderBufferFormat::DEPTH_COMPONENT32F
		);
	}
	{
		lua.new_enum("AttachmentPoint"
		,"DEPTH", kengine::AttachmentPoint::DEPTH
		,"STENCIL", kengine::AttachmentPoint::STENCIL
		,"DEPTH_STENCIL", kengine::AttachmentPoint::DEPTH_STENCIL
		,"COLOR_ATTACHMENT0", kengine::AttachmentPoint::COLOR_ATTACHMENT0
		,"COLOR_ATTACHMENT1", kengine::AttachmentPoint::COLOR_ATTACHMENT1
		,"COLOR_ATTACHMENT2", kengine::AttachmentPoint::COLOR_ATTACHMENT2
		,"COLOR_ATTACHMENT3", kengine::AttachmentPoint::COLOR_ATTACHMENT3
		,"COLOR_ATTACHMENT4", kengine::AttachmentPoint::COLOR_ATTACHMENT4
		,"COLOR_ATTACHMENT5", kengine::AttachmentPoint::COLOR_ATTACHMENT5
		,"COLOR_ATTACHMENT6", kengine::AttachmentPoint::COLOR_ATTACHMENT6
		,"COLOR_ATTACHMENT7", kengine::AttachmentPoint::COLOR_ATTACHMENT7
		,"COLOR_ATTACHMENT8", kengine::AttachmentPoint::COLOR_ATTACHMENT8
		,"COLOR_ATTACHMENT9", kengine::AttachmentPoint::COLOR_ATTACHMENT9
		);
	}
	{
		lua.new_enum("AttachmentType"
		,"TEXTURE", kengine::AttachmentType::TEXTURE
		,"RENDER_BUFFER", kengine::AttachmentType::RENDER_BUFFER
		);
	}
	{
		lua.new_enum("BindPointType"
		,"VAO", kengine::BindPointType::VAO
		,"Texture", kengine::BindPointType::Texture
		,"SSBO", kengine::BindPointType::SSBO
		,"UBO", kengine::BindPointType::UBO
		,"MAX", kengine::BindPointType::MAX
		);
	}
	{
		lua.new_enum("FrameBufferComponent"
		,"COLOR", kengine::FrameBufferComponent::COLOR
		,"DEPTH", kengine::FrameBufferComponent::DEPTH
		,"STENCIL", kengine::FrameBufferComponent::STENCIL
		,"COLOR_DEPTH", kengine::FrameBufferComponent::COLOR_DEPTH
		,"COLOR_STENCIL", kengine::FrameBufferComponent::COLOR_STENCIL
		,"DEPTH_STENCIL", kengine::FrameBufferComponent::DEPTH_STENCIL
		,"COLOR_DEPTH_STENCIL", kengine::FrameBufferComponent::COLOR_DEPTH_STENCIL
		);
	}
	{
		lua.new_enum("MonitorCommandType"
		,"Test", kengine::MonitorCommandType::Test
		,"Num", kengine::MonitorCommandType::Num
		);
	}
}
}
