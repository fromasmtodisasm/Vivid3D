#pragma once
#include "MapNode.h"
#include "LScript.h"

class NodeServer
{
public:
	NodeServer(const char* path);
	int NodeCount() {

		return Nodes.size();

	}

	MapNode* GetNode(int i)
	{
		return Nodes[i];
	}

private:
	std::vector<MapNode*> Nodes;
};

