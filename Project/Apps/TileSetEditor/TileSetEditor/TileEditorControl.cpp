#include "TileEditorControl.h"
#include "LabelControl.h"
#include "UI.h"
#include "BoolControl.h"
#include "TextBoxControl.h"
MapTile* TileEditorControl::CurTile = NULL;
MapLight* TileEditorControl::CurLight = NULL;
MapNode* TileEditorControl::CurNode = NULL;
TileEditorControl* TileEditorControl::Main = NULL;
Texture2D* NoTex = NULL;


TileEditorControl::TileEditorControl() {

	if (NoTex == NULL) {

		NoTex = new Texture2D("Edit/notile.png", false, false);

	}
	white = new Texture2D("Edit/white1.png", true);
	Main = this;

}

void TileEditorControl::SetLight(MapLight* light) {

	CurLight = light;
	Main->Mode = EditMode::Light;
	Main->Rebuild();
	

}

void TileEditorControl::SetNode(MapNode* node) {

	CurNode = node;
	Main->Mode = EditMode::Node;
	Main->Rebuild();

}

void TileEditorControl::SetTile(MapTile* tile) {

	CurTile = tile;
	Main->Mode = EditMode::Tile;
	Main->Rebuild();

}

void TileEditorControl::Rebuild()
{

	EditY = 35;
	ClearChild();
	Vec3 l;
	Vec3* ol;
	const char* Name = "";
	auto tc = [&](const char* t) {

		CurNode->SetName(t);

	};

	BoolControl* bb;
	auto bbAct = [&](bool bv) {

		CurLight->SetSpot(bv);

	};


	switch (Mode) {
	case EditMode::Node:

		Name = CurNode->GetName();

		

		AddString("Name",CurNode->GetName());
		


		break;
	case EditMode::Light:

		ol = CurLight->GetDiffusePtr();

	//	ol = &l;
		AddVec3("Diffuse", ol);
		AddFloat("Range", CurLight->GetRangePtr());
		AddFloat("SpotDir", CurLight->GetSpotDirPtr());
		AddFloat("SpotAngle", CurLight->GetSpotAnglePtr());
		bb = AddBool("SpotLight", CurLight->GetSpotPtr());

	
		bb->SetStateAct(bbAct);

		break;
	case EditMode::Tile:

		auto ctex = AddTexture("Color\n", CurTile->GetImage());
		auto ntex = AddTexture("Normal\n", CurTile->GetNormal());
		auto stex = AddTexture("Shadow\n", CurTile->GetShadow());
		auto cs = AddBool("Cast Shadows\n", CurTile->GetCastShadowsPtr());
		auto c = AddBool("Collider\n", CurTile->GetColliderPtr());

		auto csAct = [&](bool v) {
			CurTile->SetCastShadows(v);
			CurTile->Save();

		};

		auto cAct = [&](bool v) {

			CurTile->SetCollider(v);
			CurTile->Save();

		};

		cs->SetStateAct(csAct);
		c->SetStateAct(cAct);


		auto dropc = [&](void* d) {

			//Texture2D* tex = (Texture2D *) tex;
			
			CurTile->SetImage((Texture2D*)d);
			CurTile->Save();


		};

		auto dropn = [&](void* d) {

			CurTile->SetNormal((Texture2D*)d);
			CurTile->Save();
		};
			
		auto drops = [&](void* d) {

			CurTile->SetShadow((Texture2D*)d);
			CurTile->Save();
		};


		ctex->SetDropAct(dropc);
		ntex->SetDropAct(dropn);
		stex->SetDropAct(drops);

		break;

	}

}

void TileEditorControl::AddFloat(const char* name, float* v) {

	LabelControl* fl = new LabelControl();

	fl->SetText(name);
	fl->Set(5, EditY, 20, 20);
	

	TextBoxControl* fb = new TextBoxControl();

	fb->Set(55, EditY, 120, 25);

	fb->SetText(VString(v[0]).GetConst());

	fb->SetData(v);

	fl->SetText(name);

	auto fc = [&](TextBoxControl* tb, VString txt) {

		auto f = (float*)tb->GetData();

		f[0] = txt.ToFloat();

	};

	fb->SetChanged(fc);

	AddControl(fl);
	AddControl(fb);

	EditY += 35;
}

