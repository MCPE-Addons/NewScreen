#pragma once

#include "Screen.h"

class TestScreen : public Screen {
public:
	TestScreen(MinecraftClient &);
	virtual ~TestScreen();
	virtual void handleBackEvent(bool);
	virtual bool renderGameBehind() const;
	virtual bool closeOnPlayerHurt() const;
	virtual std::string getScreenName();
	virtual void render(int, int, float);
	virtual void init();
	virtual void _buttonClicked(Button &);
};