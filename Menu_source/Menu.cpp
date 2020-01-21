#include "Menu.hpp"

Menu::Menu()
{
	start_background.loadTexture("../textures/start_back.png", Rect(-1,1,1,-1));
	load_save_background.loadTexture("../textures/load_save_back.png", Rect(-1,1,1,-1));
	option_background.loadTexture("../textures/options_back.png", Rect(-1,1,1,-1));
	fill_fullscreen.loadTexture("../textures/fill.png", Rect(-0.426,0.81,-0.33,0.72));
	fill_audio.loadTexture("../textures/fill.png", Rect(-0.426,0.652,-0.33,0.56));
	scroll.loadTexture("../textures/scroll.png", Rect(-0.36, 0.345, -0.16,0.255));
	sample_back.loadTexture("../textures/bomberman_sample_back.png", Rect(-1,1,1,-1));
	curr_start = 0;
	curr_load = 0;
	curr_save = 0;
	curr_pause = 0;
}

Menu::Menu(Menu const &)
{}

Menu::~Menu()
{}

void Menu::chooseMenu(EMenu choose)
{
	switch (choose)
	{
		case EM_StartMenu :
			startMenu(abs(curr_start % ES_COUNT));
			break;
		case EM_LoadMenu :
			loadSaveMenu(abs(curr_load % ELS_COUNT));
			break;
		case EM_SaveMenu :
			loadSaveMenu(abs(curr_save % ELS_COUNT));
			break;
		case EM_PauseMenu :
			pauseMenu(abs(curr_pause % EPP_COUNT));
			break;
		case EM_OptionsMenu :
			optionsMenu((abs(curr_options % EO_COUNT)));
			break;
		case EM_PopUpMenu :
			popUpMenu((abs(curr_pop_up % EP_COUNT)));
			break;
		case EM_DieMenu :
			dieMenu((abs(curr_die % ED_COUNT)));
			break;
		case EM_UserDisplay :
			userDisplay();
			break;
	}
}

void Menu::renderText(int choose, int x, int y, std::string message, int curr)
{
	if (choose == curr)
		text.displayMessage(message, Rect(x,y,0,0), glm::vec3(0.8,0.0f,0.0f), 0.5);
	else
		text.displayMessage(message, Rect(x,y,0,0), glm::vec3(0.0,0.0f,0.0f), 0.5);
}

void Menu::popUpMenu(int choose)
{
	sample_back.drawTexture();
	renderText(0,350, 500, "Are you sure?", -1);
	for (int i = 0; i < EP_COUNT; i++)
	{
		switch (EPopUpMenu(i))
		{
			case EP_YES:
				renderText(choose ,390,455, "Yes", EP_YES);
				break;
			case EP_NO:
				renderText(choose ,505,455, "No", EP_NO);
				break;
		}
	}
}

void Menu::pauseMenu(int choose)
{
	sample_back.drawTexture();
	for (int i = 0; i < EPP_COUNT; i++)
	{
		switch (EPauseMenu(i))
		{
			case EPP_RESUME_GAME:
				renderText(choose ,400,550, "Resume Game", EPP_RESUME_GAME);
				break;
			case EPP_NEW_GAME:
				renderText(choose ,400,500, "New Game", EPP_NEW_GAME);
				break;
			case EPP_LOAD_GAME:
				renderText(choose ,400,450, "Load Game", EPP_LOAD_GAME);
				break;
			case EPP_SAVE_GAME:
				renderText(choose ,400,400, "Save Game", EPP_SAVE_GAME);
				break;
			case EPP_OPTIONS:
				renderText(choose ,400,350, "Options", EPP_OPTIONS);
				break;
			case EPP_EXIT:
				renderText(choose ,400,300, "Exit", EPP_EXIT);
				break;
		}
	}
}

void Menu::dieMenu(int choose)
{
	sample_back.drawTexture();
	renderText(0,400,550, "You Die!",-1);
	for (int i = 0; i < ED_COUNT; i++)
	{
		switch (EDieMenu(i))
		{
			case ED_MAIN_MENU:
				renderText(choose ,370,450, "Main Menu", ED_MAIN_MENU);
				break;
			case ED_EXIT:
				renderText(choose ,370,400, "Exit", ED_EXIT);
				break;
		}
	}
}

