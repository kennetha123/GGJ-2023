// audio_manager.hpp
#pragma once
#include "audio/audio_manager.h"

void audio_manager::add_bgm(const std::string& id, const std::string& filepath)
{
    auto bgm = std::make_shared<sf::Music>();
    if (bgm->openFromFile(filepath))
    {
        bgm_[id] = bgm;
    }
}

void audio_manager::add_sfx(const std::string& id, const std::string& filepath)
{
    auto sfx_buffer = std::make_shared<sf::SoundBuffer>();
    if (sfx_buffer->loadFromFile(filepath))
    {
        sfx_[id] = sfx_buffer;
    }
}

void audio_manager::remove_bgm(const std::string& id)
{
    bgm_.erase(id);
}

void audio_manager::remove_sfx(const std::string& id)
{
    sfx_.erase(id);
}

void audio_manager::play_bgm(const std::string& id, bool loop, float volume)
{
    if (bgm_.count(id))
    {
        bgm_[id]->setLoop(loop);
        bgm_[id]->setVolume(volume);
        bgm_[id]->play();
    }
}

void audio_manager::play_sfx(const std::string& id, float volume)
{
    if (sfx_.count(id))
    {
        auto sfx = std::make_shared<sf::Sound>();
        sfx->setBuffer(*sfx_[id]);
        sfx->setVolume(volume);
        sfx->play();
        active_sfx_[id] = sfx;
    }
}

void audio_manager::stop_bgm(const std::string& id)
{
    if (bgm_.count(id))
    {
        bgm_[id]->stop();
    }
}

void audio_manager::stop_all_bgm()
{
    for (auto& bgm_pair : bgm_)
    {
        bgm_pair.second->stop();
    }
}

void audio_manager::stop_all_sfx()
{
    for (auto& sfx_pair : active_sfx_)
    {
        sfx_pair.second->stop();
    }
}

void audio_manager::set_bgm_volume(float volume)
{
    bgm_volume_ = volume;
    for (auto& bgm_pair : bgm_)
    {
        bgm_pair.second->setVolume(bgm_volume_);
    }
}

void audio_manager::set_sfx_volume(float volume)
{
    sfx_volume_ = volume;
    for (auto& sfx_pair : active_sfx_)
    {
        sfx_pair.second->setVolume(sfx_volume_);
    }
}
