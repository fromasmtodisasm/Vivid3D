#include "TileSetApp.h"
#include "UITheme.h"
#include "UITheme_Neon.h"
#include "ContentBrowserControl.h"
#include "MainMenuControl.h";
#include "FileRequestorControl.h"
#include "UI.h"
#include "Utils.h"
#include "MapNode.h"
#include "TileEditorControl.h"
#include "VideoPlayerControl.h"
#include "ToolsControl.h"
#include "TreeViewControl.h"
#include "EditorGlobal.h"
#include "NumericControl.h"
#include "BakeMapWin.h"

HorizontalSplitterControl* HSplit1;
HorizontalSplitterControl* HSplit2;
HorizontalSplitterControl* HSplitB;
VerticalSplitterControl* VSplit1;
MainMenuControl* Menu;
MapEditControl* MapEdit;
TileEditorControl* Editor;

ContentBrowserControl* Browser;

const char* ContentPath;




TileSetApp::TileSetApp() {


}

NodeServer* TileSetApp::NodeServe = NULL;


void CreateSplitters(UI* ui) {

	ContentPath = "C:\\Content\\";

	

	Menu = new MainMenuControl();

	Menu->Set(0, 0, ui->GetW(), 23);

	auto proj = Menu->AddItem("Project\n");
	auto node = Menu->AddItem("Node\n");
	auto customNodes = Menu->AddItem("Custom Nodes");

	auto node_newlight = node->AddItem("New Light");
	auto node_new = node->AddItem("New Node");
	//auto node_newTerm = node->AddItem("New Terminal");


	auto n_newTerm = [&] {



	};

	auto n_newLight = [&] {


		MapLight* l = new MapLight();
		l->SetPos(40, 40, 1);
		EditorGlobal::MapEdit->GetMap()->AddLight(l);
		EditorGlobal::RebuildSceneTree();
		l->SetIcon(new Texture2D("edit/light1.png", true, false));
	};

	auto n_newNode = [&] {

		MapNode* node = new MapNode();
		node->SetPos(40, 40, 1);


		EditorGlobal::MapEdit->GetMap()->AddNode(node);
		printf("Added nonde.\n");
		EditorGlobal::RebuildSceneTree();
	};


	node_new->SetAction(n_newNode);
	node_newlight->SetAction(n_newLight);

	auto proj_new = proj->AddItem("New Project\n");
	auto proj_loadMap = proj->AddItem("Load Map\n");
	auto proj_saveMap = proj->AddItem("Save Map\n");

	auto p_loadMap = [&] {

		auto filer = new FileRequestorControl();

		filer->Set(20, 20, 300, 400);
		filer->SetText("Load Map..\n");

		filer->SetDir(ContentPath);

		UI::Main->SetTop(filer);

		auto aSel = [&](const char* path) {

			printf("Selected:");
			printf(path);
			printf("|\n");
			//while (true) {};
			EditorGlobal::MapEdit->GetMap()->LoadMap(path);
			UI::Main->SetTop(NULL);
			EditorGlobal::RebuildSceneTree();

		};

		filer->SetSelected(aSel);


	};

	auto p_saveMap = [&] {


		auto filer = new FileRequestorControl();

		filer->Set(20, 20, 300, 400);
		filer->SetText("Save Map..\n");

		filer->SetDir(ContentPath);

		UI::Main->SetTop(filer);

		auto aSel = [&](const char* path) {

			printf("Selected:");
			printf(path);
			printf("|\n");
			//while (true) {};
			EditorGlobal::MapEdit->GetMap()->SaveMap(path);
			UI::Main->SetTop(NULL);

		};

		filer->SetSelected(aSel);



	};
		
	proj_loadMap->SetAction(p_loadMap);
	proj_saveMap->SetAction(p_saveMap);


	auto newProj = [&]{
		


	};

	proj_new->SetAction(newProj);

	//Menu->


	VSplit1 = new VerticalSplitterControl;



	VSplit1->Set(0, 0, ui->GetW(), ui->GetH());
	VSplit1->SetSplit(ui->GetH()-200);

	HSplit1 = new HorizontalSplitterControl;

	HSplit1->Set(0, 0, ui->GetW(), VSplit1->GetTopH());

	HSplit1->SetSplit(180);

	HSplitB = new HorizontalSplitterControl;

	int ra = VSplit1->GetSplit()-5;

	HSplitB->Set(0, 0, ui->GetW(),ui->GetH()-ra);

	VSplit1->SetBottom(HSplitB);

	HSplitB->SetSplit(160);

	Browser = new ContentBrowserControl;

	Browser->Set(0, 0, HSplitB->GetW() - HSplitB->GetSplit() - 5, HSplitB->GetH());

	Browser->ScanDir(ContentPath);

	HSplitB->SetRight(Browser);

	VSplit1->SetTop(HSplit1);

	HSplit2 = new HorizontalSplitterControl;

	HSplit2->Set(0, 0, HSplit1->GetRightW(), VSplit1->GetTopH());

	HSplit1->SetRight(HSplit2);

	TreeViewControl* SceneTree = new TreeViewControl;

	HSplit1->SetLeft(SceneTree);

	SceneTree->Set(0, 0, HSplit1->GetSplit(), HSplit1->GetH());

	auto sceneRoot = new TreeItem();
	sceneRoot->SetText("Scene");
	SceneTree->SetRoot(sceneRoot);

	auto map = sceneRoot->AddItem("Map");

	EditorGlobal::SceneTree = SceneTree;
	


	//SceneTree->AddItem("Scene");


	MapEdit = new MapEditControl(32, 32, 64,64);

	auto tools = new ToolsControl();

	EditorGlobal::MapEdit = MapEdit;

	MapEdit->AddControl(tools);
	
	MapEdit->Set(0, 0, HSplit2->GetSplit() - 5, HSplit2->GetH());

	HSplit2->SetLeft(MapEdit);

	HSplit2->SetSplit(HSplit1->GetRightW() - 350);

	tools->Set(0, 24, HSplit2->GetSplit() - 5, 25);

	auto mClear = tools->AddItem("Clear\n");
	auto mFill = tools->AddItem("Fill\n");
	auto mPaste = tools->AddItem("Paste\n");
	
	auto layerN = new NumericControl();
	layerN->Set(0, 3, 100, 20);
	
	tools->AddItem(layerN);
	auto tBake = tools->AddItem("Bake Map\n");

	auto tPreview = tools->AddItem("Preview Map\n");

	auto aPreview = [&] {

		TileSetApp::Main->previewMode = true;
		EditorGlobal::MapEdit->GetMap()->Compile();

	};

	auto aBake = [&] {

		auto win = new BakeMapWin();
		win->Set(150, 150, 300, 250);
		win->SetText("Bake Map");
		UI::Main->SetTop(win);
		//ui->SetTop(win);

	};

	tBake->SetAction(aBake);
	tPreview->SetAction(aPreview);

	auto numC = [&](int n) {

		printf("Layer:%d \n", n);
		EditorGlobal::MapEdit->Main->SetLayer(n);

	};

	layerN->SetChanged(numC);

	auto aClear = [&] {

		MapEditControl::Main->SetMode(MapEditMode::Clear);

	};

	auto aFill = [&] {
		MapEditControl::Main->SetMode(MapEditMode::Fill);
		//exit(1);

	};

	mClear->SetAction(aClear);

	mFill->SetAction(aFill);

	

	auto aPaste=[&]{
		MapEditControl::Main->SetMode(MapEditMode::Paste);

	};

	mPaste->SetAction(aPaste);

	//mFill->SetAction(aFill);
	

	Editor = new TileEditorControl();

	Editor->Set(0, 0, ui->GetW() - HSplit2->GetSplit() - 5, HSplit2->GetH());

	HSplit2->SetRight(Editor);


	ui->GetRoot()->AddControl(VSplit1);
	//ui->SetMenu(Menu);
	ui->GetRoot()->AddControl(Menu);

	EditorGlobal::RebuildSceneTree();

	auto me_ChangedNode = [&](MapNode* node) {

		if (node->GetType() == NodeType::TypeLight)
		{
			MapLight* l = (MapLight*)node;
			EditorGlobal::TileEd->SetLight(l);
		}
	};

	MapEdit->SetChangedNode(me_ChangedNode);

	NodeServer* nodeServe = new NodeServer("c:\\content\\id\\nodes\\");

	int nc = nodeServe->NodeCount();

	TileSetApp::NodeServe = nodeServe;

	for (int i = 0; i < nc; i++) {

		auto node = nodeServe->GetNode(i);

		auto cn = customNodes->AddItem(node->GetName());

		cn->Data = nodeServe;
		cn->DataInt = i;

		auto aCn = [&](MenuItem* item) {

			//printf("Num:%d\n", item->DataInt);

			MapNode* bn = TileSetApp::NodeServe->GetNode(item->DataInt);
			MapNode* nn = bn->Clone();
			EditorGlobal::MapEdit->GetMap()->AddNode(nn);

			int cx, cy;

			Vec3 p = EditorGlobal::MapEdit->GetMap()->GetCam();

			p.X += 200;
			p.Y += 200;

			nn->SetPos(p);


			



		};

		cn->act2 = aCn;

		//cn->SetAction(aCn);


	}




}

