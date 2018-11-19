#include "stdafx.h"
#include "HPView.h"


using namespace MyDirectX;
HPView::HPView(IHP* hp, DXText* text)
{
	mHPObject = hp;
	mViewText = text;
}

HPView::~HPView()
{
}

void HPView::Update()
{
	std::wstringstream ws;
	ws.precision(6);
	ws << mHPObject->GetHP();
	auto wString = ws.str();
	auto pString = wString.c_str();
	mViewText->UpdateText(pString);
	ws.clear();
}
