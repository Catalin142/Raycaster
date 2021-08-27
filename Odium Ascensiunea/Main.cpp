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
	Application* Odium = new Game(L"Odium Ascensiunea");

	BEGIN_SESSION("Main", "profile.json");
	Odium->Run();
	END_SESSION;

	delete Odium;
	return 0;
}