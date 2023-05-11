#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30), npc(DEFAULT_WINDOW_WIDTH / 2, 10, 30,30) {

	TTF_Font* font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);

	gfx->useFont(font);
	gfx->setVerticalSync(true);

	for (int i = 0; i < numKeys; i++) {
		std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
		k->isAlive = true;
		k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
		gameKeys.push_back(k);
	}



}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 10;
	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}

	if (eventSystem->isPressed(Key::Z))
	{
		mySystem->setLanguage("ru-RU");
		
	}

	if (eventSystem->isPressed(Key::X))
	{
		mySystem->setLanguage("en-US");

	}

	if (eventSystem->isPressed(Key::C))
	{
		mySystem->setLanguage("example");
	}
}

void MyGame::update() {
	box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numKeys--;
		}
	}
	if (SDL_HasIntersection(&box.getSDLRect(), &npc.getSDLRect()) && !soundPlayed)
	{
		if (mySystem->getLocalisedSoundString("hello.wav") != "")
		{
			hello_sound = ResourceManager::loadSound(mySystem->getLocalisedSoundString("hello.wav"));
			sfx->playSound(hello_sound);
		}
		soundPlayed = true;
	}
	if (!SDL_HasIntersection(&box.getSDLRect(), &npc.getSDLRect()))
	{
		soundPlayed = false;
	}

	velocity.x = 0;
	velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	}

}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);
	gfx->setDrawColor(SDL_COLOR_GREEN);
	gfx->drawRect(npc);
	
	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
		if (key->isAlive)
			gfx->drawCircle(key->pos, 5);
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);

	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	std::string win_text = mySystem->getLocalisedString("hello_string");
	std::string task_text = mySystem->getLocalisedString("task_string");
	std::string reward_text = mySystem->getLocalisedString("reward_string");
	if (SDL_HasIntersection(&box.getSDLRect(), &npc.getSDLRect()))
	{
		if (!gameWon)
		{
			gfx->drawCustomText(win_text, 250, 100, 36);
			gfx->drawCustomText(task_text, 250, 200, 36);
		}
		else {
			gfx->drawCustomText(reward_text, 250, 200, 36);
		}
	}



	gfx->setDrawColor(SDL_COLOR_WHITE);
	std::string easter_egg = "Artemi Sementsenko-CI517-2023";
	gfx->drawCustomText(easter_egg, DEFAULT_WINDOW_WIDTH - 30 * 8, DEFAULT_WINDOW_HEIGHT - 20, 16);
	gfx->drawCustomText("Language:", 0, DEFAULT_WINDOW_HEIGHT - 40, 16);
	gfx->drawCustomText(mySystem->getLanguage(), 0, DEFAULT_WINDOW_HEIGHT - 20, 16);


}
