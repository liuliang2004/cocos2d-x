#include "3d/CCParticleBillboardRender.h"
#include "3d/CCParticleSystem3D.h"
#include "renderer/CCRenderer.h"
#include "3d/CCCamera3D.h"
#include "base/ccMacros.h"
#include "tinyxml2.h"
NS_CC_BEGIN

ParticleBillboardRender::ParticleBillboardRender(ParticleSystem3D* system)
: ParticleRender(system),
_quads(nullptr)
,_cameraUp(0,1,0)
,_cameraRight(1,0,0)
,_CamDir(0,0,1)
{
}
ParticleBillboardRender::~ParticleBillboardRender()
{
      CC_SAFE_FREE(_quads);
}
void ParticleBillboardRender::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags,int particleIdx)
{
    if(_parSystem &&_parSystem->getTexture())
    {
        Mat4 mv;
        _quadCommand.init(_parSystem->getGlobalZOrder(), _parSystem->getTexture()->getName(), _parSystem->getGLProgramState(), _parSystem->getBlendFunc(), _quads, particleIdx, transform);
         renderer->addCommand(&_quadCommand);
    }
}
void ParticleBillboardRender::update(float dt)
{
       if(_parBillboardRenderConfig.billboardType 	==BILLBOARD)
        {
            Mat4& cameraViewMatrix = Camera3D::getActiveCamera()->getViewMatrix().getInversed();
            cameraViewMatrix.getRightVector(&_cameraRight);
            cameraViewMatrix.getUpVector(&_cameraUp);
        }
        else if(_parBillboardRenderConfig.billboardType 	==BILLBOARD_SELF)
        {
            _CamDir=Camera3D::getActiveCamera()->getLookPos()-Camera3D::getActiveCamera()->getPosition3D();
        }
}
bool ParticleBillboardRender::load(tinyxml2::XMLElement* element)
{
    const tinyxml2:: XMLAttribute*	curAttribute=element->FirstAttribute();
    while (curAttribute) 
    {
        if(0==strcmp(curAttribute->Name(),"billboardSizeX"))
        {
            curAttribute->QueryFloatValue(&_parBillboardRenderConfig.billboardSize.x);
        }
        else if(0==strcmp(curAttribute->Name(),"billboardSizeY"))
        {
            curAttribute->QueryFloatValue(&_parBillboardRenderConfig.billboardSize.y);
        }
        else if(0==strcmp(curAttribute->Name(),"billboardType"))
        {
            curAttribute->QueryIntValue(&_parBillboardRenderConfig.billboardType);
        }
        curAttribute = curAttribute->Next();  
    }
    return true;
}
bool ParticleBillboardRender::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc)
{
    tinyxml2::XMLElement *pElement = xmlDoc->NewElement("ParticleBillboardRender");
    if(pElement)
    {
        pElement->SetAttribute("billboardSizeX",_parBillboardRenderConfig.billboardSize.x);
        pElement->SetAttribute("billboardSizeY",_parBillboardRenderConfig.billboardSize.y);
        pElement->SetAttribute("billboardType",_parBillboardRenderConfig.billboardType);
        element->LinkEndChild(pElement);
    }
    return true;
}
void ParticleBillboardRender::reSizeCapacity(unsigned int nCapacity)
{
     CC_SAFE_FREE(_quads);
     _quads = (V3F_C4B_T2F_Quad*)malloc(nCapacity * sizeof(V3F_C4B_T2F_Quad));
}
void ParticleBillboardRender::updateParticle(Particle3D* p,int   particleIdx,float dt,const Vec3& newPosition)
{
    if(p)
    {
        V3F_C4B_T2F_Quad *quad=&(_quads[particleIdx]);
        Color4B color = Color4B(p->color.r*255,p->color.g*255,p->color.b*255,p->color.a*255);
        float fLeft   = -0.5f;
        float fRight  = 0.5f;
        float fTop    = 0.5f;
        float fBottom = -0.5f;
        Vec3  billboardX,billboardY;
        if(_parBillboardRenderConfig.billboardType ==BILLBOARD_SELF)
        {
            billboardY =p->velocity;
            billboardY.normalize();
            Vec3::cross(-_CamDir,billboardY,&billboardX);
            billboardX.normalize();
        }
        else if(_parBillboardRenderConfig.billboardType ==XY)
        {
            billboardX=_cameraRight;
            billboardY=_cameraUp;
        }
        else
        {
            billboardX=_cameraRight.getNormalized();
            billboardY=_cameraUp.getNormalized();
        }
        Vec3  leftOff   = billboardX * _parBillboardRenderConfig.billboardSize.x*p->scale * fLeft;
        Vec3  rightOff  = billboardX * _parBillboardRenderConfig.billboardSize.x*p->scale * fRight;
        Vec3  topOff    = billboardY * _parBillboardRenderConfig.billboardSize.y*p->scale * fTop;
        Vec3  bottomOff = billboardY * _parBillboardRenderConfig.billboardSize.y*p->scale * fBottom;
        Vec3 vOffset[4];
        vOffset[0] = leftOff + bottomOff;
        vOffset[1] = rightOff + bottomOff;
        vOffset[2] = leftOff + topOff;
        vOffset[3] = rightOff + topOff;
        if (p->rotation!=0.0f) 
        {
            Vec3 axis=vOffset[3] - vOffset[0];
            axis.cross((vOffset[2] - vOffset[1]));
            Mat4 rotMat;
            Mat4::createRotation(axis, CC_DEGREES_TO_RADIANS(p->rotation), &rotMat);
            rotMat.transformVector(&vOffset[0]);
            rotMat.transformVector(&vOffset[1]);
            rotMat.transformVector(&vOffset[2]);
            rotMat.transformVector(&vOffset[3]);
        }
        quad->bl.colors = color;
        quad->br.colors = color;
        quad->tl.colors = color;
        quad->tr.colors = color;
        quad->bl.vertices =newPosition+vOffset[0];
        quad->br.vertices =newPosition+vOffset[1];
        quad->tl.vertices =newPosition+vOffset[2];
        quad->tr.vertices =newPosition+vOffset[3];
        quad->bl.texCoords.u = p->uvRect.x;
        quad->bl.texCoords.v = p->uvRect.w;
        // bottom-right vertex:
        quad->br.texCoords.u = p->uvRect.z;
        quad->br.texCoords.v = p->uvRect.w;
        // top-left vertex:
        quad->tl.texCoords.u = p->uvRect.x;
        quad->tl.texCoords.v = p->uvRect.y;
        // top-right vertex:
        quad->tr.texCoords.u = p->uvRect.z;
        quad->tr.texCoords.v = p->uvRect.y;
    }
}

NS_CC_END