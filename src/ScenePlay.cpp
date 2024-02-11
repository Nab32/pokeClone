#include "ScenePlay.h"

ScenePlay::ScenePlay(GameEngine *game, const std::string &path)
    : Scene(game), m_path(path)
{
    init();
}

// Register actions and load map
void ScenePlay::init()
{
    registerAction(sf::Keyboard::Key::Escape, "pause");
    registerAction(sf::Keyboard::Key::W, "move_up");
    registerAction(sf::Keyboard::Key::A, "move_left");
    registerAction(sf::Keyboard::Key::S, "move_down");
    registerAction(sf::Keyboard::Key::D, "move_right");
    registerAction(sf::Keyboard::Key::Space, "interact");

    m_view.setSize(832, 468); // Set the size of the view to the size of the window (1280x720 pixels)

    m_game->getAssets().getSound("LITTLEROOT_MUSIC")->play();
    m_game->getAssets().getSound("LITTLEROOT_MUSIC")->setLoop(true);

    auto sign = m_entities.addEntity("sign");
    sign->cTransform = std::make_shared<CTransform>();
    sign->cTransform->pos = getPosition(Vec2(12, 9));
    sign->cInteract = std::make_shared<CInteract>();
    sign->cInteract->name = "sign";
    sign->cInteract->dialogue = {"STU's house"};

    auto sign2 = m_entities.addEntity("sign2");

    sign2->cTransform = std::make_shared<CTransform>();
    sign2->cTransform->pos = getPosition(Vec2(17, 9));
    sign2->cInteract = std::make_shared<CInteract>();
    sign2->cInteract->name = "sign2";
    sign2->cInteract->dialogue = {"Welcome to Littleroot Town!"};

    loadLevel();

    loadCollision();
    loadDecorations();
    spawnPlayer();
}

void ScenePlay::loadInteractables()
{
}

void ScenePlay::loadDecorations()
{
    std::ifstream file("levels/littleroot/decorations.txt");
    if (file.is_open())
    {
        int a, b;
        while (file >> a >> b)
        {
            auto dec = m_entities.addEntity("decoration");
            dec->cTransform = std::make_shared<CTransform>();
            dec->cTransform->pos = getPosition(Vec2(a, b));
            //offset
            dec->cTransform->pos.y += 8 * gameScale;
            dec->cAnimation = std::make_shared<CAnimation>();
            dec->cAnimation->animation = m_game->getAssets().getAnimation("FLOWERS");
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }
}

void ScenePlay::loadLevel()
{
    auto e = m_entities.addEntity("map");

    e->cAnimation = std::make_shared<CAnimation>();
    e->cAnimation->animation = m_game->getAssets().getAnimation("LITTLEROOT");
    e->cTransform = std::make_shared<CTransform>();
    Vec2 sizeMap = e->cAnimation->animation.getSize();

    e->cTransform->pos = Vec2(0, 0);
    m_map = e;
}

// Load another scene
void ScenePlay::onEnd()
{
}

Vec2 ScenePlay::getPosition(Vec2 grid)
{
    return Vec2(grid.x * 16 * gameScale, grid.y * 16 * gameScale);
}

void ScenePlay::spawnPlayer()
{

    auto e = m_entities.addEntity("player");

    e->cTransform = std::make_shared<CTransform>();
    e->cAnimation = std::make_shared<CAnimation>();
    e->cAnimation->animation = m_game->getAssets().getAnimation("WALK_DOWN");
    e->cInput = std::make_shared<CInput>();
    e->cState = std::make_shared<CState>();
    e->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(16 * gameScale, 16 * gameScale));
    m_player = e;
    m_player->cTransform->pos = getPosition(Vec2(10, 10));
}

// Update the scene
void ScenePlay::update()
{
    m_entities.update();

    sCamera();
    sRender();
    if (m_player->cState->currentState == CState::GameStates::IDLE)
    {
        sMovement();
    }
    sCollision();
    sAnimation();
    currentFrame++;
}

void ScenePlay::loadCollision()
{
    std::ifstream file("levels/littleroot/collisions.txt");
    if (file.is_open())
    {
        int a, b;
        while (file >> a >> b)
        {
            auto col = m_entities.addEntity("collision");
            col->cTransform = std::make_shared<CTransform>();
            col->cTransform->pos = getPosition(Vec2(a, b));
            col->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(16 * gameScale, 16 * gameScale));
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }
}

