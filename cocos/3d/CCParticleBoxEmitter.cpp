
#include "3d/CCParticleBoxEmitter.h"
#include "3d/CCParticleSystem3D.h" 
#include "tinyxml2.h"
NS_CC_BEGIN

ParticleBoxEmitter::ParticleBoxEmitter(ParticleSystem3D* system)
    : ParticleEmitter(system)
{
}
ParticleBoxEmitter::~ParticleBoxEmitter()
{
}
void   ParticleBoxEmitter::initParticlePos(Particle3D* particle)
{
    particle->position.x =_boxeEmitterConfig.boxSize.x*0.5*CCRANDOM_MINUS1_1();      
    particle->position.y =_boxeEmitterConfig.boxSize.y*0.5*CCRANDOM_MINUS1_1();        
    particle->position.z =_boxeEmitterConfig.boxSize.z*0.5*CCRANDOM_MINUS1_1();
}
bool  ParticleBoxEmitter::load(tinyxml2::XMLElement* element)
{
    ParticleEmitter::load(element);
    element->QueryFloatAttribute("boxSizeX",&_boxeEmitterConfig.boxSize.x);
    element->QueryFloatAttribute("boxSizeY",&_boxeEmitterConfig.boxSize.y);
    element->QueryFloatAttribute("boxSizeZ",&_boxeEmitterConfig.boxSize.z);
    return true;
}
bool    ParticleBoxEmitter::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc)
{
    tinyxml2::XMLElement *pElement = xmlDoc->NewElement("ParticleBoxEmitter");
    if(pElement)
    {
        ParticleEmitter::save(pElement,xmlDoc);
        pElement->SetAttribute("boxSizeX",_boxeEmitterConfig.boxSize.x);
        pElement->SetAttribute("boxSizeY",_boxeEmitterConfig.boxSize.y);
        pElement->SetAttribute("boxSizeZ",_boxeEmitterConfig.boxSize.z);
        xmlDoc->LinkEndChild(pElement);
    }
    return true;
}

NS_CC_END
