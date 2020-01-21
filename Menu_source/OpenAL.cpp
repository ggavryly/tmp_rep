#include "OpenAL.hpp"

OpenAL	OpenAL::open_al;

OpenAL::OpenAL()
{}

OpenAL::OpenAL(OpenAL const &)
{}

OpenAL::~OpenAL()
{}

bool OpenAL::InitOpenAL()
{
	// Ініціалізація прилада
	OpenAL::open_al.device = alcOpenDevice(nullptr);
	
	// Ініціалізація контексту
	OpenAL::open_al.context = alcCreateContext(OpenAL::open_al.device, nullptr);
	
	if (!OpenAL::open_al.device || !OpenAL::open_al.context)
		std::cout << "error init OpenAL" << std::endl;
	
	alcMakeContextCurrent(OpenAL::open_al.context); // Робимо контекст поточним
	
	// Ініціалізуємо параметри слухача
	alListenerfv(AL_POSITION, OpenAL::open_al.listener_pos); // Позиція
	alListenerfv(AL_VELOCITY, OpenAL::open_al.listener_vel); // Швидкість
	alListenerfv(AL_ORIENTATION, OpenAL::open_al.listener_ori); // Орієнтація
	return true;
}

bool OpenAL::DestroyAL()
{
	// Очищаємо всі буфери
	Close(true);
	Close(false);
	// CODE
	// Виключаємо поточний контекст
	alcMakeContextCurrent(nullptr);
	// Деініціалізуємо контекст
	alcDestroyContext(OpenAL::open_al.context);
	// Закриваємо звуковий прилад
	alcCloseDevice(OpenAL::open_al.device);
	
	return true;
}

ALboolean OpenAL::CheckALError()
{
	ALenum err_code;
	std::string err = "OpenAL error: ";
	if ((err_code = alGetError()) != AL_NO_ERROR)
	{
		err += (char *)alGetString(err_code);
		std::cerr << err << std::endl;
		return AL_FALSE;
	}
	return AL_TRUE;
}

bool OpenAL::Open(std::string const &file_name, bool loop, bool streamed, bool is_front, float sound_volume)
{
	OpenAL::open_al.looped = loop;
	ALuint	source_id;
	// Створюємо id нашого звуку
	if (is_front)
		alGenSources(1, &OpenAL::open_al.source_id_front);
	else
		alGenSources(1, &OpenAL::open_al.source_id_back);
	source_id = (is_front) ? (OpenAL::open_al.source_id_front) : (OpenAL::open_al.source_id_back);
	if (!CheckALError())
		return false;
	
	alSourcef(source_id, AL_PITCH, 1.0f);
	alSourcef(source_id, AL_GAIN, 1.0f);
	alSourcefv(source_id, AL_POSITION, OpenAL::open_al.listener_pos);
	alSourcefv(source_id, AL_VELOCITY, OpenAL::open_al.listener_vel);
	alSourcei(source_id, AL_LOOPING, loop);
	alSourcef(source_id, AL_GAIN, sound_volume);
	
	// Отримуєсо розширення звуку
	const unsigned long it = file_name.find(".wav");
	if (it != std::string::npos)
		return LoadWavFile(file_name, is_front);
	std::cout << __LINE__ << std::endl;
	return false;
}

void OpenAL::Play(bool is_front)
{
	ALuint	source_id = (is_front) ? (OpenAL::open_al.source_id_front) : (OpenAL::open_al.source_id_back);
	alSourcePlay(source_id);
}

void OpenAL::Close(bool is_front)
{
	ALuint	source_id = (is_front) ? (OpenAL::open_al.source_id_front) : (OpenAL::open_al.source_id_back);
	alSourceStop(source_id);
	if (alIsSource(source_id))
		alDeleteSources(1, &source_id);
}

void OpenAL::Stop(bool is_front)
{
	ALuint	source_id = (is_front) ? (OpenAL::open_al.source_id_front) : (OpenAL::open_al.source_id_back);
	alSourceStop(source_id);
}

bool OpenAL::LoadWavFile(std::string const &file_name, bool is_front)
{
	SoundInfo	buffer_info; // Структура яка містить аудіо парамтри іd і тд.
	
	ALenum	format; // Формат інфи в буфері
	
	ALvoid	*data; // Поінтер на массив данних звука
	
	ALsizei	size; // Розмір масива ^
	
	ALsizei	freq; // Частота звука в герцах
	
	ALboolean	loop; // Зациклено?
	
	ALuint	buf_id = 0; // id буфера
	
	ALuint	source_id = (is_front) ? (OpenAL::open_al.source_id_front) : (OpenAL::open_al.source_id_back);
	
	buffer_info.file_name = file_name;
	
	for (auto & elem : buffers) // Перевірємо чи не має вже такого звуку в мапі
	{
		if (elem.second.file_name == file_name)
			buf_id = elem.first;
	}
	if (!buf_id)
	{
		std::cout << context << std::endl;
		alGenBuffers(1, &buffer_info.id); // Створюємо буфер
		if (!CheckALError())
			return false;
		std::cout << file_name.data() << std::endl;
		alutLoadWAVFile((ALbyte *)file_name.c_str(), &format, &data, &size, &freq); // Грузимо дані з wav файлу
		if (!CheckALError())
			return false;
		if (!CheckALError())
			return false;
		buffer_info.format = format;
		buffer_info.rate = freq;
		alBufferData(buffer_info.id, format, data, size, freq); // Заповнюємо буфер даними
		if (!CheckALError())
			return false;
		alutUnloadWAV(format, data, size, freq); // Звільнюємо потік зчитування wav файлу
		if (!CheckALError())
			return false;
		buffers[buffer_info.id] = buffer_info;
	}
	else
		buffer_info = buffers[buf_id];

	alSourcei(source_id, AL_BUFFER, buffer_info.id); // Ассоціюємо буфер з джерелом
	
	return true;
}