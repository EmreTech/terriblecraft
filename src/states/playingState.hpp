#ifndef PLAYINGSTATE_HPP
#define PLAYINGSTATE_HPP

#include "base.hpp"

namespace States
{

struct PlayingState : public StateBase
{
    PlayingState();

    void handleInput() override;
    void mouseInput(double x, double y) override;

    void update(float dt) override;
    void render() override;

    void onOpen() override;
};

} // namespace States


#endif