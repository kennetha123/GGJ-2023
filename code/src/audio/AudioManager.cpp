#include "audio/AudioManager.h"

void AudioManager::addBgm(const std::string& id, const std::string& filepath)
{
    auto bgm_ = std::make_shared<sf::Music>();
    if (bgm_->openFromFile(filepath))
    {
        bgm[id] = bgm_;
    }
}

void AudioManager::addSfx(const std::string& id, const std::string& filepath)
{
    auto sfx_buffer = std::make_shared<sf::SoundBuffer>();
    if (sfx_buffer->loadFromFile(filepath))
    {
        sfx[id] = sfx_buffer;
    }
}

void AudioManager::removeBgm(const std::string& id)
{
    bgm.erase(id);
}

void AudioManager::removeSfx(const std::string& id)
{
    sfx.erase(id);
}

void AudioManager::playBgm(const std::string& id, bool loop, float volume)
{
    if (bgm.count(id))
    {
        bgm[id]->setLoop(loop);
        bgm[id]->setVolume(volume);
        bgm[id]->play();
    }
}

void AudioManager::playSfx(const std::string& id, float volume)
{
    if (sfx.count(id))
    {
        auto sfx_ = std::make_shared<sf::Sound>();
        sfx_->setBuffer(*sfx[id]);
        sfx_->setVolume(volume);
        sfx_->play();
        active_sfx[id] = sfx_;
    }
}

void AudioManager::stopBgm(const std::string& id)
{
    if (bgm.count(id))
    {
        bgm[id]->stop();
    }
}

void AudioManager::stopAllBgm()
{
    for (auto& bgm_pair : bgm)
    {
        bgm_pair.second->stop();
    }
}

void AudioManager::stopAllSfx()
{
    for (auto& sfx_pair : active_sfx)
    {
        sfx_pair.second->stop();
    }
}

void AudioManager::setBgmVolume(float volume)
{
    bgm_volume = volume;
    for (auto& bgm_pair : bgm)
    {
        bgm_pair.second->setVolume(bgm_volume);
    }
}

void AudioManager::setSfxVolume(float volume)
{
    sfx_volume = volume;
    for (auto& sfx_pair : active_sfx)
    {
        sfx_pair.second->setVolume(sfx_volume);
    }
}
