/* 
 * File:   ParticleSystem.hpp
 * Author: iMer
 *
 * Created on 22. August 2014, 21:18
 */

#ifndef PARTICLESYSTEM_HPP
#define	PARTICLESYSTEM_HPP
#include "SpriteNode.hpp"
#include <SFML/System.hpp>
namespace engine {

    class ParticleSystem : public Node {
    protected:
        std::vector<SpriteNode*> m_particles;
        size_t m_particleCount;
        size_t m_currentIndex;
        float m_rate;
        bool m_burst;
        float m_angle;
        float m_spread;
        sf::Vector3f m_minVelocity;
        sf::Vector3f m_maxVelocity;
        float m_toRelease;
        std::string m_particleConfig;
    public:
        ParticleSystem(Scene* scene);
        virtual ~ParticleSystem();
        virtual void OnUpdate(sf::Time interval);
        void SetVelocity(sf::Vector2f velocity);
        sf::Vector2f GetVelocity() const;
        void SetSpread(float spread);
        float GetSpread() const;
        void SetAngle(float angle);
        float GetAngle() const;
        void SetBurst(bool bust);
        bool IsBurst() const;
        void SetRate(int rate);
        int GetRate() const;
        void SetParticleCount(size_t particleCount);
        size_t GetParticleCount() const;
        void SetParticleConfig(std::string particleConfig);
        std::string GetParticleConfig() const;
        virtual bool initialize(Json::Value& root);

        
    };
}

#endif	/* PARTICLESYSTEM_HPP */