BoolControl* TileEditorControl::AddBool(const char* name, bool* b) {

	BoolControl* bc = new BoolControl;
	bc->SetText(name);
	bc->Set(5, EditY, 16, 16);
	bc->SetState(b[0]);
	AddControl(bc);
	EditY += 20;
	return bc;

}

UIControl* TileEditorControl::AddTexture(const char* name, Texture2D* tex)
{

	LabelControl* tLab = new LabelControl();

	tLab->SetText(name);
	tLab->Set(5, EditY, 20, 20);

	ImageDropControl* texc = NULL;

	if (tex != NULL) {
		texc = new ImageDropControl(tex);
	}
	else {
		texc = new ImageDropControl(NoTex);
	}
	texc->Set(60, EditY, 80, 80);

	texc->SetDrop(true);


	AddControl(texc);
	AddControl(tLab);

	EditY += 95;

	return (UIControl*)texc;

}

void TileEditorControl::Render() {

	UI::DrawTexture(white, GetX(), GetY(), GetW(), GetH(), 0.3f, 0.3f, 0.3f, 1.0);

}

void TileEditorControl::AddVec3(const char* name, Vec3* v) {


	auto xl = new LabelControl();
	auto yl = new LabelControl();
	auto zl = new LabelControl();

	auto xt = new TextBoxControl();
	auto yt = new TextBoxControl();
	auto zt = new TextBoxControl();

	xt->Set(25, EditY, 80, 25);
	yt->Set(125, EditY, 80, 25);
	zt->Set(230, EditY, 80, 25);

	xt->SetText(VString(v->X).GetConst());
	yt->SetText(VString(v->Y).GetConst());
	zt->SetText(VString(v->Z).GetConst());

	xt->SetData(v);
	yt->SetData(v);
	zt->SetData(v);

	auto xC = [&](TextBoxControl* tb,VString txt) {

		auto v = (Vec3*)tb->GetData();

		float fv = txt.ToFloat();

		v->X = fv;


	//	printf("TexTchanged:");
	//	printf(txt.GetConst());
	//	printf(":\n");


	};

	auto yC = [&](TextBoxControl* tb, VString txt) {

		auto v = (Vec3*)tb->GetData();

		float fv = txt.ToFloat();

		v->Y = fv;

	};

	auto zC = [&](TextBoxControl* tb, VString txt) {

		auto v = (Vec3*)tb->GetData();

		float fv = txt.ToFloat();

		v->Z = fv;

	};

	xt->SetChanged(xC);
	yt->SetChanged(yC);
	zt->SetChanged(zC);


	xl->SetText("X");
	yl->SetText("Y");
	zl->SetText("Z");

	AddControl(xt);
	AddControl(yt);
	AddControl(zt);

	AddControl(xl);
	AddControl(yl);
	AddControl(zl);

	xl->Set(5, EditY+5,20,20);
	yl->Set(110, EditY+5, 20, 20);
	zl->Set(215, EditY+5, 20, 20);

	EditY += 40;



}

void TileEditorControl::AddString(const char* name, const char* init)
{

	LabelControl* nNode = new LabelControl();
	nNode->Set(5, EditY+5, 20, 20);
	nNode->SetText(name);

	TextBoxControl* editB = new TextBoxControl();

	editB->Set(55, EditY, 120, 25);
	
	editB->SetText(init);


	editB->SetData((void*)init);


	auto nChanged = [&](TextBoxControl* tb, VString txt) {


		char* dat = (char*)tb->GetData();
		for (int i = 0; i < txt.Len(); i++) {
			dat[i] = txt.GetChar(i);
		}
		dat[txt.Len()] = "\0"[0];

	};

	editB->SetChanged(nChanged);


	AddControl(editB);
	AddControl(nNode);
	EditY += 35;


}