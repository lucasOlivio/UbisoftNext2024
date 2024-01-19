#include "Core/EditorEngine.h"

int main()
{
	using namespace MyEngine;

	Editor editor = Editor();

	editor.LoadConfigurations();

	// TODO: This would be better comming from command args?
	const std::string INITIAL_SCENE = "scene01.json";
	editor.Init();

	editor.Run(INITIAL_SCENE, false);
}