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

#ifndef __CCPARTICLEAFFECTOR_H__
#define __CCPARTICLEAFFECTOR_H__

#include <vector>
#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "base/CCProtocols.h"
#include "2d/CCNode.h"
namespace tinyxml2
{
    class XMLElement;
    class XMLDocument; 
}
NS_CC_BEGIN
struct Particle3D;
class ParticleSystem3D;
/**
Base class of particle Affector
A class affect the particle
*/
class ParticleAffector 
{
public:
    ParticleAffector(ParticleSystem3D* system);
    virtual ~ParticleAffector();
    //init particle affector
    virtual void initAffector(Particle3D* p){}
    //update particle affector
    virtual void updateAffector(Particle3D* p,float dt){}
    //load particle affector data
    virtual bool load(tinyxml2::XMLElement* element);
    //save particle affector data
    virtual bool save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc);
protected:
    ParticleSystem3D* _parSystem;
};

struct ColorAffectorConfig
{
    int   type;
    Vec4  endColor;	
};
/**
Defines particle color Affector
It is a compulsory component for particle system
It updates particle color
*/
class ColorAffector  : public ParticleAffector
{
public:
    ColorAffector(ParticleSystem3D* system);
    virtual ~ColorAffector();
    //init particle color affector
    virtual void initAffector(Particle3D* p);
    virtual void updateAffector(Particle3D* p,float dt);
    virtual bool load(tinyxml2::XMLElement* element);
    virtual bool save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc);
    void  setDefaultProperty(const ColorAffectorConfig& config);

private:
    ColorAffectorConfig _colorAffectorConfig;

};
struct ScaleAffectorConfig
{
    int   type;
    float endScale;	
};
/**
Defines particle scale Affector
It is a compulsory component for particle system
It updates particle scale
*/
class ScaleAffector  : public ParticleAffector
{
public:
    ScaleAffector(ParticleSystem3D* system);
    virtual ~ScaleAffector();
     //init particle scale affector
    virtual void initAffector(Particle3D* p);
    virtual void updateAffector(Particle3D* p,float dt);
    virtual bool load(tinyxml2::XMLElement* element);
    virtual bool save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc);
    void  setDefaultProperty(const ScaleAffectorConfig& config);
private:
    ScaleAffectorConfig _scaleAffectorConfig;
};
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
class RotAffector  : public ParticleAffector
{
public:
    RotAffector(ParticleSystem3D* system);
    virtual ~RotAffector();
     //init particle rot affector
    virtual void initAffector(Particle3D* p);
    virtual void updateAffector(Particle3D* p,float dt);
    virtual bool load(tinyxml2::XMLElement* element);
    virtual bool save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc);
    void  setDefaultProperty(const RotAffectorConfig& config);

private:
    RotAffectorConfig _rotAffectorConfig;
};
NS_CC_END
#endif // __SPRITE3D_H_
