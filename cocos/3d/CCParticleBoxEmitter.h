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
#ifndef __CCPARTICLEBOXLEMITTER_H__
#define __CCPARTICLEBOXLEMITTER_H__
#include "2d/CCNode.h"
#include "3d/CCParticleEmitter.h"
NS_CC_BEGIN
struct    BoxEmitterConfig
{
    Vec3 boxSize;
};
class ParticleBoxEmitter : public ParticleEmitter 
{
public:	
    ParticleBoxEmitter(ParticleSystem3D* system);
    virtual ~ParticleBoxEmitter();
    //Initializes a particle   pos
    virtual void   initParticlePos(Particle3D* particle);
    virtual bool   load(tinyxml2::XMLElement* element);
    bool    ParticleBoxEmitter::save(tinyxml2::XMLElement* element,tinyxml2::XMLDocument* xmlDoc);
private:
    BoxEmitterConfig  _boxeEmitterConfig;
};
NS_CC_END
#endif 
