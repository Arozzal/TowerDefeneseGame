#include "Framework.hpp"


int main() {
	std::cout << "init" << std::endl;
	{
		Framework framework;

		while (framework.isRunning) {
			framework.run();
		}
	}
	std::cout << "MAIN::" << " leaved framework!" << std::endl;
}