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

#include "3d/CCParticleSystem3D.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "deprecated/CCString.h" // For StringUtils::format
#include "base/CCConfiguration.h"
#include "3d/CCParticleAffector.h" 
#include "tinyxml2.h"
#include "3d/CCParticlePointEmitter.h"
#include "3d/CCParticleBoxEmitter.h"
#include "3d/CCParticleBillboardRender.h"
#include "3d/CCParticleMeshRender.h"
#include "3d/CCParticleColorAffector.h"
#include "3d/CCParticleRotationAffector.h"
#include "3d/CCParticleScaleAffector.h"
NS_CC_BEGIN
    ParticleSystem3D * ParticleSystem3D::create(const std::string& particleFile)
{
    ParticleSystem3D *ret = new (std::nothrow) ParticleSystem3D();
    if (ret && ret->load(particleFile))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}
ParticleSystem3D * ParticleSystem3D::create()
{
    ParticleSystem3D *ret = new (std::nothrow) ParticleSystem3D();
    if (ret)
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}
ParticleSystem3D::ParticleSystem3D():
    _particles(nullptr)
    ,_particleIdx(0)
    ,_particleCount(0)
    ,_texture(nullptr)
    ,_particleEmitter(nullptr)
    ,_particleRender(nullptr)
{
    _started = false;
    _blend = BlendFunc::ADDITIVE;
    gettimeofday(&_lastTime, NULL);
}
ParticleSystem3D::~ParticleSystem3D()
{
    CC_SAFE_FREE(_particles);
    CC_SAFE_DELETE(_particleEmitter);
    CC_SAFE_DELETE(_particleRender);
    for( std::vector<ParticleAffector*>::iterator iter=_parAffectors.begin(); iter!=_parAffectors.end(); ++iter )
    {
        CC_SAFE_DELETE(*iter);
    }
	_parAffectors.clear();
}

void ParticleSystem3D::updateParticleSystem(float dt) 
{  
    if(!_started)
    {
        return;
    }
    if(!_particleEmitter || !_particleRender)
    {
        return;
    }
    if (_particles)
    {
        if(_particleRender)
        {
            _particleRender->update(dt);
        }  
        emitterParticle(dt);
        updateParticle(dt);
    }
}
bool ParticleSystem3D::isFull()
{
    return (_particleCount == _parSystemConfig.totalParticles);
}
void ParticleSystem3D::onEnter()
{
    Node::onEnter();
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    // update after action in run!
    this->scheduleUpdateWithPriority(1);
}
//add particle
bool  ParticleSystem3D::addParticle()
{
    if (this->isFull())
    {
        return false;
    }
    Particle3D * particle = &_particles[ _particleCount ];
    if(particle)
    {   
        initParticle(particle);
        for(std::vector<ParticleAffector*>::iterator iter =_parAffectors.begin(); iter!=_parAffectors.end(); ++iter)
        {
            (*iter)->initAffector(particle);
        }
    }
    ++_particleCount;
    return true;
}
void   ParticleSystem3D::initParticle(Particle3D* particle)
{
    if(_particleEmitter)
    {
        _particleEmitter->initParticleLife(particle);
        _particleEmitter->initParticlePos(particle);
        _particleEmitter->initParticleDirection(particle);
        _particleEmitter->initParticleColor(particle);
        _particleEmitter->initParticleScale(particle);
        _particleEmitter->initParticleUV(particle);
        _particleEmitter->initParticleRotation(particle);
    }
}
void ParticleSystem3D::start()
{
    resume();
}
void ParticleSystem3D::pause()
{ 
}
void ParticleSystem3D::resume()
{
    _started=true;
    _timeRunning = 0.0f;
    _emitCounter=0;
}

void ParticleSystem3D::stop()
{
    _started=false;
}
void ParticleSystem3D::setTexture(const std::string& texFile)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
    if( tex && _texture != tex ) {
        CC_SAFE_RETAIN(tex);
        CC_SAFE_RELEASE_NULL(_texture);
        _texture = tex;
    }
}
void ParticleSystem3D::setTexture(Texture2D* texture)
{
    if(_texture != texture) {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE_NULL(_texture);
        _texture = texture;
    }
}
Texture2D* ParticleSystem3D::getTexture()const
{
    return _texture;
}
void ParticleSystem3D::setBlendFunc(const BlendFunc &blendFunc)
{
    if(_blend.src != blendFunc.src || _blend.dst != blendFunc.dst)
    {
        _blend = blendFunc;
    }
}
const BlendFunc& ParticleSystem3D::getBlendFunc() const
{
    return _blend;
}

