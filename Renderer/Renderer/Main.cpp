#include "MeshLoading.h"
#include "Utility.h"
#include <iostream>

int main() {

	//new Startup to utilise Application class, easy entry point to swap out program

	MeshLoading newApp;

	while (newApp.Run()) {
		newApp.Render();
	}
	newApp.ShutDown();

	return 0;
}