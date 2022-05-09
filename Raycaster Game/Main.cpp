#include "App/Raycaster.h"

class Game : public Application
{
public:
	Game(const wchar_t* title) : Application(title) {
		pushLayer(new RaycasterGame());
	}
};

int main()
{
	BEGIN_SESSION("Main", "profile.json");

	Application* Raycaster = new Game(L"Raycaster game");
	Raycaster->Run();

	END_SESSION;

	delete Raycaster;
	return 0;
}