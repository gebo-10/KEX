#pragma once
#include"type.h"
namespace kengine {
	class CTree
	{
		struct Node {
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