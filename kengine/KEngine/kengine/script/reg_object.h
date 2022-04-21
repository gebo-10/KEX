#include "auto_registe.h"
#include <D:/KEX/kengine/KEngine/kengine/scene/object.h>
void reg_object.h(sol::table& lua) {
	{
		sol::usertype<kengine::Component> type = lua.new_usertype<kengine::Component>("kengine::Component",
			sol::constructors <
			kengine::Component (kengine::ComponentType)
			> ()
		);
        type["type"] = &kengine::Component::type;
        type["go"] = &kengine::Component::go;
        type["on_attach"] = &kengine::Component::on_attach;
        type["on_dettach"] = &kengine::Component::on_dettach;
	}
	{
		sol::usertype<kengine::Transform> type = lua.new_usertype<kengine::Transform>("kengine::Transform",
			sol::base_classes, sol::bases<kengine::Component>()
			sol::constructors <
			kengine::Transform ()
			> ()
		);
        type["local_dirty"] = &kengine::Transform::local_dirty;
        type["t"] = &kengine::Transform::t;
        type["r"] = &kengine::Transform::r;
        type["s"] = &kengine::Transform::s;
        type["mat_local"] = &kengine::Transform::mat_local;
        type["update_local_matrix"] = &kengine::Transform::update_local_matrix;
        type["matrix"] = &kengine::Transform::matrix;
        type["translate"] = &kengine::Transform::translate;
        type["rotate"] = &kengine::Transform::rotate;
        type["scale"] = &kengine::Transform::scale;
        type["set_translate"] = &kengine::Transform::set_translate;
        type["set_rotate"] = &kengine::Transform::set_rotate;
        type["set_scale"] = &kengine::Transform::set_scale;
	}
	{
		sol::usertype<kengine::MeshRender> type = lua.new_usertype<kengine::MeshRender>("kengine::MeshRender",
			sol::base_classes, sol::bases<kengine::Component>()
			sol::constructors <
			kengine::MeshRender ()
			> ()
		);
        type["mesh"] = &kengine::MeshRender::mesh;
        type["material"] = &kengine::MeshRender::material;
        type["instance_count"] = &kengine::MeshRender::instance_count;
	}
	{
		sol::usertype<kengine::SRTKey> type = lua.new_usertype<kengine::SRTKey>("kengine::SRTKey",
		);
        type["time"] = &kengine::SRTKey::time;
        type["srt"] = &kengine::SRTKey::srt;
	}
	{
		sol::usertype<kengine::SRTKeyAnimation> type = lua.new_usertype<kengine::SRTKeyAnimation>("kengine::SRTKeyAnimation",
		);
        type["duration"] = &kengine::SRTKeyAnimation::duration;
        type["ticks_per_second"] = &kengine::SRTKeyAnimation::ticks_per_second;
	}
	{
		sol::usertype<kengine::BoneWeight> type = lua.new_usertype<kengine::BoneWeight>("kengine::BoneWeight",
		);
        type["bone_id"] = &kengine::BoneWeight::bone_id;
        type["weight"] = &kengine::BoneWeight::weight;
	}
	{
		sol::usertype<kengine::VertexBoneData> type = lua.new_usertype<kengine::VertexBoneData>("kengine::VertexBoneData",
		);
        type["weights"] = &kengine::VertexBoneData::weights;
	}
	{
		sol::usertype<kengine::Bone> type = lua.new_usertype<kengine::Bone>("kengine::Bone",
		);
        type["dirty"] = &kengine::Bone::dirty;
        type["bone_id"] = &kengine::Bone::bone_id;
        type["offset_matrix"] = &kengine::Bone::offset_matrix;
        type["local_matrix"] = &kengine::Bone::local_matrix;
        type["animation_matrix"] = &kengine::Bone::animation_matrix;
        type["global_matrix"] = &kengine::Bone::global_matrix;
	}
	{
		sol::usertype<kengine::MeshSkin> type = lua.new_usertype<kengine::MeshSkin>("kengine::MeshSkin",
			sol::base_classes, sol::bases<kengine::Component>()
			sol::constructors <
			kengine::MeshSkin ()
			> ()
		);
        type["mesh"] = &kengine::MeshSkin::mesh;
        type["compute_material"] = &kengine::MeshSkin::compute_material;
        type["global_inverse_matrix"] = &kengine::MeshSkin::global_inverse_matrix;
        type["vertex_size"] = &kengine::MeshSkin::vertex_size;
        type["event_id"] = &kengine::MeshSkin::event_id;
        type["matrix_buffer"] = &kengine::MeshSkin::matrix_buffer;
        type["on_attach"] = &kengine::MeshSkin::on_attach;
        type["init"] = &kengine::MeshSkin::init;
        type["set_mesh"] = &kengine::MeshSkin::set_mesh;
        type["update"] = &kengine::MeshSkin::update;
        type["update_animation"] = &kengine::MeshSkin::update_animation;
        type["interpolate_srt"] = &kengine::MeshSkin::interpolate_srt;
        type["update_bone_matrix"] = &kengine::MeshSkin::update_bone_matrix;
	}
	{
		sol::usertype<kengine::Light> type = lua.new_usertype<kengine::Light>("kengine::Light",
			sol::base_classes, sol::bases<kengine::Component>()
			sol::constructors <
			kengine::Light ()
			> ()
		);
        type["type"] = &kengine::Light::type;
        type["accept_cull"] = &kengine::Light::accept_cull;
        type["ambient"] = &kengine::Light::ambient;
        type["diffuse"] = &kengine::Light::diffuse;
        type["specular"] = &kengine::Light::specular;
        type["constant"] = &kengine::Light::constant;
        type["linear"] = &kengine::Light::linear;
        type["quadratic"] = &kengine::Light::quadratic;
        type["cutoff"] = &kengine::Light::cutoff;
	}
	{
		sol::usertype<kengine::Object> type = lua.new_usertype<kengine::Object>("kengine::Object",
			sol::constructors <
			kengine::Object ()
			> ()
		);
        type["active"] = &kengine::Object::active;
        type["parent"] = &kengine::Object::parent;
        type["add_component"] = &kengine::Object::add_component;
        type["get_component"] = &kengine::Object::get_component;
	}
}
