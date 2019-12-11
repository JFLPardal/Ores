#pragma once
#include "IUIBar.h"

class FillBar : public IUIBar
{
public:
	FillBar(int screenCoordX, int screenCoordY);
	~FillBar();
	
	void Fill() override;
private:

};