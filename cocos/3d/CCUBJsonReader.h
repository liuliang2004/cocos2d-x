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

#ifndef __CC_UBJSONREADER_H_
#define __CC_UBJSONREADER_H_
#include "base/ccMacros.h"
#include "math/CCMath.h"
#include "json/document.h"
NS_CC_BEGIN

class UBJsonReader 
{
public:
    UBJsonReader();
    virtual ~UBJsonReader();
    void parse(unsigned char* lpbuffer, ssize_t length, rapidjson::Document* doc);
protected:
     rapidjson::Value* parse (unsigned char type);
     /**
     * Reads an array of elements.
     *
     * @param ptr   The pointer to the memory to copy into.
     *              The available size should be at least bytes.
     * @param size  The size of each element to be read, in bytes.
     * @param count The number of elements to read.
     *
     * @return The number of elements read.
     */
     ssize_t read(void* ptr, ssize_t size, ssize_t count);
     rapidjson::Value* parseArray();
     rapidjson::Value* parseObject();
     rapidjson::Value* parseData(unsigned char blockType);
    const char* parseString(bool sOptional,unsigned char type);
    long  parseSize(unsigned char type,bool useIntOnError,long defaultValue);
    short readUChar();
    unsigned short readUShort();
    unsigned int   readUInt();
    unsigned char  readByte();
    char*          readString(long size);
    /**
    * Returns true if the end of the buffer has been reached.
    */
    bool eof();

    /**
    * Returns the length of the buffer in bytes.
    */
    ssize_t length();

    /**
    * Returns the position of the file pointer.
    */
    long int tell();

private:
    ssize_t  _position;
    ssize_t  _length;
    ssize_t  _validLength;
    unsigned char*    _buffer;
    bool     _oldFormat;
    rapidjson::Document* _document;
    rapidjson::Value::AllocatorType*  _alloctor;
    bool      _isRoot;
};

NS_CC_END
#endif
