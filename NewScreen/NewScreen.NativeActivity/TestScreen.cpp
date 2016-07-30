#include "TestScreen.h"
#include "Color.h"

TestScreen::TestScreen(MinecraftClient &client) : Screen(client) {
}

TestScreen::~TestScreen() {
}

void TestScreen::handleBackEvent(bool b) {
	Screen::handleBackEvent(b);
}

bool TestScreen::renderGameBehind() const {
	return true;
}

bool TestScreen::closeOnPlayerHurt() const {
	return false;
}

std::string TestScreen::getScreenName() {
	return "TestScreen";
}

void TestScreen::render(int i1, int i2, float f1) {
	drawString(client->getFont(), "ABCDEFG", i1, i2, Color(f1, 1 - f1, f1, 1));

	Screen::render(i1, i2, f1);
}

void TestScreen::init() {
}

void TestScreen::_buttonClicked(Button &) {
}