void ScenePlay::sDoAction(const Action &action)
{
    if (action.getType() == "START")
    {
        if (action.getName() == "move_up")
        {
            m_player->cInput->forceFalse();
            m_player->cInput->up = true;
        }
        else if (action.getName() == "move_left")
        {
            m_player->cInput->forceFalse();
            m_player->cInput->left = true;
        }
        else if (action.getName() == "move_down")
        {
            m_player->cInput->forceFalse();
            m_player->cInput->down = true;
        }
        else if (action.getName() == "move_right")
        {
            m_player->cInput->forceFalse();
            m_player->cInput->right = true;
        }
        else if (action.getName() == "interact")
        {
            sInteract();
        }
    }
    else
    {
        if (action.getName() == "move_up")
        {
            m_player->cInput->up = false;
        }
        else if (action.getName() == "move_left")
        {
            m_player->cInput->left = false;
        }
        else if (action.getName() == "move_down")
        {
            m_player->cInput->down = false;
        }
        else if (action.getName() == "move_right")
        {
            m_player->cInput->right = false;
        }
    }
}

void ScenePlay::sMovement()
{
    for (auto &e : m_entities.getEntities())
    {
        if (e->cTransform && e->cInput)
        {
            // Check if the entity is currently moving or if the movement cooldown is active
            if (!e->cInput->isMoving)
            {
                e->cTransform->nextPos = e->cTransform->pos;
                if (e->cInput->up)
                {
                    e->cState->state = "WALK_UP";
                    e->cState->currentDirection = CState::Direction::UP;
                    e->cTransform->nextPos.y -= 16 * gameScale; // Move up by one grid cell
                    e->cInput->isMoving = true;
                }
                else if (e->cInput->down)
                {
                    e->cState->state = "WALK_DOWN";
                    e->cState->currentDirection = CState::Direction::DOWN;
                    e->cTransform->nextPos.y += 16 * gameScale; // Move down by one grid cell
                    e->cInput->isMoving = true;
                }
                else if (e->cInput->left)
                {
                    e->cState->state = "WALK_LEFT";
                    e->cState->currentDirection = CState::Direction::LEFT;
                    e->cTransform->nextPos.x -= 16 * gameScale; // Move left by one grid cell
                    e->cInput->isMoving = true;
                }
                else if (e->cInput->right)
                {
                    e->cState->state = "WALK_RIGHT";
                    e->cState->currentDirection = CState::Direction::RIGHT;
                    e->cTransform->nextPos.x += 16 * gameScale; // Move right by one grid cell
                    e->cInput->isMoving = true;
                }
            }
            if (e->cInput->isMoving)
            {
                // What is nextPos? A collision? an interaction? etc

                if (e->cTransform->pos != e->cTransform->nextPos)
                {
                    Vec2 dir = e->cTransform->nextPos - e->cTransform->pos;
                    dir.normalize();
                    e->cTransform->prevPos = e->cTransform->pos;
                    e->cTransform->pos += dir * 3;
                }
                else
                {
                    e->cInput->isMoving = false;
                }
            }
        }
    }
}

void ScenePlay::sCamera()
{

    m_view.setCenter(m_player->cTransform->pos.x, m_player->cTransform->pos.y + m_cameraYOffset);
    m_game->getWindow().setView(m_view);
}

void ScenePlay::sInteract()
{
    auto &curDir = m_player->cState->currentDirection;
    Vec2 lookingAt = m_player->cTransform->pos;

    if (curDir == CState::Direction::UP)
    {
        lookingAt.y = m_player->cTransform->pos.y - 16 * gameScale;
    }
    else if (curDir == CState::Direction::DOWN)
    {
        lookingAt.y = m_player->cTransform->pos.y + 16 * gameScale;
    }
    else if (curDir == CState::Direction::LEFT)
    {
        lookingAt.x = m_player->cTransform->pos.x - 16 * gameScale;
    }
    else if (curDir == CState::Direction::RIGHT)
    {
        lookingAt.x = m_player->cTransform->pos.x + 16 * gameScale;
    }

    for (auto &e : m_entities.getEntities())
    {
        if (e->cTransform && e->cInteract)
        {
            if (lookingAt == e->cTransform->pos)
            {
                if (m_player->cState->currentState == CState::GameStates::IDLE)
                {

                    sDialogue(e->cInteract->dialogue);
                    m_player->cState->currentState = CState::GameStates::DIALOGUE;
                }
                else if (m_player->cState->currentState == CState::GameStates::DIALOGUE)
                {
                    queueDialogue();
                }
            }
        }
    }
}

void ScenePlay::sDialogue(std::vector<std::string> dialogue)
{
    m_dialogue = dialogue;
    generateTextbox(m_dialogue[currentDialogue]);
}

