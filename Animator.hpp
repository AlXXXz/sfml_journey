#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "AssetManager.hpp"


class Animator {
public:
    struct Animation {
        std::string m_Name;
        std::string m_TextureName;
        std::vector<sf::IntRect> m_frames;
        sf::Time m_duration;
        bool m_Looping;

        Animation(std::string const& name, std::string const& textureName, 
             sf::Time const& duration, bool looping) : m_Name(name),
             m_TextureName(textureName), m_duration(duration), m_Looping(looping)
        { }

        /**
         * @brief Добавить кадры в анимацию
         * @param startFrom Позиция с которой начать добавлять кадры
         * @param frameSize Размер одного кадра
         * @param frames количество кадров анимации
        */
        void AddFrames(sf::Vector2i const& startFrom, sf::Vector2i const& frameSize, 
             unsigned int frames) {
            sf::Vector2i current = startFrom;
            for (unsigned int i = 0; i < frames; i++) {
                m_frames.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));
                current.x += frameSize.x;
            }
        }
    };

    Animator(sf::Sprite& sprite);
    Animator::Animation& CreateAnimation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool loop = false);
    void update(sf::Time const& dt);
    bool SwitchAnimation(std::string const& name);
    std::string GetCurrentAnimationName() const;

private:
    sf::Sprite& m_Sprite;
    sf::Time m_CurrentTime;
    std::list<Animator::Animation> m_Animations;
    Animator::Animation* m_CurrentAnimation;

    Animator::Animation* FindAnimation(std::string const& name);
    void SwitchAnimation(Animator::Animation* animation);
};