TileSetApp* TileSetApp::Main = NULL;

void TileSetApp::Init() {

	Main = this;
	const char* ContentPath = "C:/Projects";

	UITheme_Neon* theme = new UITheme_Neon();

	UI::SetTheme(theme);

	ui = new UI(Width(), Height());

	CreateSplitters(ui);
	shadowBuf = new kFrameBuffer(Application::WinW, Application::WinH);

	Application::Main->InitCL();
	
	/*

	HorizontalSplitterControl * Split = new HorizontalSplitterControl;
	
	
	Split->Set(0, 0, Width(), Height());
	

	MainMenuControl* Menu = new MainMenuControl;

	auto m_file = Menu->AddItem("Files/n");

	auto f_addimg = m_file->AddItem("Add Image/n");
	auto f_addfolder = m_file->AddItem("Add Folder/n");

	auto a_addimg = [&] {

		FileRequestorControl* filer = new FileRequestorControl;

		filer->SetText("FILER/n");

		filer->Set(50, 50, 350, 500);

		filer->SetDir(ContentPath);

		ui->SetTop(filer);

	};

	f_addimg->SetAction(a_addimg);


	auto map = new MapEditControl(16, 16, 64, 64);

	//return;
	Split->SetSplit(Width()-300);


	Split->SetLeft(map);

	

	map->AddControl(Menu);

	//return;

	
	//eturn;

	Menu->Set(0, 0, Width(), 25);
	
	//return;

	ui->GetRoot()->AddControl(Split);
//	while (true) {};
*/
	return;
};

void TileSetApp::Update() {

	ui->Update();

};

void TileSetApp::Render() {

	if (previewMode == true) {

		Map* map = EditorGlobal::MapEdit->GetMap();
	//	shadowBuf->bind();
	//	glClearColor(1, 1, 1, 1);
	///	glClear(GL_COLOR_BUFFER_BIT);
	//	map->RenderShadows1();
	//	shadowBuf->unbind();

	//	map->RenderShadows2(shadowBuf->GetBB());
		map->RenderCompiled();

	}
	else {
		ui->Render();
	}
};