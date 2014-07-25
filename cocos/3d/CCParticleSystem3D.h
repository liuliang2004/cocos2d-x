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
// particle Emitter config data
struct ParEmitterConfig
{  
    int totalParticles;
    float emitDelay;    
    float emitDuration; 
    int   emitType;
    Vec3  emitPos;
    float emitRate;   
    Vec3  boxSize; 
    float sphereRadius;
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

    int startRotation;
    int startRotationVar;
    //uv
    Vec4  uvRect;
    //render
    int   renderType;
    Vec2  billboardSize; 
    int   billboardType;
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
/** ParticleSystem3D: A particleSystem can be loaded from particle files, .particle, then can be drawed as particleSystem */
class ParticleSystem3D : public Node , public BlendProtocol
{
public:	
    static ParticleSystem3D * create(const std::string& particleFile);
    static ParticleSystem3D * create();
    ParticleSystem3D();
    virtual ~ParticleSystem3D();
    /**
    * particle state.
    */
    enum ParticleState
    {
        STOP,
        RUNNING,
        PAUSE,
    };
    void  setTotalParticles(int tp);
    virtual void  onEnter() override;
    /**
    * is particle system start ?
    */
    bool isStarted() const;
    /**
    * particle system control.
    */
    void start();
    void stop();
    void pause();
    void resume();
    virtual void update(float dt) ;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    //set texture
    void setTexture(const std::string& texFile);
    void setTexture(Texture2D* texture);
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
    /**
    * load & save particle system .particle.
    */
    bool load(const std::string& fileName);
    bool save(const std::string& szFile);
private:
      //update a billboard particle
    void   updateBillboardParticle(Particle3D* particle,const Vec3& newPosition);
    //emitted particle
    void   emitterParticle(float dt);
    //update all particle
    void   updateParticle(float dt);
    //Add a particle to the emitter
    bool   addParticle();
    void   initParticleLife(Particle3D* particle);
    bool   isFull();
     //Initializes a particle   direction
    void   initParticleDirection(Particle3D* particle);
    //Initializes a particle   pos
    void   initParticlePos(Particle3D* particle);
     //Initializes a particle   color
    void   initParticleColor(Particle3D* particle);
     //Initializes a particle   scale
    void   initParticleScale(Particle3D* particle);
    //Initializes a particle   uv
    void   initParticleUV(Particle3D* particle);
     //Initializes a particle   rotation
    void   initParticleRotation(Particle3D* particle);
     /**
     * Generates a scalar within the range defined by min and max.
     */
    float  generateScalar(float min, float max);
    /**
    * load & save particle system .particle.
    */
    bool load(tinyxml2::XMLElement* element);
    bool save(tinyxml2::XMLDocument* xmlDoc);
protected:
    Particle3D*         _particles;         //Array of particles
    ParEmitterConfig    _emitterConfig;    //particle emitter config
    int                 _particleIdx;      // particle idx
    int                 _particleCount;    //Quantity of particles that are being simulated at the moment 
    float               _emitCounter;   //! How many particles can be emitted per second
    bool                _started;
    ParticleState       _state;        // particle system state
    float               _timeRunning; // particle system running time
    Vec3                _cameraRight; // camera right dir
    Vec3                _cameraUp;    // camera up dir
    Vec3                _CamDir;      // camera lookat dir
    V3F_C4B_T2F_Quad*   _quads;       // quads to be rendered
    QuadCommand        _quadCommand;  // quad command
    Texture2D*         _texture;       // quad texture
    BlendFunc          _blend;
    std::vector<ParticleAffector*> _parAffectors;
};
NS_CC_END
#endif // __SPRITE3D_H_
