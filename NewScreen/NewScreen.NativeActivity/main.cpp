#include <jni.h>
#include <memory>

#include "log.h"
#include "substrate.h"
#include "dl_internal.h"

#include "TestScreen.h"
#include "ScreenChooser.h"
#include "MinecraftScreenModel.h"
#include "MinecraftScreenController.h"
#include "UIControlFactory.h"
#include "MinecraftInputHandler.h"
#include "ScreenView.h"

template<class ScreenModel, class ScreenController, class ... Types>
std::shared_ptr<BaseScreen> createScreen(ScreenChooser const &chooser, MinecraftClient &client, std::string const &uiname, Types ...) {
	UIDefRepository *uidefrepo = client.getUIDefRepo();
	Json::Value vars = chooser.createGlobalVars();
	NameRegistry *namereg = client.getInput()->getNameRegistry();

	std::shared_ptr<ScreenController> controller = std::make_shared<ScreenController, std::shared_ptr<ScreenModel>>(std::make_shared<ScreenModel, MinecraftClient &>(client));
	controller->addStaticScreenVars(vars);

	UIControlFactory *factory = new UIControlFactory(*uidefrepo, vars, *namereg, *chooser.player, client.getFont());

	std::shared_ptr<UIControl> control1;
	std::shared_ptr<UIControl> cont = factory->createControlTree(uiname, control1);

	LOGI("%s", cont->getName().c_str());

	std::unique_ptr<UIControlFactory> fac = std::unique_ptr<UIControlFactory>(factory);

	ScreenView *view = new ScreenView(*namereg, client.keyboardManager, controller, cont, std::move(fac));
	std::shared_ptr<ScreenView> screen(view);

	LOGI("%s", view->getScreenName().c_str());

	return NULL;
}

static void(*ScreenChooser$pushChatScreen_real)(ScreenChooser *);
static void ScreenChooser$pushChatScreen_hook(ScreenChooser *_this) {
	std::shared_ptr<BaseScreen> screen = createScreen<MinecraftScreenModel, MinecraftScreenController>(*_this, *_this->client, "debug_screen.debug_screen");
	//_this->_pushScreen(screen, false);

	//_this->_pushScreen(std::make_shared<TestScreen, MinecraftClient &>(*_this->client), false);
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	soinfo2 *handle = (soinfo2 *)dlopen("libminecraftpe.so", RTLD_LAZY);
	MSHookFunction((void *)&ScreenChooser::pushChatScreen, (void *)&ScreenChooser$pushChatScreen_hook, (void **)&ScreenChooser$pushChatScreen_real);

	return JNI_VERSION_1_2;
}
