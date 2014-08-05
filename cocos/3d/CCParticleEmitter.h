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
#ifndef __CCPARTICLEMITTER_H__
#define __CCPARTICLEMITTER_H__
#include "2d/CCNode.h"
namespace tinyxml2
{
    class XMLElement;
    class XMLAttribute;
    class XMLDocument; 
}
NS_CC_BEGIN
struct  Particle3D;
class   ParticleSystem3D;
struct ParEmitterConfig
{ 
    float emitDelay;
    float emitDuration; 
    float emitRate;
    bool  followPosition;
    //life
    float life;
    float lifeVar; 
    //color
    Vec4  startColor;
    Vec4  startColorVar;
    //velocity
    int   dirType; 
    Vec3  velocityAxis;
    float startSpeed; 
    float startSpeedVar;
    //scale
    float startScale; 
    float startScaleVar;
    //rotation
    int startRotation;
    int startRotationVar;
    //uv
    Vec4  uv;
};
class ParticleEmitter 
{
public:	
    ParticleEmitter(ParticleSystem3D* system);
    virtual ~ParticleEmitter();
    virtual void   initParticleLife(Particle3D* particle);
    //Initializes a particle   direction
    virtual void   initParticleDirection(Particle3D* particle);
    //Initializes a particle   pos
    virtual void   initParticlePos(Particle3D* particle)=0;
    //Initializes a particle   color
    virtual void   initParticleColor(Particle3D* particle);
    //Initializes a particle   scale
    virtual void   initParticleScale(Particle3D* particle);
    //Initializes a particle   uv
    virtual void   initParticleUV(Particle3D* particle);
    //Initializes a particle   rotation
    virtual void   initParticleRotation(Particle3D* particle);
     /**
    * load & save particle system .particle.
    */
    virtual bool   load(tinyxml2::XMLElement* element);
    virtual bool   save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc);
    const float&   getEmitDelay();
    const float&   getEmitRate();
    const float&   getEmitDuration();
    const bool&    getFollowPosition();
private:
     /**
     * Generates a scalar within the range defined by min and max.
     */
    float  generateScalar(float min, float max);
protected:
    ParticleSystem3D* _parSystem;
protected:
    ParEmitterConfig  _emitterConfig;
};
NS_CC_END
#endif 
