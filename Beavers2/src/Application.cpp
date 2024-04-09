#include <iostream>
#include "Render.h"
#include "System.h"
#include "ECSManager.h"

int main()
{
	if (!ECSInit() || !GameInit() || !RenderInit())
	{
		return 0;
	}

	while (true)
	{
		if (!GameIter())
			break;

		if (!Render())
			break;
	}

	GameStop();
	RenderStop();
	ECSStop();
}