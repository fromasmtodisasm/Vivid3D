#include "BakeMapWin.h"
#include "LabelControl.h"
#include "EditorGlobal.h"
BakeMapWin::BakeMapWin() {

}

void BakeMapWin::Resized() {

	WindowControl::Resized();

	if (tbWidth == NULL) {

		LabelControl* lW;
		LabelControl* lH;

		lW = new LabelControl();
		lW->Set(5, 30, 20, 20);
		lW->SetText("Width");

		lH = new LabelControl();
		lH->Set(5, 60, 20, 20);
		lH->SetText("Height");

		tbWidth = new TextBoxControl();
		tbWidth->Set(60, 30, 90, 25);
		tbWidth->SetText("2048");

		tbHeight = new TextBoxControl();
		tbHeight->Set(60, 60, 90, 25);
		tbHeight->SetText("2048");

		AddControl(lW);
		AddControl(lH);

		AddControl(tbWidth);
		AddControl(tbHeight);

		tbBlur = new TextBoxControl();
		tbBlur->Set(60, 90, 90, 25);
		tbBlur->SetText("0.7f");

		auto blab = new LabelControl();
		blab->Set(5, 90, 20, 20);
		blab->SetText("Blur");

		AddControl(blab);
		AddControl(tbBlur);

		bBake = new ButtonControl();
		bBake->Set(15, 130, 90, 25);
		bBake->SetText("Bake");

		auto aBake = [&] {

			VString sw(tbWidth->GetText());
			VString sh(tbHeight->GetText());
			VString sb(tbBlur->GetText());

			int ww = sw.ToInt();
			int hh = sh.ToInt();
			float bf = sb.ToFloat();
			if (bf < 0.0001f)
			{
				bf = 0.0001f;
			}
			if (bf > 20.0f)
			{
				bf = 20.0f;
			}

			printf("Baking map. MapW:%d MapH:%d\n", ww, hh);

			EditorGlobal::MapEdit->Main->GetMap()->BakeShadows(ww,hh,bf);

		};

		bBake->SetAction(aBake);

		AddControl(bBake);

	}
}