#include "Core/AppEngine.h"

int main()
{
	using namespace MyEngine;

	Application app = Application();

	app.LoadConfigurations();

	// TODO: This would be better comming from command args?
	const std::string INITIAL_SCENE = "scene01.json";
	app.Init();

	app.Run(INITIAL_SCENE);
}