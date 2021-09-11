#include "Odium/OdiumAsceniunea.h"

class Game : public Application
{
public:
	Game(const wchar_t* title) : Application(title) {
		pushLayer(new OdiumAsceniunea());
	}
};

int main()
{
	BEGIN_SESSION("Main", "profile.json");

	Application* Odium = new Game(L"Odium Ascensiunea");
	Odium->Run();

	END_SESSION;

	delete Odium;
	return 0;
}