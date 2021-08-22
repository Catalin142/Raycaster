#include "Odium/OdiumAsceniunea.h"

class Game : public Application
{
public:
	Game(const wchar_t* title) : Application(title) {
		setLayer(new OdiumAsceniunea());
	}
};

int main()
{
	Application* Odium = new Game(L"Odium Ascensiunea");
	Odium->setCamera(1, 1, 60.0f);

	Odium->Run();

	delete Odium;
	return 0;
}