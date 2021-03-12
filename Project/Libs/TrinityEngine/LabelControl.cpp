#include "pch.h"
#include "LabelControl.h"
#include "UI.h"
#include "Texture2D.h"
#include "UITheme.h"
void LabelControl::Render() {

	UI::RenderText(GetX(), GetY(), GetText(), 1, 1, 1, 1);
}