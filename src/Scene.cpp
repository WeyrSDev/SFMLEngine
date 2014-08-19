/* 
 * File:   Scene.cpp
 * Author: iMer
 * 
 * Created on 3. Juli 2014, 01:01
 */

#include "Scene.hpp"
#include "Game.hpp"
#include "Light.hpp"
#include <iostream>
#include <mutex>
#include "Light.hpp"
namespace engine {
    b2Vec2 Scene::default_gravity(0, 0);

    Scene::Scene(Game* game) : Node::Node(this), m_game(game), m_pixToM(20.0f), m_debugDraw(this), m_lightSystem(this), m_debug(false) {
        m_world = new b2World(default_gravity);
        m_world->SetDebugDraw(&m_debugDraw);
        m_debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
    }

    LightSystem* Scene::GetLightSystem() {
        return &m_lightSystem;
    }

    void Scene::SetDebug(bool debug) {
        m_debug = debug;
    }

    bool Scene::IsDebug() const {
        return m_debug;
    }

    Scene::~Scene() {
        delete m_world;
    }

    void Scene::SetGame(Game* game) {
        m_game = game;
    }

    Game* Scene::GetGame() const {
        return m_game;
    }

    b2World* Scene::GetWorld() {
        return m_world;
    }

    float Scene::MeterToPixel(float m) {
        return m_pixToM*m;
    }

    float Scene::GetPixelMeterRatio() const {
        return m_pixToM;
    }

    void Scene::PostDraw(sf::RenderTarget& target, sf::RenderStates states) {
        if (m_debug) {
            m_mutexDebug.lock();
            if (m_debugDraw.IsInitialized()) {
                m_debugDraw.draw(target, states);
            }
            m_mutexDebug.unlock();
        }
        m_lightSystem.draw(target, states);
    }

    void Scene::OnUpdate(sf::Time interval) {
        m_world->Step(interval.asSeconds(), 8, 3); // TODO: tweakable iterations? currently the box2d recommended ones
        if (m_debug) {
            m_mutexDebug.lock();
            m_debugDraw.Begin();
            m_world->DrawDebugData();
            m_debugDraw.End();
            m_mutexDebug.unlock();
        }
        m_lightSystem.update(interval);
    }

}

