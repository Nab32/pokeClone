#include "vector2D.h"
#include "Animation.h"

class Component
{
    public:
        bool has = false;
};


class CTransform : public Component
{
    public:
        Vec2 pos = Vec2(0, 0);
        Vec2 vel = Vec2(0, 0);
        Vec2 scale = Vec2(3, 3);
        Vec2 prevPos = Vec2(0, 0);
        Vec2 nextPos = Vec2(0, 0);

        CTransform() {}
        CTransform(const Vec2& pos) : pos(pos) {}
        CTransform(const Vec2& pos, const Vec2& vel) : pos(pos), vel(vel) {}
};

class CInput : public Component
{
    public:
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
        bool isMoving = false;
        int moveCooldown = 0;

        void forceFalse()
        {
            up = false;
            down = false;
            left = false;
            right = false;
        }

        CInput() {}
};

class CBoundingBox : public Component
{
    public:
        Vec2 size;
        Vec2 halfSize;
        CBoundingBox() {}
        CBoundingBox(const Vec2& size) : size(size), halfSize(size.x / 2, size.y / 2) {}
};

class CAnimation : public Component
{
    public:
        Animation animation;
        bool isRepeated = false;
        CAnimation() {}
        CAnimation(Animation& animation, bool repeat = false) : animation(animation), isRepeated(repeat) {}
};

class CState : public Component
{
    public:
        std::string state = "IDLE";
        enum class GameStates { IDLE, DIALOGUE };
        enum class Direction { UP, DOWN, LEFT, RIGHT };
        GameStates currentState = GameStates::IDLE;
        Direction currentDirection = Direction::DOWN;
        CState() {}
        CState(const std::string& state) : state(state) {}
};

class CInteract : public Component
{
    public:
        std::string name = "sign";
        std::vector<std::string> dialogue;
        CInteract() {}
        CInteract(const std::string& name) : name(name) {}
};

class CText : public Component
{
    public:
        std::string text = "Hello, World!";
        Vec2 textPos = Vec2(0, 0);
        std::string currentText = "";
        int count = 0;
        int nextCall = 0;
        int textSpeed = 5;
        CText() {}
        CText(const std::string& text) : text(text) {}
};

class CLifespan : public Component
{
    public:
        int lifespan = 5;
        int frameCreated = 0;
        CLifespan() {}
        CLifespan(int lifespan) : lifespan(lifespan) {}
};