void Menu::userDisplay()
{
	user_display.drawTexture();
	text.displayMessage("Score " + std::to_string(score), Rect(15,740,0,0),glm::vec3(1,1,1),0.5f);
	text.displayMessage("Time " + std::to_string(time), Rect(400,740,0,0),glm::vec3(1,1,1),0.5f);
	text.displayMessage("Level 1-" + std::to_string(level), Rect(820,740,0,0),glm::vec3(1,1,1),0.5f);
}

void Menu::startMenu(int choose)
{
	start_background.drawTexture();
	for (int i = 0; i < ES_COUNT; i++)
	{
		switch (EStartMenu(i))
		{
			case ES_StartGame:
				renderText(choose ,100,300, "Start Game", ES_StartGame);
				break;
			case ES_LoadGame:
				renderText(choose ,100,250, "Load Game", ES_LoadGame);
				break;
			case ES_SaveGame:
				renderText(choose ,100,200, "Save Game", ES_SaveGame);
				break;
			case ES_Options:
				renderText(choose ,100,150, "Options", ES_Options);
				break;
			case ES_Exit:
				renderText(choose ,100,100, "Exit", ES_Exit);
				break;
		}
	}
}

void Menu::loadSaveMenu(int choose)
{
	load_save_background.drawTexture();
	for (int i = 0; i < ELS_COUNT; i++)
	{
		switch (ELoadSaveMenu(i))
		{
			case ELS_FIRST:
				renderText(choose, 65, 450, "-Empty-", ELS_FIRST);
				break;
			case ELS_SECOND:
				renderText(choose, 425, 450, "-Empty-", ELS_SECOND);
				break;
			case ELS_THIRD:
				renderText(choose, 785, 450, "-Empty-", ELS_THIRD);
				break;
		}
	}
}

void Menu::renderResolutionScroll(EOptions choose)
{
	switch (choose)
	{
		case EO_WINDOW_SIZE_640x480:
			scroll.changePosition(Rect(WINDOW_SIZE_640x480,0.345,WINDOW_SIZE_640x480 + 0.26,0.255));
			scroll.drawTexture();
			renderText(0,550,450,"640x480",-1);
			break;
		case EO_WINDOW_SIZE_800x600:
			scroll.changePosition(Rect(WINDOW_SIZE_800x600,0.345,WINDOW_SIZE_800x600 + 0.26,0.255));
			scroll.drawTexture();
			renderText(0,550,450,"800x600",-1);
			break;
		case EO_WINDOW_SIZE_1024x768:
			scroll.changePosition(Rect(WINDOW_SIZE_1024x768,0.345,WINDOW_SIZE_1024x768 + 0.26,0.255));
			scroll.drawTexture();
			renderText(0,550,450,"1024x768",-1);
			break;
		case EO_WINDOW_SIZE_1440x900:
			scroll.changePosition(Rect(WINDOW_SIZE_1440x900,0.345,WINDOW_SIZE_1440x900 + 0.26,0.255));
			scroll.drawTexture();
			renderText(0,550,450,"1440x900",-1);
			break;
		case EO_WINDOW_SIZE_2560x1440:
			scroll.changePosition(Rect(WINDOW_SIZE_2560x1440,0.345,WINDOW_SIZE_640x480 + 0.26,0.255));
			scroll.drawTexture();
			renderText(0,550,450,"2560x1440",-1);
			break;
	}
}

