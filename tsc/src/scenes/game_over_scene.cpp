#include "../core/global_basic.hpp"
#include "../core/global_game.hpp"
#include "../core/bintree.hpp"
#include "../core/errors.hpp"
#include "../core/property_helper.hpp"
#include "../core/xml_attributes.hpp"
#include "../scripting/scriptable_object.hpp"
#include "../objects/actor.hpp"
#include "../scenes/scene.hpp"
#include "../core/scene_manager.hpp"
#include "../core/filesystem/resource_manager.hpp"
#include "../core/filesystem/package_manager.hpp"
#include "../user/preferences.hpp"
#include "../core/tsc_app.hpp"
#include "../objects/actor.hpp"
#include "../level/level.hpp"
#include "scene.hpp"
#include "game_over_scene.hpp"

using namespace TSC;

cGameOverScene::cGameOverScene()
{
    m_gameover_texture.loadFromFile(gp_app->Get_ResourceManager().Get_Game_Pixmap("game/game_over.png").native());

    m_gameover_sprite.setTexture(m_gameover_texture);
    m_gameover_sprite.setOrigin(m_gameover_sprite.getLocalBounds().width / 2.0,
                                m_gameover_sprite.getLocalBounds().height / 2.0);
}

cGameOverScene::~cGameOverScene()
{
}

std::string cGameOverScene::Name() const
{
    return "GameOverScene";
}

void cGameOverScene::Update(sf::RenderWindow& stage)
{
    sf::Vector2u size = stage.getSize();
    m_gameover_sprite.setPosition(size.x / 2.0, size.y / 2.0);
}

void cGameOverScene::Draw(sf::RenderWindow& stage)
{
    cScene::Draw(stage);

    stage.draw(m_gameover_sprite);
}

void cGameOverScene::Handle_Event(sf::Event& evt)
{
}