void ParticleSystem3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    timeval	tNowTime;
    gettimeofday(&tNowTime, NULL);
    float fDeltaTime = (tNowTime.tv_sec - _lastTime.tv_sec) + (tNowTime.tv_usec - _lastTime.tv_usec) / 1000000.0f;
	_lastTime = tNowTime;
    updateParticleSystem(fDeltaTime);
    if(_particleIdx > 0)
    {
        if(_particleRender)
        {
            _particleRender->draw(renderer,transform,flags,_particleIdx);
        }
    }
}
void ParticleSystem3D::setTotalParticles(int tp)
{
    _parSystemConfig.totalParticles = tp;
    CC_SAFE_FREE(_particles);
    _particles = (Particle3D*)calloc(tp, sizeof(Particle3D));
    if(_particleEmitter)
    {
        _particleRender->reSizeCapacity(tp);
    }
}
void   ParticleSystem3D::updateParticle(float dt)
{
    _particleIdx = 0;
    Vec3 currentPosition = Vec3::ZERO;
    if (_particleEmitter->getFollowPosition())
    {
        currentPosition.x = convertToWorldSpace(Vec2::ZERO).x;
        currentPosition.y = convertToWorldSpace(Vec2::ZERO).y;
    }
    while (_particleIdx < _particleCount)
    {
        Particle3D *p = &_particles[_particleIdx];
        p->timeToLive -= dt;
        if (p->timeToLive > 0.0f)
        {

            for(std::vector<ParticleAffector*>::iterator iter =_parAffectors.begin(); iter!=_parAffectors.end(); ++iter)
            {
                (*iter)->updateAffector(p,dt);
            }
            p->position += p->velocity * dt;
            Vec3    newPos;
            if (_particleEmitter->getFollowPosition())
            {
                Vec3 diff = currentPosition - p->startPos;
                newPos = p->position - diff;
            } 
            else
            {
                newPos = p->position;
            }
            if(_particleRender)
            {
                _particleRender->updateParticle(p,_particleIdx,dt,newPos);
            } 
            ++_particleIdx;
        }
        else 
        {
            // life < 0
            if( _particleIdx != _particleCount-1 )
            {
                _particles[_particleIdx] = _particles[_particleCount-1];
            }
            --_particleCount;
        }
    }
}
void ParticleSystem3D::addAffector(ParticleAffector* affector)
{
    _parAffectors.push_back(affector);

}
void ParticleSystem3D::removeAffector(ParticleAffector* affector)
{
    for (size_t i = 0; i < _parAffectors.size(); i++)
    {
        if (_parAffectors[i] == affector)
        {
            delete affector;
            _parAffectors.erase(_parAffectors.begin() + i);
            break;
        }
    }
}
bool ParticleSystem3D::load(const std::string& fileName)
{
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
    ssize_t nSize; 
    const char* pXmlBuffer = (const char*)FileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &nSize);
    if(NULL == pXmlBuffer)  
    {  
        CCLOG("can not read xml file"); 
        delete pDoc;
        return false;  
    }  
    pDoc->Parse(pXmlBuffer, nSize);  
    delete[] pXmlBuffer;
    tinyxml2::XMLElement *rootElement = pDoc->RootElement();
    if(!rootElement)
    {
        delete pDoc;
        return false;
    }
    load(rootElement);
    delete pDoc;
    return true;
}
bool ParticleSystem3D::save(const std::string& szFile)
{ 
    tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
    if (NULL==xmlDoc) {

        return false;
    }
    //xmlÉùÃ÷
    tinyxml2::XMLDeclaration *pDel = xmlDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    if (NULL==pDel) {

        delete xmlDoc;
        return false;
    }
    xmlDoc->LinkEndChild(pDel);
    xmlDoc->SaveFile(szFile.c_str());
    delete xmlDoc;
    return true;
}
bool ParticleSystem3D::load(tinyxml2::XMLElement* element)
{
    CC_SAFE_DELETE(_particleEmitter);
    CC_SAFE_DELETE(_particleRender);
    const tinyxml2:: XMLAttribute*	curAttribute=element->FirstAttribute();
    while (curAttribute) 
    {  
        if(0==strcmp(curAttribute->Name(),"totalParticles"))
        {
            curAttribute->QueryIntValue(&_parSystemConfig.totalParticles);
        }
        else if(0==strcmp(curAttribute->Name(),"textureName"))
        {   
            strcpy_s(_parSystemConfig.textureName,curAttribute->Value());
        }
        else if(0==strcmp(curAttribute->Name(),"blendType"))
        {
            curAttribute->QueryIntValue(&_parSystemConfig.blendType);
        }
        curAttribute = curAttribute->Next();  
    } 
    tinyxml2::XMLElement *childElement = element->FirstChildElement();
    while(childElement)  
    {  
        ParticleAffector*  particleAffector=NULL;
        if(0==strcmp(childElement->Name(),"ParticlePointEmitter"))
        {
            _particleEmitter= new ParticlePointEmitter(this);
            if(_particleEmitter)
            {
                _particleEmitter->load(childElement);
            }
        }
        else if(0==strcmp(childElement->Name(),"ParticleBoxEmitter"))
        {
            _particleEmitter= new ParticleBoxEmitter(this);
            if(_particleEmitter)
            {
                _particleEmitter->load(childElement);
            }
        }
        else if(0==strcmp(childElement->Name(),"ParticleBillboardRender"))
        {
            _particleRender = new 	ParticleBillboardRender(this);
            if(_particleRender)
            {
                _particleRender->load(childElement);
            }
        }
        else if(0==strcmp(childElement->Name(),"ParticleMeshRender"))
        {
            _particleRender = new 	ParticleMeshRender(this);
            if(_particleRender)
            {
                _particleRender->load(childElement);
            }
        }
        else if(0==strcmp(childElement->Name(),"ParticleColorAffector"))
        {
            particleAffector = new 	ParticleColorAffector(this);
        }
        else if(0==strcmp(childElement->Name(),"ParticleRotationAffector"))
        {
            particleAffector = new 	ParticleRotationAffector(this);
        }
        else if(0==strcmp(childElement->Name(),"ParticleScaleAffector"))
        {
            particleAffector = new 	ParticleScaleAffector(this);
        }
        if(particleAffector)
        {
            particleAffector->load(childElement);
            addAffector(particleAffector);
        }
        childElement= childElement->NextSiblingElement();
    } 
    setTotalParticles(_parSystemConfig.totalParticles);
    setTexture(_parSystemConfig.textureName);
    return true;
}
bool ParticleSystem3D::save(tinyxml2::XMLDocument* xmlDoc)
{
    tinyxml2::XMLElement *pElement = xmlDoc->NewElement("particleSystem");
    pElement->SetAttribute("totalParticles",_parSystemConfig.totalParticles);
    pElement->SetAttribute("textureName",_parSystemConfig.textureName);
    pElement->SetAttribute("blendType",_parSystemConfig.blendType);
    xmlDoc->LinkEndChild(pElement);
    if(_particleEmitter)
    {
        _particleEmitter->save(pElement,xmlDoc);
    }
     if(_particleRender)
    {
        _particleRender->save(pElement,xmlDoc);
    }
    for (size_t i = 0; i < _parAffectors.size(); i++)
    {
        _parAffectors[i]->save(pElement,xmlDoc);
    }
    return true;
}
int  ParticleSystem3D::getTotalParticle()const
{
    return _parSystemConfig.totalParticles;
}
void ParticleSystem3D::setParticleEmitter(ParticleEmitter* parEmitter)
{
    CC_SAFE_DELETE(_particleEmitter);
    if(parEmitter)
    {
        _particleEmitter =parEmitter;
    }
}
void ParticleSystem3D::setParticleRender(ParticleRender* parRender)
{
    CC_SAFE_DELETE(parRender);
    if(parRender)
    {
        _particleRender = parRender;
    }
}
void   ParticleSystem3D::emitterParticle(float dt)
{
    if(!_started)
    {
        return;
    }

    if (_timeRunning >= _particleEmitter->getEmitDelay())    
    {     
        if (_particleEmitter->getEmitRate())        
        {           

            float rate = 1.0f /_particleEmitter->getEmitRate();    
            if (_particleCount < _parSystemConfig.totalParticles)          
            {              
                _emitCounter += dt;        
            }           
            while (_particleCount <_parSystemConfig.totalParticles && _emitCounter > rate)        
            {               
                this->addParticle();             
                _emitCounter -= rate;         
            }      

        }    
    }
    _timeRunning+=dt;
    if (_particleEmitter->getEmitDuration() != -1 &&_particleEmitter->getEmitDuration() < _timeRunning)     
    {            stop();       
    }
}
Particle3D* ParticleSystem3D::getParticle(int index)const
{
    if(_particles)
    {
       return &_particles[index];
    }
    return NULL;
}

NS_CC_END
