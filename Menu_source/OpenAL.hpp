#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "../lib/open_al/include/AL/al.h"
#include "../lib/open_al/include/AL/alc.h"
#include "../lib/alut/include/AL/alut.h"

struct SoundInfo
{
	u_int			id;
	u_int			rate;
	u_int			format;
	std::string		file_name;
	
};

class OpenAL
{
private:
	OpenAL();
	OpenAL(OpenAL const &);
	~OpenAL();

public:
	bool InitOpenAL();
	bool DestroyAL();
	bool Open(std::string const & file_name, bool loop, bool streamed, bool is_front, float sound_volume);
	void Close(bool is_front);
	void Play(bool is_front);
//	void Update(bool is_front);
	void Stop(bool is_front);
	bool LoadWavFile(std::string const & file_name, bool is_front);
	ALboolean CheckALError();

public:
	std::map<ALint, SoundInfo>	buffers; // Мапа з id та параметрами музики
	static OpenAL				open_al; // Singleton
	
private:
	// Позиція слухача.
	ALfloat listener_pos[3] = { 0.0, 0.0, 0.0 };
	
	// Швидкість слухача.
	ALfloat listener_vel[3] = { 0.0, 0.0, 0.0 };
	
	// Орієнтація слухача.
	ALfloat listener_ori[6] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
	
	// Контекст програвання звуку
	ALCcontext *context;
	
	// Прилад для програвання звуку
	ALCdevice *device;
	
	// Ідентифікатори джерела звуку
	ALuint	source_id_front;
	ALuint	source_id_back;
	
	// В потоці звук?
	bool streamed;
	
	// Зациклений звук?
	bool looped;
};