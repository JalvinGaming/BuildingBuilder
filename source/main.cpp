// Created by JalvinGaming/Chillaxe. All code uses the MIT license.
#include <BBEngine.hpp>
BBApplication* bb;
int main() {
	bb = new BBApplication();
	bb->Run();
	delete bb;
	return 0;
}