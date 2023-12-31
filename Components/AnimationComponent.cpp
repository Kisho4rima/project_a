#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet) {

}

AnimationComponent::~AnimationComponent()
{
    for (auto &i : this->animations)
    {
        delete i.second;
    }

}

//Functions

void AnimationComponent::play(const std::string key,  const float &deltaTime)
{
    this->animations[key]->play(deltaTime);
}

void AnimationComponent::addAnimation(const std::string key,
    float animation_timer,
    int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
    {

    this->animations[key] = new Animation(
        this->sprite, this->textureSheet, animation_timer, start_frame_x, start_frame_y,frames_x, frames_y, width, height);
}

bool AnimationComponent::isDone(const std::string key) const
{
    return this->animations.at(key)->isDone();
}
