#pragma once
#include "WndBase.h"
class OthelloWindow : public WndBase
{
public :
	void OnClose() override;

protected :
	void ProcessInput() override;
};