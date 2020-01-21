#pragma once
#include "main.hpp"
#include "MenuText.hpp"
#include "MenuTexture.hpp"
#include "Animation.hpp"
#define WINDOW_SIZE_640x480	-0.36
#define WINDOW_SIZE_800x600	-0.15
#define WINDOW_SIZE_1024x768	0.09
#define WINDOW_SIZE_1440x900	0.33
#define WINDOW_SIZE_2560x1440	0.57
enum EMenu
{
	EM_PauseMenu,
	EM_StartMenu,
	EM_LoadMenu,
	EM_SaveMenu,
	EM_DieMenu,
	EM_UserDisplay,
	EM_OptionsMenu,
	EM_PopUpMenu
};

enum EStartMenu
{
	ES_StartGame,
	ES_LoadGame,
	ES_SaveGame,
	ES_Options,
	ES_Exit,
	ES_COUNT = 5
};

enum EPopUpMenu
{
	EP_YES,
	EP_NO,
	EP_COUNT = 2
};

enum EDieMenu
{
	ED_MAIN_MENU,
	ED_EXIT,
	ED_COUNT = 2
};

enum EPauseMenu
{
	EPP_RESUME_GAME,
	EPP_NEW_GAME,
	EPP_LOAD_GAME,
	EPP_SAVE_GAME,
	EPP_OPTIONS,
	EPP_EXIT,
	EPP_COUNT = 6
};

enum ELoadSaveMenu
{
	ELS_FIRST = 0,
	ELS_SECOND = 1,
	ELS_THIRD = 2,
	ELS_COUNT = 3
};
enum EOptions
{
	EO_FULLSCREEN,
	EO_AUDIO,
	EO_WINDOW,
	EO_BIND_UP,
	EO_BIND_DOWN,
	EO_BIND_LEFT,
	EO_BIND_RIGHT,
	EO_BIND_ATTACK,
	EO_COUNT = 8,
	EO_WINDOW_SIZE_640x480 = 10,
	EO_WINDOW_SIZE_800x600 = 11,
	EO_WINDOW_SIZE_1024x768 = 12,
	EO_WINDOW_SIZE_1440x900 = 13,
	EO_WINDOW_SIZE_2560x1440 = 14,
};

class Menu
{
public:
	Menu();
	
	Menu(Menu const &);
	
	~Menu();
	
	void					chooseMenu(EMenu);
	void					pauseMenu(int);
	void					startMenu(int);
	void					loadSaveMenu(int);
	void					renderResolutionScroll(EOptions);
	void					dieMenu(int);
	void					userDisplay();
	void					popUpMenu(int);
	void					optionsMenu(int choose);
	void					renderText(int choose, int x, int y, std::string message, int curr);
	
	int						getCurrStart() const;
	void					setCurrStart(int currStart);
	int						getCurrPause() const;
	void					setCurrPause(int currPause);
	int						getCurrPopUp() const;
	void					setCurrPopUp(int currPopUp);
	int						getCurrOptions() const;
	void					setCurrOptions(int currOptions);
	int						getCurrDie() const;
	void					setCurrDie(int currDie);
	int						getCurrOptionsWindow() const;
	void					setCurrOptionsWindow(int currOptionsWindow);
	bool					isOptionsFullscreen() const;
	void					setOptionsFullscreen(bool optionsFullscreen);
	bool					isOptionsAudio() const;
	void					setOptionsAudio(bool optionsAudio);
	int						getOptionsResolution() const;
	void					setOptionsResolution(int optionsResolution);
	int						getOptionsMoveUp() const;
	void					setOptionsMoveUp(int optionsMoveUp);
	int						getOptionsMoveDown() const;
	void					setOptionsMoveDown(int optionsMoveDown);
	int						getOptionsMoveLeft() const;
	void					setOptionsMoveLeft(int optionsMoveLeft);
	int						getOptionsMoveRight() const;
	void					setOptionsMoveRight(int optionsMoveRight);
	int						getOptionsAttack() const;
	void					setOptionsAttack(int optionsAttack);
	int						getCurrLoad() const;
	void					setCurrLoad(int currLoad);
	int						getCurrSave() const;
	void					setCurrSave(int currSave);
	int						getLevel() const;
	void					setLevel(int level);
	int						getTime() const;
	void					setTime(int time);
	int						getScore() const;
	void					setScore(int score);
	
private:
	int 					curr_start;
	int 					curr_pause;
	int 					curr_pop_up;
	int 					curr_options;
	int 					curr_die;
	int 					curr_options_window;
	bool 					options_fullscreen;
	bool 					options_audio;
	int						options_resolution;
	int 					options_move_up;
	int 					options_move_down;
	int 					options_move_left;
	int 					options_move_right;
	int 					options_attack;
	int 					curr_load;
	int 					curr_save;
	int 					level;
	int 					time;
	int 					score;
	MenuTexture					start_background;
	MenuTexture					load_save_background;
	MenuTexture					fill_fullscreen;
	MenuTexture					sample_back;
	MenuTexture					fill_audio;
	MenuTexture					scroll;
	MenuTexture					user_display;
	MenuTexture					option_background;
	MenuText					text;
};


