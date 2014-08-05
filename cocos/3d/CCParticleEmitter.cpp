
#include "3d/CCParticleEmitter.h"
#include "3d/CCParticleSystem3D.h" 
#include "base/ccMacros.h"
#include "tinyxml2.h"
NS_CC_BEGIN
    ParticleEmitter::ParticleEmitter(ParticleSystem3D* system) :
    _parSystem(system)
{
}
ParticleEmitter::~ParticleEmitter()
{
}
void   ParticleEmitter::initParticleLife(Particle3D* particle)
{
    particle->timeToLive = _emitterConfig.life + _emitterConfig.lifeVar * CCRANDOM_MINUS1_1();
    particle->timeToLive = MAX(0, particle->timeToLive);
}
void   ParticleEmitter::initParticleDirection(Particle3D* particle)
{
    if (_emitterConfig.dirType == DIR_SPHERE)
    {  
        if (particle->position.isZero())
        {
            Mat4 rot,rotX,rotY,rotZ;
            Mat4::createRotationX(CC_DEGREES_TO_RADIANS(generateScalar(0, 360)), &rotX);
            Mat4::createRotationY(CC_DEGREES_TO_RADIANS(generateScalar(0, 360)), &rotY);
            Mat4::createRotationZ(CC_DEGREES_TO_RADIANS(generateScalar(0, 360)), &rotZ);
            rot =rotX*rotY*rotZ;
            particle->velocity = rot * Vec3::UNIT_Y;
        }
        else
        {
            particle->velocity = particle->position;
        }
    }
    else if (_emitterConfig.dirType ==DIR_PLANAR)
    {
        particle->velocity=_emitterConfig.velocityAxis;  
    }
    particle->velocity.normalize();
    float speed =_emitterConfig.startSpeed + _emitterConfig.startSpeedVar * CCRANDOM_MINUS1_1();
    particle->velocity*=speed;

}
void   ParticleEmitter::initParticleColor(Particle3D* particle)
{
    particle->color.r = clampf(_emitterConfig.startColor.x + _emitterConfig.startColorVar.x * CCRANDOM_MINUS1_1(), 0, 1);
    particle->color.g = clampf(_emitterConfig.startColor.y + _emitterConfig.startColorVar.y * CCRANDOM_MINUS1_1(), 0, 1);
    particle->color.b = clampf(_emitterConfig.startColor.z + _emitterConfig.startColorVar.z * CCRANDOM_MINUS1_1(), 0, 1);
    particle->color.a = clampf(_emitterConfig.startColor.w + _emitterConfig.startColorVar.w * CCRANDOM_MINUS1_1(), 0, 1);
}
void   ParticleEmitter::initParticleScale(Particle3D* particle)
{
    particle->scale = _emitterConfig.startScale + _emitterConfig.startScaleVar * CCRANDOM_MINUS1_1();
}
void   ParticleEmitter::initParticleUV(Particle3D* particle)
{
    particle->uvRect = _emitterConfig.uv;
}
void   ParticleEmitter::initParticleRotation(Particle3D* particle)
{
    particle->rotation = _emitterConfig.startRotation + _emitterConfig.startRotationVar * CCRANDOM_MINUS1_1();
}
float   ParticleEmitter::generateScalar(float min, float max)
{
    return min + (max - min) * CCRANDOM_0_1();
}
bool   ParticleEmitter::load(tinyxml2::XMLElement* element)
{
    const tinyxml2:: XMLAttribute*	curAttribute=element->FirstAttribute();
    while (curAttribute) 
    {  

        if(0==strcmp(curAttribute->Name(),"emitDelay"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.emitDelay);
        }
        else if(0==strcmp(curAttribute->Name(),"emitDuration"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.emitDuration);
        }
        else if(0==strcmp(curAttribute->Name(),"emitRate"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.emitRate);
        }
        else if(0==strcmp(curAttribute->Name(),"life"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.life);
        }
        else if(0==strcmp(curAttribute->Name(),"lifeVar"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.lifeVar);
        }
        else if(0==strcmp(curAttribute->Name(),"startColorR"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startColor.x);
        }
        else if(0==strcmp(curAttribute->Name(),"startColorG"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startColor.y);
        }
        else if(0==strcmp(curAttribute->Name(),"startColorB"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startColor.z);
        }
        else if(0==strcmp(curAttribute->Name(),"startColorA"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startColor.w);
        }
        else if(0==strcmp(curAttribute->Name(),"startColorVarR"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startColorVar.x);
        }
        else if(0==strcmp(curAttribute->Name(),"startColorVarG"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startColorVar.y);
        }
        else if(0==strcmp(curAttribute->Name(),"startColorVarB"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startColorVar.z);
        }
        else if(0==strcmp(curAttribute->Name(),"startColorVarA"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startColorVar.w);
        }
        else if(0==strcmp(curAttribute->Name(),"dirType"))
        {
            curAttribute->QueryIntValue(&_emitterConfig.dirType);
        }
        else if(0==strcmp(curAttribute->Name(),"velocityAxisX"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.velocityAxis.x);
        }
        else if(0==strcmp(curAttribute->Name(),"velocityAxisY"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.velocityAxis.y);
        }
        else if(0==strcmp(curAttribute->Name(),"velocityAxisZ"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.velocityAxis.z);
        }
        else if(0==strcmp(curAttribute->Name(),"startSpeed"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startSpeed);
        } 
        else if(0==strcmp(curAttribute->Name(),"startSpeedVar"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startSpeedVar);
        } 
        else if(0==strcmp(curAttribute->Name(),"startScale"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startScale);
        }
        else if(0==strcmp(curAttribute->Name(),"startScaleVar"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.startScaleVar);
        }
        else if(0==strcmp(curAttribute->Name(),"startRotation"))
        {
            curAttribute->QueryIntValue(&_emitterConfig.startRotation);
        }
        else if(0==strcmp(curAttribute->Name(),"startRotationVar"))
        {
            curAttribute->QueryIntValue(&_emitterConfig.startRotationVar);
        }
        else if(0==strcmp(curAttribute->Name(),"uvRectLeft"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.uv.x);
        }
        else if(0==strcmp(curAttribute->Name(),"uvRectTop"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.uv.y);
        }
        else if(0==strcmp(curAttribute->Name(),"uvRectRight"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.uv.z);
        }
        else if(0==strcmp(curAttribute->Name(),"uvRectBottom"))
        {
            curAttribute->QueryFloatValue(&_emitterConfig.uv.w);
        }
        curAttribute = curAttribute->Next();  
    }
    return true;
}
bool   ParticleEmitter::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc)
{
    element->SetAttribute("emitDelay",_emitterConfig.emitDelay);
    element->SetAttribute("emitDuration",_emitterConfig.emitDuration);
    element->SetAttribute("emitRate",_emitterConfig.emitRate);
    element->SetAttribute("life",_emitterConfig.life);
    element->SetAttribute("lifeVar",_emitterConfig.lifeVar);
    element->SetAttribute("startColorR",_emitterConfig.startColor.x);
    element->SetAttribute("startColorG",_emitterConfig.startColor.y);
    element->SetAttribute("startColorB",_emitterConfig.startColor.z);
    element->SetAttribute("startColorA",_emitterConfig.startColor.w);
    element->SetAttribute("startColorVarR",_emitterConfig.startColorVar.x);
    element->SetAttribute("startColorVarG",_emitterConfig.startColorVar.y);
    element->SetAttribute("startColorVarB",_emitterConfig.startColorVar.z);
    element->SetAttribute("startColorVarA",_emitterConfig.startColorVar.w);
    element->SetAttribute("dirType",_emitterConfig.dirType);
    element->SetAttribute("velocityAxisX",_emitterConfig.velocityAxis.x);
    element->SetAttribute("velocityAxisY",_emitterConfig.velocityAxis.y);
    element->SetAttribute("velocityAxisZ",_emitterConfig.velocityAxis.z);
    element->SetAttribute("startSpeed",_emitterConfig.startSpeed);
    element->SetAttribute("startSpeedVar",_emitterConfig.startSpeedVar);
    element->SetAttribute("startScale",_emitterConfig.startScale);
    element->SetAttribute("startScaleVar",_emitterConfig.startScaleVar);
    element->SetAttribute("startRotation",_emitterConfig.startRotation);
    element->SetAttribute("startRotationVar",_emitterConfig.startRotationVar);
    element->SetAttribute("uvRectLeft",_emitterConfig.uv.x);
    element->SetAttribute("uvRectTop",_emitterConfig.uv.y);
    element->SetAttribute("uvRectRight",_emitterConfig.uv.z);
    element->SetAttribute("uvRectBottom",_emitterConfig.uv.w);
    return true;
}
const float&    ParticleEmitter::getEmitDelay()
{
    return _emitterConfig.emitDelay;
}
const float&    ParticleEmitter::getEmitRate()
{
    return _emitterConfig.emitRate;
}
const float&   ParticleEmitter::getEmitDuration()
{
    return _emitterConfig.emitDuration;
}
const bool&    ParticleEmitter::getFollowPosition()
{
    return  _emitterConfig.followPosition;
}
NS_CC_END
