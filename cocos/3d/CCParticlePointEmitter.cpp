
#include "3d/CCParticlePointEmitter.h"
#include "3d/CCParticleSystem3D.h" 
#include "tinyxml2.h"
NS_CC_BEGIN

    ParticlePointEmitter::ParticlePointEmitter(ParticleSystem3D* system)
    : ParticleEmitter(system)
{
}
ParticlePointEmitter::~ParticlePointEmitter()
{
}
void   ParticlePointEmitter::initParticlePos(Particle3D* particle)
{
    if (_emitterConfig.followPosition)   
    {       
        particle->startPos.x = _parSystem->convertToWorldSpace(Vec2::ZERO).x;      
        particle->startPos.y = _parSystem->convertToWorldSpace(Vec2::ZERO).y;   
    }
    particle->position=Vec3::ZERO;
}
bool    ParticlePointEmitter::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc)
{
    tinyxml2::XMLElement *pElement = xmlDoc->NewElement("ParticlePointEmitter");
    ParticleEmitter::save(pElement,xmlDoc);
    xmlDoc->LinkEndChild(pElement);
    return true;
}

NS_CC_END
