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

#include "3d/CCParticleColorAffector.h"
#include "base/CCDirector.h"
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

    ParticleColorAffector::ParticleColorAffector(ParticleSystem3D* system):
    ParticleAffector(system)
{
}
ParticleColorAffector::~ParticleColorAffector()
{

}
bool ParticleColorAffector::load(tinyxml2::XMLElement* element)
{
    const tinyxml2:: XMLAttribute*	curAttribute=element->FirstAttribute();
    while (curAttribute) 
    {  
        if(0==strcmp(curAttribute->Name(),"type"))
        {
            curAttribute->QueryIntValue(&_colorAffectorConfig.type);
        }
        else if(0==strcmp(curAttribute->Name(),"endColorR"))
        {
            curAttribute->QueryFloatValue(&_colorAffectorConfig.endColor.x);
        }
        else if(0==strcmp(curAttribute->Name(),"endColorG"))
        {
            curAttribute->QueryFloatValue(&_colorAffectorConfig.endColor.y);
        }
        else if(0==strcmp(curAttribute->Name(),"endColorB"))
        {
            curAttribute->QueryFloatValue(&_colorAffectorConfig.endColor.z);
        }
        else if(0==strcmp(curAttribute->Name(),"endColorA"))
        {
            curAttribute->QueryFloatValue(&_colorAffectorConfig.endColor.w);
        }
        curAttribute = curAttribute->Next();  
    }
    return true;
}
bool ParticleColorAffector::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc)
{
    tinyxml2::XMLElement *pAffectElement = xmlDoc->NewElement("ParticleColorAffector");
    if(pAffectElement)
    {
        pAffectElement->SetAttribute("type",_colorAffectorConfig.type);
        pAffectElement->SetAttribute("endColorR",_colorAffectorConfig.endColor.x);
        pAffectElement->SetAttribute("endColorG",_colorAffectorConfig.endColor.y);
        pAffectElement->SetAttribute("endColorB",_colorAffectorConfig.endColor.z);
        pAffectElement->SetAttribute("endColorA",_colorAffectorConfig.endColor.w);
        element->LinkEndChild(pAffectElement);
    }
    return true;
}
void ParticleColorAffector::initAffector(Particle3D* p)
{
    p->deltaColor.r = (_colorAffectorConfig.endColor.x - p->color.r) / p->timeToLive;
    p->deltaColor.g = (_colorAffectorConfig.endColor.y - p->color.g) / p->timeToLive;
    p->deltaColor.b = (_colorAffectorConfig.endColor.z - p->color.b) / p->timeToLive;
    p->deltaColor.a = (_colorAffectorConfig.endColor.w - p->color.a) / p->timeToLive;
}
void ParticleColorAffector::updateAffector(Particle3D* p,float dt)
{

    p->color.r += (p->deltaColor.r * dt);
    p->color.g += (p->deltaColor.g * dt);
    p->color.b += (p->deltaColor.b * dt);
    p->color.a += (p->deltaColor.a * dt);
}
NS_CC_END
