#include <iostream>
#include "Render.h"
#include "System.h"
#include "Components.h"
#include "ECSFunc.h"

int main()
{	
	if (!GameInit() || !RenderInit())
	{
		return 0;
	}

	std::unique_ptr<Manager> manager = ECSInit();
	while (true)
	{
		manager->refresh();

		if (!GameIter(manager))
			break;
		if (!Render(manager))
			break;
	}
	

	ECSStop(std::move(manager));
	GameStop();
	RenderStop();
}
