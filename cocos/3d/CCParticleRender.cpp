
#include "3d/CCParticleRender.h"
#include "3d/CCParticleSystem3D.h" 
NS_CC_BEGIN

ParticleRender::ParticleRender(ParticleSystem3D* system) :
 _parSystem(system)
{
	
}
ParticleRender::~ParticleRender()
{
}
void ParticleRender::update(float dt)
{
}
bool ParticleRender::load(tinyxml2::XMLElement* element)
{
    return true;
}
bool ParticleRender::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc)
{
    return true;
}

NS_CC_END