# Game Systems

## Core Systems

- FrameSystem
Responsible for keeping track of current frames and FPS.

- StateSystem
Manages the game state, facilitating transitions between different game states.

- CoreSystem
Provides all the systems required for each game states.

- ParentSystem
Handles parent-child relationships between entities for hierarchical transformations.

- MediaPlayerSystem
Manages multimedia playback, handling sound playback and keeping track of progress.

## Graphics Systems

- RenderSystem
Responsible for rendering all the sprites.

## Debug Systems

- ConsoleSystem
Provides a console interface for debugging and logging any values.

- DrawGridSystem
Draws the aabb grid for better collision visualization.

## Physics Systems

- MovementSystem
Handles entity movement and navigation within the game world.

- RotationSystem
Manages rotation and orientation of entities in the game.

- GridBroadPhaseSystem
Implements a grid-based broad-phase collision detection system.

- CollisionSystem
Handles narrow-phase collision detection and triggering collision event.

## Gameplay Systems

- PlayerControllerSystem
Manages player input for shooting and following mouse for the player entity.

- TruckControllerSystem
Handles the input for the movement of the truck.

- ZombieSpawnSystem
Controls the spawning of zombie entities.

- FollowTargetSystem
Enables zombies to follow a target(player) entity rotating and moving towards it.

- DestructionSystem
Manages destruction of all entities after collision or leaving game area.

- ScoreSystem
Tracks and manages the player's score during gameplay.

- PlayerHealthSystem
Handles player health and triggers gameover on health 0.

- LevelSystem
Manages the state of game levels and increase in difficulty.

- ItemSystem
Handles the pickup and hadling of the items.

## UI Systems

- PlayerUISystem
Manages the display of all user status.

- GameStateUISystem
Handles the display and updates of the overall game state user interface.
