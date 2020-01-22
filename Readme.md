# Fireblast Engine

## Getting Started
To get started with using the engine, you have to clone the project with the --recursive.
```
git clone --recursive https://github.com/blackout1471/Fireblast.git
```
The --recursive part is important to fetch all the submodules, which is needed to build the project.

After the project has been cloned, you can go ahead and double click the file Generate_solutions.bat to generate the project for your OS.

## Setup and linking
To use the engine in another project, you have to link the static build libraries. and all the sub libraries.
How to link can be watched in the Sandbox2D or the Sandbox3D project.

### Entrypoint & the structure of the engine
```cpp
int main(int argv, char* argc) {
	// The application class
	Game* game = new Game();

	// The run command inherited from application class
	game->Run();

	return 0;
}
```

```cpp
// The application class, also the entry point
class Game : public Fireblast::Application {
	virtual void OnStart() override
	{
		// Load Resources
		// Load Scenes
		// Load custom systems
	}

	virtual void OnUpdate() override
	{
		// Update some code between each frame
	}

	virtual void OnDraw() override
	{
		// Update some code between each draw call
	}

	virtual ~Game() override 
	{
		// Destroy all resources
	}

};
```

```cpp
// The scene class, all the entities will be contained here
// The scene should be loaded in the start of the application
// And loaded at some point
class Level : public Fireblast::Scene
{
	virtual void OnStart() override
	{
		// Spawn entities, ex: SpawnEntity(new SimpleEntity("DefaultTexture"), {2, 2, 1.f});
	}

	virtual void OnUpdate() override
	{
		// Update some specific scene code
	}
};
```

```cpp
// The entity class, every visible and non-visible object
// In the application should be contained in a entity class
// Different systems can handle the different components.
class SimpleEntity : public Fireblast::Entity
{
protected:
	virtual void OnStart() override
	{
		// Add some components to the entity: ex AddComponent(new Fireblast::SpriteComponent({ 0, 0, 0 }, { 2.f, 2.f }, m_TextureName, {1.f, 0.f, 0.f, 1.f}));
	}

	virtual void OnUpdate() override
	{
		// update some entity specific code
	}
};
```

## Future Features
You can see what is planned for the next release in [TODO](Todo.md).

## The Plan
The plan for this game engine, is to be able to do everything from the code side.
So that no end-user is dependent on the editor.
Ofcourse those that want the editor features, will also get those.

## How To Commit
Create a pull request and if the work is something that i like, i will add it.