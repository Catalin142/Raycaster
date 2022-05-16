#include "App/UIDemo.h"

class Game : public Application
{
public:
	Game(const wchar_t* title) : Application(title, 1600, 900, 426, 240) {
		pushLayer(new UIDemo());
	}
};

int main()
{
	BEGIN_SESSION("Main", "profile.json");

	Application* Raycaster = new Game(L"UI Demo");
	Raycaster->Run();

	END_SESSION;

	delete Raycaster;
	return 0;
}