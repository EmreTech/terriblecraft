#ifndef BASE_HPP
#define BASE_HPP

namespace States
{

struct StateBase
{
    virtual ~StateBase() = 0;

    virtual void handleInput() = 0;

    virtual void update(float dt) = 0;
    virtual void render() = 0;

    virtual void onOpen() = 0;
};

} // namespace States


#endif