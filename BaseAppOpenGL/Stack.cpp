#include "Stack.h"

void Stack::adicionarCubo(Cube& cubo) {
	if (cubos.size() < 10) {
		cubos.push_back(cubo);
	}
}

void Stack::draw() {
	for (Cube& cubo : cubos) {
		cubo.draw();
	}
}

float Stack::getHeight() {
	if (!cubos.empty()) {
		return cubos.back().y + 1.0f;
	}
	else {
		return 0.5f;
	}
}

bool Stack::isFull(){
	return cubos.size() >= 10;
}

void Stack::clear() {
	cubos.clear();
}