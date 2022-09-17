#include "App/RaycasterDemo.h"

class Game : public Application
{
public:
	Game(const wchar_t* title) : Application(title, 1600, 900, 425, 240) {
	//Game(const wchar_t* title) : Application(title, 1600, 900, 900, 500) {
		pushLayer(new RaycasterDemo());
	}
};

int main()
{
	BEGIN_SESSION("Main", "profile.json");

	Application* Raycaster = new Game(L"Raycaster Demo");
	Raycaster->Run();

	END_SESSION;

	delete Raycaster;
	return 0;
}