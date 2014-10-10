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

#ifndef __CCPARTICLSYSTEM3D_H__
#define __CCPARTICLSYSTEM3D_H__
#include <vector>
#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "renderer/CCQuadCommand.h"
namespace tinyxml2
{
    class XMLElement;
    class XMLDocument; 
}
NS_CC_BEGIN
class GLProgramState;
class Texture2D;
class ParticleAffector;
class ParticleEmitter;
class ParticleRender;
// particle System config data
struct ParSystemConfig
{  
    int totalParticles;
    char  textureName[32];
    int   blendType;
};
// particle Emitter Type 
enum  EMITTYPE
{
    EMIT_POINT,         
    EMIT_BOX,          
    EMIT_SPHERE,        
};
// particle direction Type 
enum DIRECTION_TYPE
{
    DIR_PLANAR,
    DIR_SPHERE,
};
// render billboard Type 
enum BILLBOARD_TYPE
{
    BILLBOARD,
    XY,
    BILLBOARD_SELF
};
/**
Structure that contains the values of each particle
*/
struct Particle3D
{
    int     index;          
    int     totalIndex;
    Vec3    position;
    Vec3    startPos;
    Vec3    velocity;
    float   scale;
    float   deltaScale;
    Color4F deltaColor;
    Color4F color;
    float   timeToLive;
    Vec4    uvRect;	
    float   rotation;
    float   deltaRotation;
};

class CC_DLL ParticleSystem3D : public Node , public BlendProtocol{
public:	
    static ParticleSystem3D * create(const std::string& particleFile);
    static ParticleSystem3D * create();
    ParticleSystem3D();
    virtual ~ParticleSystem3D();
    virtual void  onEnter() override;
    /**
    * particle system control.
    */
    void start();
    void stop();
    void pause();
    void resume();
    virtual void updateParticleSystem(float dt) ;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    //set texture
    void setTexture(const std::string& texFile);
    void setTexture(Texture2D* texture);
    Texture2D* getTexture()const;
    // overrides
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    virtual const BlendFunc &getBlendFunc() const override;
    /**
    * add Affector to particle system to affect particles movement
    */
    void addAffector(ParticleAffector* affector);

    /**
    * remove particle system Affector
    */
    void removeAffector(ParticleAffector* affector);
    void setParticleEmitter(ParticleEmitter* parEmitter);
    void setParticleRender(ParticleRender* parRender);
    /**
    * load & save particle system .particle.
    */
    bool load(const std::string& fileName);
    bool save(const std::string& szFile);
    void  setTotalParticles(int tp);
    int   getTotalParticle()const;
    Particle3D* getParticle(int index)const;
private:
    //update all particle
    void   updateParticle(float dt);
    //Add a particle to the emitter
    bool   addParticle();
    //Initializes a particle
    void   initParticle(Particle3D* particle);
    void   emitterParticle(float dt);
    bool   isFull();
    /**
    * load & save particle system .particle.
    */
    bool load(tinyxml2::XMLElement* element);
    bool save(tinyxml2::XMLDocument* xmlDoc);
protected:
    Particle3D*         _particles;         //Array of particles
    ParticleEmitter*    _particleEmitter;
    ParticleRender*     _particleRender;
    ParSystemConfig     _parSystemConfig;    //particle emitter config
    int                 _particleIdx;      // particle idx
    int                 _particleCount;    //Quantity of particles that are being simulated at the moment 
    bool                _started;
    float               _timeRunning;
    float               _emitCounter;
    Texture2D*          _texture;       // quad texture
    BlendFunc           _blend;
    std::vector<ParticleAffector*> _parAffectors;
    timeval             _lastTime;
};
NS_CC_END
#endif // __SPRITE3D_H_
