#pragma once
#include "VerticalSplitterControl.h"
#include "EditorThirdSplit.h"
#include "EditorContentBrowser.h"
class EditorSecondSplit : public VerticalSplitterControl
{
public:
	EditorSecondSplit();
	
	static const char* ContentPath;

private:

	EditorThirdSplit* ThirdSplit;
	EditorContentBrowser* Browser;

};

