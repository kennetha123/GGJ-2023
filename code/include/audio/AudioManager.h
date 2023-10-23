#pragma once
#include <SFML/Audio.hpp>
#include <spdlog/spdlog.h>

#include <map>
#include <string>
#include <memory>
#include <iostream>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    void addBgm(const std::string& id, const std::string& filepath);
    void addSfx(const std::string& id, const std::string& filepath);

    void removeBgm(const std::string& id);
    void removeSfx(const std::string& id);

    void playBgm(const std::string& id, bool loop = true, float volume = 50.f);
    void playSfx(const std::string& id, float volume = 50.f);

    void stopBgm(const std::string& id);
    void stopAllBgm();
    void stopAllSfx();

    void setBgmVolume(float volume);
    void setSfxVolume(float volume);


private:
    std::shared_ptr<spdlog::logger> log;

    std::map<std::string, std::shared_ptr<sf::Music>> bgm;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sfx;
    std::map<std::string, std::shared_ptr<sf::Sound>> active_sfx;

    float bgm_volume = 50.f;
    float sfx_volume = 50.f;
};