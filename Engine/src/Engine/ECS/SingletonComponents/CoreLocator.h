#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class CoreLocator
	{
	public:
		static ConfigPathComponent* GetConfigPath();
		static FrameCounterComponent* GetFrameCounter();
		static KeyInputComponent* GetKeyInput();
		static MouseInputComponent* GetMouseInput();
		static StateComponent* GetState();

		static void SetConfigPath(ConfigPathComponent* pConfigPath);
		static void SetFrameCounter(FrameCounterComponent* pFrameCounter);
		static void SetKeyInput(KeyInputComponent* pKeyInput);
		static void SetMouseInput(MouseInputComponent* pMouseInput);
		static void SetState(StateComponent* pState);

		static void Clear();

	private:
		static ConfigPathComponent* m_pConfigPath;
		static FrameCounterComponent* m_pFrameCounter;
		static KeyInputComponent* m_pKeyInput;
		static MouseInputComponent* m_pMouseInput;
		static StateComponent* m_pState;
	};
}
