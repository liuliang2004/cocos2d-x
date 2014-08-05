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
#ifndef __CCPARTICLBILLBOARDRENDER_H__
#define __CCPARTICLBILLBOARDRENDER_H__
#include "3d/CCParticleRender.h"
#include "renderer/CCQuadCommand.h"
NS_CC_BEGIN
struct ParBillboardRenderConfig
{
    Vec2  billboardSize; 
    int   billboardType;
};
  struct  Particle3D;
class ParticleBillboardRender  : public ParticleRender
{
public:	
	ParticleBillboardRender(ParticleSystem3D* system);
    virtual ~ParticleBillboardRender();
     /**
     * create particle render.
	 * @param system particle system it belongs to
	 * @param szMaterialFile material file name .material
	 * @param capacity maximum particles it can render
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags,int particleIdx);
    virtual void update(float dt);
    virtual void updateParticle(Particle3D* p,int particleIdx,float dt,const Vec3& newPosition);
    virtual bool load(tinyxml2::XMLElement* element);
    virtual bool save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc);
    virtual void reSizeCapacity(unsigned int nCapacity);
private:
    QuadCommand               _quadCommand;  // quad command
    V3F_C4B_T2F_Quad*         _quads; 
    Vec3                      _cameraRight; // camera right dir
    Vec3                      _cameraUp;    // camera up dir
    Vec3                      _CamDir;      // camera lookat dir
    ParBillboardRenderConfig  _parBillboardRenderConfig;
};
NS_CC_END
#endif 
