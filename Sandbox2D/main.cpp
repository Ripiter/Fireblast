#include <Fireblast.h>
#include "Graphics/Api/RenderAPI.h"
#include "Graphics/Renderer2D.h"

class SpriteEntity : public Fireblast::Entity 
{
public:
	Fireblast::Transform* transform;

	SpriteEntity()
	{
		AddComponent(new Fireblast::SpriteComponent({ 0, 0, 1 }, { 0.5f, 0.5f }, Fireblast::RenderAPI::GetApi()->CreateTexture("C:/Users/eadr/Desktop/Fish.png")));
		transform = GetComponent<Fireblast::Transform>();
	}

	// Inherited via Entity
	virtual void Start() override
	{
		
	}

	virtual void Update() override
	{
		//transform->Translate(glm::vec3(0.001f, 0.f, 0.f));
		transform->Rotate({0, 0, 0.001f});
	}

	void Draw() 
	{
	}
};

class Game : public Fireblast::Application {

	SpriteEntity* sp;

	virtual void OnStart() override
	{

	}

	virtual void OnAfterStart() override {
		Fireblast::FileUtils::FlipImages(true);
		sp = new SpriteEntity();
	}

	virtual void OnUpdate() override
	{
		sp->Update();
	}

	virtual void OnDraw() override
	{
		sp->Draw();
	}

	virtual ~Game() override {
		delete sp;
	}

};

int main(int argv, char* argc) {

	Game* game = new Game();

	game->Run();

	return 0;
}