void ScenePlay::queueDialogue()
{

    std::cout << m_dialogue.size() << " DIALOGUE SIZE" << std::endl;
    std::cout << m_dialogue[currentDialogue] << " CURRENT DIALOGUE" << std::endl;

    if (m_currentTextbox->cText->currentText != m_dialogue[currentDialogue])
    {
        m_currentTextbox->cText->currentText = m_dialogue[currentDialogue];
        m_currentTextbox->cText->count = m_dialogue[currentDialogue].size();
    }
    else
    {
        if (currentDialogue + 1 < m_dialogue.size())
        {
            currentDialogue++;
            generateTextbox(m_dialogue[currentDialogue]);
        }
        else
        {
            currentDialogue = 0;
            m_dialogue.clear();
            m_currentTextbox = nullptr;
            for (auto &e : m_entities.getEntities("textbox"))
            {
                e->destroy();
            }
            m_player->cState->currentState = CState::GameStates::IDLE;
        }
    }
}

void ScenePlay::sRender()
{
    m_game->getWindow().clear(sf::Color::Black);
    for (auto e : m_entities.getEntities())
    {

        if (e->cTransform && e->cAnimation)
        {
            e->cAnimation->animation.getSprite().setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
            e->cAnimation->animation.getSprite().setScale(e->cTransform->scale.x, e->cTransform->scale.y);
            m_game->getWindow().draw(e->cAnimation->animation.getSprite());
        }

        if (e->cText)
        {
            sf::Text text;
            text.setFont(m_game->getAssets().getFont("MAIN_FONT"));
            if (currentFrame >= e->cText->nextCall)
            {
                findStringtoPrint(e);
                e->cText->nextCall = currentFrame + e->cText->textSpeed;
            }

            text.setString(e->cText->currentText);
            text.setCharacterSize(44);
            text.setFillColor(sf::Color::Black);
            text.setPosition(e->cText->textPos.x, e->cText->textPos.y);
            m_game->getWindow().draw(text);
        }
    }
}

std::string ScenePlay::findStringtoPrint(std::shared_ptr<Entity> entity)
{
    if (entity->cText->count >= entity->cText->text.size())
    {
        entity->cText->currentText = entity->cText->text;
        return entity->cText->text;
    }
    else
    {
        entity->cText->currentText += entity->cText->text[entity->cText->count];
        entity->cText->count++;
        return entity->cText->currentText;
    }
}

void ScenePlay::generateTextbox(std::string text)
{
    int desiredWidth = 800;
    int desiredHeight = 180;
    auto textbox = m_entities.addEntity("textbox");
    textbox->cTransform = std::make_shared<CTransform>();
    textbox->cTransform->pos = Vec2(m_player->cTransform->pos.x, m_player->cTransform->pos.y + 250);
    textbox->cAnimation = std::make_shared<CAnimation>();
    textbox->cAnimation->animation = m_game->getAssets().getAnimation("TEXTBOX");
    // Scaling the box to desired width and height
    textbox->cTransform->scale = Vec2((float)desiredWidth / textbox->cAnimation->animation.getSize().x, (float)desiredHeight / textbox->cAnimation->animation.getSize().y);
    // Center textbox on middle bottom of screen (depending on player pos)
    textbox->cAnimation->animation.getSprite().setOrigin(textbox->cAnimation->animation.getSize().x / 2, textbox->cAnimation->animation.getSize().y);
    // put the text in the textbox
    textbox->cText = std::make_shared<CText>();
    textbox->cText->text = text;
    textbox->cText->textPos = Vec2(textbox->cTransform->pos.x - desiredWidth / 2 + 32, textbox->cTransform->pos.y - desiredHeight / 2 - 50);
    m_currentTextbox = textbox;
}

void ScenePlay::sCollision()
{

    for (auto &e2 : m_entities.getEntities())
    {
        if (e2->cTransform && e2->cBoundingBox)
        {
            if (m_player->cTransform->pos != e2->cTransform->pos)
            {
                if (m_player->cTransform->pos.x < e2->cTransform->pos.x + e2->cBoundingBox->size.x &&
                    m_player->cTransform->pos.x + m_player->cBoundingBox->size.x > e2->cTransform->pos.x &&
                    m_player->cTransform->pos.y < e2->cTransform->pos.y + e2->cBoundingBox->size.y &&
                    m_player->cTransform->pos.y + m_player->cBoundingBox->size.y > e2->cTransform->pos.y)
                {
                    m_player->cTransform->pos = m_player->cTransform->prevPos;
                    m_player->cInput->isMoving = false;
                }
            }
        }
    }
}

// Change animation depending on state
void ScenePlay::sAnimation()
{
    for (auto &e : m_entities.getEntities())
    {
        if (e->cAnimation)
            e->cAnimation->animation.update();
        if (e->cState)
        {

            auto &anim = e->cAnimation->animation;

            auto &state = e->cState->state;

            if (state == "IDLE")
            {
                anim.setFrame(2);
            }

            else if (anim.getName() != state)
            {
                anim = m_game->getAssets().getAnimation(state);
            }

            if (!e->cInput->isMoving)
            {
                e->cState->state = "IDLE";
            };
        }
    }
}
