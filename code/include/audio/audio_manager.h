// audio_manager.hpp
#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

class AudioManager
{
public:
    AudioManager() {}
    ~AudioManager() {}

    void add_bgm(const std::string& id, const std::string& filepath);
    void add_sfx(const std::string& id, const std::string& filepath);

    void remove_bgm(const std::string& id);
    void remove_sfx(const std::string& id);

    void play_bgm(const std::string& id, bool loop = true, float volume = 50.f);
    void play_sfx(const std::string& id, float volume = 50.f);

    void stop_bgm(const std::string& id);
    void stop_all_bgm();
    void stop_all_sfx();

    void set_bgm_volume(float volume);
    void set_sfx_volume(float volume);

private:

    std::map<std::string, std::shared_ptr<sf::Music>> bgm_;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sfx_;
    std::map<std::string, std::shared_ptr<sf::Sound>> active_sfx_;

    float bgm_volume_ = 50.f;
    float sfx_volume_ = 50.f;
};