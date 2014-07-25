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
#ifndef _CCCAMERA3D_H__
#define _CCCAMERA3D_H__
#include "2d/CCNode.h"
NS_CC_BEGIN
/**
 * Defines a camera .
 */
class Camera3D :public Node
{
public:
    /**
     * The type of camera.
     */
    enum class Type
    {
        PERSPECTIVE = 1,
        ORTHOGRAPHIC = 2
    };
    /**
     * Creates a perspective camera.
     *
     * @param fieldOfView The field of view for the perspective camera (normally in the range of 40-60 degrees).
     * @param aspectRatio The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).
     * @param nearPlane The near plane distance.
     * @param farPlane The far plane distance.
     */
    static Camera3D*    createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    /**
     * Creates an orthographic camera.
     *
     * @param zoomX The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).
     * @param zoomY The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).
     * @param aspectRatio The aspect ratio of the orthographic projection.
     * @param nearPlane The near plane distance.
     * @param farPlane The far plane distance.
     */
    static Camera3D*  createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
	static Camera3D*  getActiveCamera();
    /**
     * Gets the type of camera.
     *
     * @return The camera type.
     */
    Camera3D::Type  getCameraType() const;

	/**
	 *
	 *
	 */
	void lookAt(const Vec3& position, const Vec3& up, const Vec3& target);
	/**
     * Gets the camera's projection matrix.
     *
     * @return The camera projection matrix.
     */
    Mat4& getProjectionMatrix();
	/**
     * Gets the camera's view matrix.
     *
     * @return The camera view matrix.
     */
    Mat4& getViewMatrix();
    
    /**get view projection matrix*/
    const Mat4& getViewProjectionMatrix();
    
    /**set additional matrix for the projection matrix, it multiplys mat to projection matrix when called, used by WP8*/
    void setAdditionalProjection(const Mat4& mat);
    
    /**
     *  set the camera's projection View.
     */
    void applyProjection();
    /**
     * Sets the position (X, Y, and Z) in its parent's coordinate system
     */
	virtual void setPosition3D(const Vec3& position);
	 //set active camera 
    static void setActiveCamera(Camera3D* camera);
    
    
CC_CONSTRUCTOR_ACCESS:
    Camera3D();
    ~Camera3D();
    
protected:
    
    Mat4 _projection;
    Mat4 _view;
    Mat4 _viewProjection;
    
    
    Camera3D::Type _type;
    float _fieldOfView;
    float _zoom[2];
    float _aspectRatio;
    float _nearPlane;
    float _farPlane;
    static Camera3D* _activeCamera;
};
NS_CC_END
#endif// __CCCAMERA3D_H_