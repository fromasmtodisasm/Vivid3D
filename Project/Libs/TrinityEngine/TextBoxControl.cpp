#include "pch.h"
#include "TextBoxControl.h"
#include "UI.h"
#include "strings.h"

TextBoxControl::TextBoxControl() {

	Bg = new Texture2D("Edit/white1.png", false);

}

void TextBoxControl::Render() {

	UI::DrawTexture(Bg, GetX(), GetY(), GetW(), GetH(), 0.2f, 0.2f, 0.2f, 1.0f);

	UI::RenderText(GetX() + 2, GetY() + 3, GetText(), 1, 1, 1, 1);



	if (Active) {

		//exit(5);
		if (caratOn) {
			int mx = 5;

			VString ct(GetText());

			

			int cx = 0;

			if (caratX > 0) {

				ct = ct.SubString(0, caratX);

				//printf("CT:%d\n", ct.Len());


				cx = UI::TextWidth(ct.GetConst());
				printf("TXT:");
				printf(ct.GetConst());
				printf(" CL:%d\n", cx);


					
			}

			UI::DrawTexture(Bg, GetX() + 5+cx, GetY() + 2, 2, GetH() - 4, 0, 0, 0, 1.0f);

		}

	}

};

void TextBoxControl::Update() {

	int time = clock();

	if (time > lastCarat + 250) {

		lastCarat = time;
		if (caratOn) {
			caratOn = false;
		}
		else {
			caratOn = true;
		}



	}


};


void TextBoxControl::KeyPressed(int key,bool shift) {

	if (key == GLFW_KEY_LEFT_ALT) {
		return;
	}
	if (key == GLFW_KEY_RIGHT_SHIFT || key == GLFW_KEY_LEFT_SHIFT)
	{
		return;
	}
	if (key == GLFW_KEY_ENTER) {
		if (TextChanged != NULL) {

			TextChanged(this,VString(GetText()));

		}
		return;
	}
	Txt = VString(GetText());
	if (key == GLFW_KEY_RIGHT) {

		caratX++;
		if (caratX > Txt.Len()) {

			caratX--;

		}

	//	printf("CarratX:%d",caratX);
//		printf("\n");
		return;

	}

	if (key == GLFW_KEY_LEFT) {

		caratX--;
		if (caratX < 0)
		{

			caratX = 0;

		}
		return;


	}

	if (key == GLFW_KEY_DELETE) {

		VString t3(GetText());

		if (caratX == t3.Len())
		{
			return;
		}
		if (caratX == 0 && t3.Len() == 0) {
			return;
		}

		if (caratX > 0) {
			VString d1 = t3.SubString(0, caratX);
			VString d2 = t3.SubString(caratX + 1, t3.Len()-caratX-1);
			d1.Add(d2);

			SetText(d1.GetConst());
			return;


		}
		if (caratX == 0) {

			VString ns(GetText());
			
			if (ns.Len() > 1) {
				ns = ns.SubString(1, ns.Len() - 1);
				SetText(ns.GetConst());
				return;

			}
			else {

				SetText(VString("").GetConst());
				return;

			}


		}

	}

	if (key == GLFW_KEY_BACKSPACE) {

		VString tmp(GetText());

		if (caratX == 0)
		{
			return;
		}
		if (caratX == tmp.Len())
		{
			if (tmp.Len() > 1)
			{
				tmp = tmp.SubString(0, caratX - 1);
				SetText(tmp.GetConst());
				caratX--;
				return;
			}
			else {
				SetText(VString("").GetConst());
				caratX = 0;
				return;
			}
		}
		else
		{
			VString t1 = tmp.SubString(0, caratX - 1);
			VString t2 = tmp.SubString(caratX,tmp.Len()-caratX);
			t1.Add(t2);
			SetText(t1.GetConst());
			caratX--;
			return;
		}


		return;
	}

	int md =0;

	if (shift) {
		md = 1;
	}
	else {
		md = 0;
	}
	const char* chr = KeyToChar(key, md);
		
	const char* txt = GetText();



	VString tx2(txt);
	VString tx1(chr);

	if (tx2.Len() == caratX)
	{

		tx2.Add(chr);

		SetText(tx2.GetConst());
		caratX++;
	}
	else {

		VString s1(tx2.SubString(0, caratX));
		s1.Add(tx1);
		s1.Add(tx2.SubString(caratX,-1));

		SetText(s1.GetConst());
		caratX++;

	}

	/*
	char* ns = (char*)malloc(350);

	strcpy(ns, txt);

	strcat(ns, chr);

	SetText(ns);

	//strcat((char*)txt, chr);
	

	printf("Key:");
	printf(chr);
	printf("\n");
	*/


};