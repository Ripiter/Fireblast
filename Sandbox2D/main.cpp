#include <Fireblast.h>
#include "Utils/ModelLoader.h"

class SimpleEntity : public Fireblast::Entity
{
private:
	std::string m_TextureName;
	Fireblast::Transform* m_Transform;
public:
	SimpleEntity(std::string textureName) : Entity(), m_TextureName(textureName), m_Transform(nullptr)
	{
	}

protected:
	virtual void OnStart() override
	{
		AddComponent(new Fireblast::SpriteComponent({ 0, 0, 0 }, { 2.f, 2.f }, m_TextureName, {1.f, 0.f, 0.f, 1.f}));
		m_Transform = GetComponent<Fireblast::Transform>();
	}

	virtual void OnUpdate() override
	{
		m_Transform->Rotate({ 0, 0, 0.01f });
	}
};

class Level : public Fireblast::Scene
{
	virtual void OnStart() override
	{
		SpawnEntity(new SimpleEntity("DefaultTexture"), {2, 2, 1.f});
		SpawnEntity(new SimpleEntity("FishTexture"), { 7.5f, 7.5f, 1.f});
		SpawnEntity(new SimpleEntity("DefaultTexture"), { 14.f, 14.f, 1.f});

	}

	virtual void OnUpdate() override
	{
	}

	void Draw()
	{
	}
};

class Game : public Fireblast::Application {


	virtual void OnStart() override
	{
		Fireblast::FileUtils::FlipImages(true);
		Fireblast::SManager::Get()->GetManager<Fireblast::ResourceManager>()->LoadTexture("FishTexture", "./Assets/Fish.png");
		Fireblast::SManager::Get()->GetManager<Fireblast::ResourceManager>()->LoadTexture("DuckTexture", "./Assets/Duck.jpg");

		Fireblast::SManager::Get()->GetManager<Fireblast::SceneManager>()->CreateScene("Level", new Level());
		Fireblast::SManager::Get()->GetManager<Fireblast::SceneManager>()->LoadScene("Level");

		Fireblast::Utils::ObjMeshLoader* obj = new Fireblast::Utils::ObjMeshLoader();
		obj->LoadFile("./Assets/cube.obj");
		FB_CORE_INFO(obj->TestMethod());
		delete obj;
	}

	virtual void OnUpdate() override
	{
	}

	virtual void OnDraw() override
	{
	}

	virtual ~Game() override {
	}

};

int main(int argv, char* argc) {

	Game* game = new Game();

	game->Run();

	return 0;
}