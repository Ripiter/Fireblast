#include <Fireblast.h>
#include "Graphics/Api/RenderAPI.h"
#include "Graphics/Renderer2D.h"

class SimpleEntity : public Fireblast::Entity
{
private:
	Fireblast::Texture* texture;
	Fireblast::Transform* transform;
public:
	SimpleEntity(Fireblast::Texture* text) : Entity(), texture(nullptr), transform(nullptr)
	{
		texture = text;
	}

protected:
	// Inherited via Entity
	virtual void OnStart() override
	{
		AddComponent(new Fireblast::SpriteComponent({ 0, 0, 0 }, { 0.5f, 0.5f }, texture));
		transform = GetComponent<Fireblast::Transform>();
	}

	virtual void OnUpdate() override
	{
		transform->Rotate({ 0, 0, 0.01f });
	}
};

class Level : public Fireblast::Scene
{
	Fireblast::Texture* textu;

	// Inherited via Scene
	virtual void OnStart() override
	{
		textu = Fireblast::RenderAPI::GetApi()->CreateTexture("C:/Users/eadr/Desktop/Fish.png");
		SpawnEntity(new SimpleEntity(textu));
		SpawnEntity(new SimpleEntity(textu), { 0.5f, -0.5f, 1.f});
		SpawnEntity(new SimpleEntity(textu), { 0.5f, 0.5f, 1.f});
		//SpawnEntity(new SimpleEntity(), { -0.5f, 0.f, 1.f});

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

		Fireblast::SManager::Get()->GetManager<Fireblast::SceneManager>()->CreateScene("Level", new Level());
		Fireblast::SManager::Get()->GetManager<Fireblast::SceneManager>()->LoadScene("Level");
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