#pragma once
#include"type.h"
namespace kengine {
	class CTree
	{
		struct Node {
			void* data;
			Node* father;
			std::vector<Node*> children;
		};
	public:
		Node root;
		CTree()
		{
		}

		~CTree()
		{
		}

	private:

	};
}