void Menu::optionsMenu(int choose)
{
	option_background.drawTexture();
	for (int i = 0; i < EO_COUNT; i++)
	{
		switch (EOptions (i))
		{
			case EO_FULLSCREEN:
				options_fullscreen ? fill_fullscreen.drawTexture() : void();
				renderText(choose,60,670, "FULLSCREEN", EO_FULLSCREEN );
				break;
			case EO_AUDIO:
				options_audio ? fill_audio.drawTexture() : void();
				renderText(choose,180,605, "AUDIO", EO_AUDIO);
				break;
			case EO_WINDOW:
				renderResolutionScroll(EOptions(abs(curr_options_window % 5) + 10));
				renderText(choose,50,490,"RESOLUTION", EO_WINDOW);
				break;
			case EO_BIND_UP:
				renderText(choose,220,370, "UP", EO_WINDOW);
//				renderText(choose,0,0, std::to_string(options_move_up),-1);
				break;
			case EO_BIND_DOWN:
				renderText(choose,175,315, "DOWN", EO_BIND_DOWN);
//				renderText(choose,0,0, std::to_string(options_move_down),-1);
				break;
			case EO_BIND_LEFT:
				renderText(choose,177,265, "LEFT", EO_BIND_LEFT);
//				renderText(choose,0,0, std::to_string(options_move_left),-1);
				break;
			case EO_BIND_RIGHT:
				renderText(choose,167,215, "RIGHT", EO_BIND_RIGHT);
//				renderText(choose,0,0, std::to_string(options_move_right),-1);
				break;
			case EO_BIND_ATTACK:
				renderText(choose,137,165, "ATTACK", EO_BIND_ATTACK);
//				renderText(choose,0,0, std::to_string(options_attack),-1);
				break;
		}
	}
}

int Menu::getCurrStart() const
{
	return curr_start;
}

void Menu::setCurrStart(int currStart)
{
	curr_start = currStart;
}

int Menu::getCurrPause() const
{
	return curr_pause;
}

void Menu::setCurrPause(int currPause)
{
	curr_pause = currPause;
}

int Menu::getCurrPopUp() const
{
	return curr_pop_up;
}

void Menu::setCurrPopUp(int currPopUp)
{
	curr_pop_up = currPopUp;
}

int Menu::getCurrOptions() const
{
	return curr_options;
}

void Menu::setCurrOptions(int currOptions)
{
	curr_options = currOptions;
}

int Menu::getCurrDie() const
{
	return curr_die;
}

void Menu::setCurrDie(int currDie)
{
	curr_die = currDie;
}

int Menu::getCurrOptionsWindow() const
{
	return curr_options_window;
}

void Menu::setCurrOptionsWindow(int currOptionsWindow)
{
	curr_options_window = currOptionsWindow;
}

bool Menu::isOptionsFullscreen() const
{
	return options_fullscreen;
}

void Menu::setOptionsFullscreen(bool optionsFullscreen)
{
	options_fullscreen = optionsFullscreen;
}

bool Menu::isOptionsAudio() const
{
	return options_audio;
}

void Menu::setOptionsAudio(bool optionsAudio)
{
	options_audio = optionsAudio;
}

int Menu::getOptionsResolution() const
{
	return options_resolution;
}

void Menu::setOptionsResolution(int optionsResolution)
{
	options_resolution = optionsResolution;
}

int Menu::getOptionsMoveUp() const
{
	return options_move_up;
}

void Menu::setOptionsMoveUp(int optionsMoveUp)
{
	options_move_up = optionsMoveUp;
}

int Menu::getOptionsMoveDown() const
{
	return options_move_down;
}

void Menu::setOptionsMoveDown(int optionsMoveDown)
{
	options_move_down = optionsMoveDown;
}

int Menu::getOptionsMoveLeft() const
{
	return options_move_left;
}

void Menu::setOptionsMoveLeft(int optionsMoveLeft)
{
	options_move_left = optionsMoveLeft;
}

int Menu::getOptionsMoveRight() const
{
	return options_move_right;
}

void Menu::setOptionsMoveRight(int optionsMoveRight)
{
	options_move_right = optionsMoveRight;
}

int Menu::getOptionsAttack() const
{
	return options_attack;
}

void Menu::setOptionsAttack(int optionsAttack)
{
	options_attack = optionsAttack;
}

int Menu::getCurrLoad() const
{
	return curr_load;
}

void Menu::setCurrLoad(int currLoad)
{
	curr_load = currLoad;
}

int Menu::getCurrSave() const
{
	return curr_save;
}

void Menu::setCurrSave(int currSave)
{
	curr_save = currSave;
}

int Menu::getLevel() const
{
	return level;
}

void Menu::setLevel(int level)
{
	Menu::level = level;
}

int Menu::getTime() const
{
	return time;
}

void Menu::setTime(int time)
{
	Menu::time = time;
}

int Menu::getScore() const
{
	return score;
}

void Menu::setScore(int score)
{
	Menu::score = score;
}


