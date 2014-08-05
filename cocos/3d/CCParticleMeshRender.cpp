
#include "3d/CCParticleMeshRender.h"
#include "3d/CCParticleSystem3D.h" 
#include "3d/CCSprite3D.h"
NS_CC_BEGIN
ParticleMeshRender::ParticleMeshRender(ParticleSystem3D* system):
ParticleRender(system)
{
	
}
ParticleMeshRender::~ParticleMeshRender()
{
     for( std::vector<Sprite3D*>::iterator iter=_particleMeshVec.begin(); iter!=_particleMeshVec.end(); ++iter )
    {
        (*iter)->release();
    }
	_particleMeshVec.clear();
}
void ParticleMeshRender::update(float dt)
{
}
bool ParticleMeshRender::load(tinyxml2::XMLElement* element)
{
    return true;
}
bool ParticleMeshRender::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc)
{
    return true;
}
void ParticleMeshRender::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags,int particleIdx)
{
    if(_parSystem)
    {
        for(int i = 0; i < particleIdx; i++)
        {
            _particleMeshVec[i]->visit(renderer, transform,flags);
        } 
    }
}
void ParticleMeshRender::reSizeCapacity(unsigned int nCapacity)
{
    for( std::vector<Sprite3D*>::iterator iter=_particleMeshVec.begin(); iter!=_particleMeshVec.end(); ++iter )
    {
        (*iter)->release();
    }
    _particleMeshVec.clear();
    for(int i = 0; i < nCapacity ; i++ )
    {
        auto _particleMesh = Sprite3D::create("CameraTest/orc.c3b");
        if(_particleMesh)
        {
            _particleMesh->retain();
            _particleMeshVec.push_back(_particleMesh);
        }
    }
}
void ParticleMeshRender::updateParticle(Particle3D* p, int   particleIdx,float dt,const Vec3& newPosition)
{
     _particleMeshVec[particleIdx]->setPositionZ(p->position.z);
     _particleMeshVec[particleIdx]->setPosition3D(p->position);
     _particleMeshVec[particleIdx]->setColor(Color3B(p->color.r*255,p->color.g*255,p->color.b*255));
     _particleMeshVec[particleIdx]->setScale(p->scale);
     _particleMeshVec[particleIdx]->setOpacity(p->color.a*255);
     _particleMeshVec[particleIdx]->setRotation3D(Vec3(0,p->rotation,0));
}
NS_CC_END