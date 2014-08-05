/****************************************************************************
Copyright (c) 2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "3d/CCParticleRotationAffector.h"
#include "base/CCDirector.h"
#include "base/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "3d/CCParticleSystem3D.h"
#include "deprecated/CCString.h" // For StringUtils::format
#include "3d/CCParticleSystem3D.h" 
#include "tinyxml2.h"
NS_CC_BEGIN

ParticleRotationAffector::ParticleRotationAffector(ParticleSystem3D* system):
    ParticleAffector(system)
{
}
ParticleRotationAffector::~ParticleRotationAffector()
{

}
void ParticleRotationAffector::initAffector(Particle3D* p)
{
    p->deltaRotation = (_rotAffectorConfig.rotationEnd - p->rotation) / p->timeToLive;

}
void ParticleRotationAffector::updateAffector(Particle3D* p,float dt)
{
    p->rotation+=p->deltaRotation*dt;
}
bool ParticleRotationAffector::load(tinyxml2::XMLElement* element)
{
    const tinyxml2:: XMLAttribute*	curAttribute=element->FirstAttribute();
    while (curAttribute) 
    {  
        if(0==strcmp(curAttribute->Name(),"type"))
        {
            curAttribute->QueryIntValue(&_rotAffectorConfig.type);
        }
        else if(0==strcmp(curAttribute->Name(),"rotationEnd"))
        {
            curAttribute->QueryIntValue(&_rotAffectorConfig.rotationEnd);
        }
        curAttribute = curAttribute->Next();  
    }
    return true;
}
bool ParticleRotationAffector::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc)
{
    tinyxml2::XMLElement *pAffectElement = xmlDoc->NewElement("ParticleRotationAffector");
    if(pAffectElement)
    {
        pAffectElement->SetAttribute("type",_rotAffectorConfig.type);
        pAffectElement->SetAttribute("rotationEnd",_rotAffectorConfig.rotationEnd);
        element->LinkEndChild(pAffectElement);
    }
    return true;
}

NS_CC_END
