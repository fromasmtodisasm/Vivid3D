#include "pch.h"
#include "NodeServer.h"
#include <filesystem>

namespace fs = std::filesystem;

NodeServer::NodeServer(const char* path) {

	Nodes.resize(0);

	std::string p = std::string(path);

	for (const auto& entry : fs::directory_iterator(p))
	{

		std::string npath = entry.path().string();

		printf("Scanning node:");
		printf(npath.c_str());
		printf("\n");

		LScript* ls = new LScript();
		ls->RunFile(npath.c_str());

		ls->PushCall("GetNodeName");
		ls->Call(0, 1);
		const char * name =  ls->GetString(-1);
		ls->Pop(1);

		printf("Node Name:");
		printf(name);
		printf("|\n");

		ls->PushCall("GetNodeImage");
		ls->Call(0, 1);
		const char* imgPath = ls->GetString(-1);
		ls->Pop(1);

		Texture2D* nimg = new Texture2D(imgPath, true, true);

		ls->PushCall("GetNodeSize");
		ls->Call(0, 2);
		int nW = ls->GetInt(-2);
		int nH = ls->GetInt(-1);
		ls->Pop(2);

		MapNode* base = new MapNode();
		base->SetName(name);
		base->SetLS(ls);
		base->SetImage(nimg);
		base->SetSize(nW, nH);
		Nodes.push_back(base);

	}



};