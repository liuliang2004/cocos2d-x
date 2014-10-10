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

#ifndef __CCPARTICLEROTATIONAFFECTOR_H__
#define __CCPARTICLEROTATIONAFFECTOR_H__
#include "3d/CCParticleAffector.h"
NS_CC_BEGIN
struct RotAffectorConfig
{
    int   type;
    int   rotationEnd;
};
/**
Defines particle rot Affector
It is a compulsory component for particle system
It updates particle rot
*/
class ParticleRotationAffector  : public ParticleAffector
{
public:
    ParticleRotationAffector(ParticleSystem3D* system);
    virtual ~ParticleRotationAffector();
     //init particle rot affector
    virtual void initAffector(Particle3D* p);
    virtual void updateAffector(Particle3D* p,float dt);
    virtual bool load(tinyxml2::XMLElement* element);
    virtual bool save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc);
private:
    RotAffectorConfig _rotAffectorConfig;
};
NS_CC_END
#endif // __SPRITE3D_H_
