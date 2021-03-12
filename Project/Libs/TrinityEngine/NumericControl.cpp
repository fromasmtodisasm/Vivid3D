#include "pch.h"
#include "NumericControl.h"

NumericControl::NumericControl() {



}

void NumericControl::Resized() {

	if (Up == NULL) {

		Up = new ButtonControl();
		Up->Set(0, 0, 16, 20);
		Down = new ButtonControl();
		Down->SetText("\\/");
		Up->SetText("/\\");
		Down->Set(GetW() - 16, 0, 16, 20);
		Num = new TextBoxControl();
		Num->Set(18, 0, GetW() - 36, 20);
		Num->SetText("0");
		AddControl(Up);
		AddControl(Down);
		AddControl(Num);
		Up->SetData((void*)Num);
		Down->SetData((void*)Num);
		auto upB = [&](void* data) {

			TextBoxControl* c = (TextBoxControl*)data;
			CNum++;
			VString ns(CNum);
			c->SetText(ns.GetConst());
			actChanged(CNum);

		};
		auto downB = [&](void* data) {

			TextBoxControl* c = (TextBoxControl*)data;
			CNum--;
			if (CNum < 0) CNum = 0;
			VString ns(CNum);
			c->SetText(ns.GetConst());
			actChanged(CNum);

		};

		Up->SetActData(upB);
		Down->SetActData(downB);
	}

}