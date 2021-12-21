#pragma once
#include <kengine/core/base/base.h>
namespace kengine::animation {
	enum class AnimatorState {
		Playing,
		Stoped,
		Paused,
	};
	enum class AnimatorMode {
		Once,
		Loop,
		PingPong,
	};
	class Animator;
	struct Channel
	{
		float start;
		float scale;
		shared_ptr<Animator> animator;
	};
	typedef std::function<void(float t)> Modify;
	struct AnimatorKey{
		float time;
	};
	class Animator
	{
	public:
		AnimatorState state;
		AnimatorMode mode;
		float time;
		float scale;
		float current_time;
		
		std::vector<Channel> channels;
		Modify modify;
		std::function<void()> complete;
		Animator(Modify m):modify(m)
		{
		}

		~Animator()
		{
		}
		
		void play(){}
		void stop() {}
		void pause() {}

		void update(){}

		void add_channel(shared_ptr<Animator> animator, float start=0, float scale=1){}
	};
	typedef shared_ptr<Animator> AnimatorPtr;
}