#pragma once
namespace gebo{
	enum class ObjectType{

	}
	
	templete<typename T>
	struct Ref{
		T * ptr;
		Ref(void * p){
			ptr=(T*)p;
		}
		~Ref(){
			ID * id=(ID *) ptr;
			id->release();
		}

		templete<typename T>
		static Ref<T> make(){
			auto ptr=std::malloc(sizeof(T));
			return Ref<T>(ptr);
		}
	}

	struct ID{
	private:
		uint32 sign;// | type | refcount | deleted |  changed | 
	public:
		ObjectType type();
		bool deleted();
		void release(){
			refcount--;
			if(refcount==0){
				free();
			}
		}
		void retain(){
			refcount++;
		}
		static IsNull(void ** pptr){
			void * ptr=*pptr;
			if(ptr == nullptr) return true;
			ID * id=(ID *) ptr;
			if(id.deleted()){
				*pptr=nullptr;
				release();
			}
		}
	}

	struct Buffer{
		ID id;
		void * memery;
		uint32 size;
	}
}