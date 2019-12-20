#include <Fireblast.h>

class Game : public Fireblast::Application {

	

	virtual void OnStart() override
	{
	}

	virtual void OnAfterStart() override {
		
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