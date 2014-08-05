/****************************************************************************
Copyright (c) Chukong Technologies Inc.

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
#include "CCUBJsonReader.h"
NS_CC_BEGIN

#define SWAP(X,Y,T) {T=X; X=Y; Y=T;}
    template<size_t n> void swap(char * const &data) {assert(("This shouldnt happen", false));}
template<> inline void swap<1>(char * const &data) {}
template<> inline void swap<2>(char * const &data) 
{
    static char tmp;
    SWAP(data[0], data[1], tmp);
}
template<> inline void swap<4>(char * const &data) {
    static char tmp;
    SWAP(data[0], data[3], tmp);
    SWAP(data[1], data[2], tmp);
}
template<> inline void swap<8>(char * const &data) {
    static char tmp;
    SWAP(data[0], data[7], tmp);
    SWAP(data[1], data[6], tmp);
    SWAP(data[2], data[5], tmp);
    SWAP(data[3], data[4], tmp);
}

UBJsonReader::UBJsonReader()
{
    _oldFormat=true;
    _alloctor = nullptr; //new rapidjson::Value::AllocatorType();
    _document=nullptr;
}
UBJsonReader::~UBJsonReader()
{
    _alloctor=NULL;
}

void UBJsonReader::parse(unsigned char* lpbuffer, ssize_t length, rapidjson::Document* doc)
{
    _position = 0;
    _buffer  = lpbuffer;
    _length = length;
    _isRoot = false;
    _document = doc;
    _alloctor = &(_document->GetAllocator());
    unsigned char type;
    read(&type,sizeof(unsigned char),1);
    parse(type);
}
rapidjson::Value* UBJsonReader::parse(unsigned char type)
{
    if (type == 'd')
    {
        float value;
        read(&value,sizeof(float),1);
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        swap<sizeof(float)>((char*)&value);
        //#endif
        return  new rapidjson::Value(value);
    }
    else if (type == 'D')
    {
        double value;
        read(&value,sizeof(double),1);
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        swap<sizeof(double)>((char*)&value);
        //#endif
        return  new rapidjson::Value(value);
    }
    else if (type == '[')
        return parseArray();
    else if (type == '{')
        return parseObject();
    else if (type == 'Z')
        return  new rapidjson::Value(rapidjson::kNullType);
    else if (type == 'T')
        return  new rapidjson::Value(true);
    else if (type == 'F')
        return  new rapidjson::Value(false);
    else if (type == 'B')
        return  new rapidjson::Value(readByte());
    else if (type == 'U')
        return  new rapidjson::Value(readUChar());
    else if (type == 'i')
    {
        if(_oldFormat)
        {

            short value; 
            read(&value,sizeof(short),1);
            //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            swap<sizeof(short)>((char*)&value);
            //#endif
            //return  new rapidjson::Value(value);
            return  new rapidjson::Value(value);;
        }
        else
        {
            unsigned char value;
            read(&value,sizeof(unsigned char),1);
            return  new rapidjson::Value(value);
        }
    }
    else if (type == 'I')
    {
        if(_oldFormat)
        {
            int value; 
            read(&value,sizeof(int),1);
            //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            swap<sizeof(int)>((char*)&value);
            //#endif
            return  new rapidjson::Value(value);
        }
        else
        {
            short value; 
            read(&value,sizeof(short),1);
            //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            swap<sizeof(int)>((char*)&value);
            //#endif
            return  new rapidjson::Value(value);
        }
    }  
    else if (type == 'l')
    {
        int value; 
        read(&value,sizeof(int),1);
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        swap<sizeof(int)>((char*)&value);
        //#endif
        return  new rapidjson::Value(value);
    }
    else if (type == 'L')
    {
        long value; 
        read(&value,sizeof(long),1);
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        swap<sizeof(long)>((char*)&value);
        //#endif
        return new rapidjson::Value((long long)value);
    }
    else if (type == 's' || type == 'S')
    {
        return new rapidjson::Value(parseString(false,type));
    }
    else if (type == 'a' || type == 'A')
    {
        return parseData( type);
    }
    return nullptr;
}
ssize_t UBJsonReader::read(void* ptr, ssize_t size, ssize_t count)
{
    if (!_buffer || eof())
        return 0;

    ssize_t validCount;
    _validLength = _length - _position;
    ssize_t needLength = size*count;
    char* ptr1 = (char*)ptr;
    if(_validLength <= needLength)
    {
        validCount = _validLength/size;
        ssize_t readLength = size*validCount;
        memcpy(ptr1,(char*)_buffer+_position,readLength);
        ptr1 += readLength;
        _position += readLength;
        readLength = _validLength - readLength;
        if(readLength>0)
        {
            memcpy(ptr1,(char*)_buffer+_position,readLength);
            _position += readLength;
            validCount+=1;
        }
    }
    else
    {
        memcpy(ptr1,(char*)_buffer+_position,needLength);
        _position += needLength;
        validCount = count;
    }
    return validCount;
}
bool UBJsonReader::eof()
{
    if (!_buffer)
        return true;

    return ((ssize_t)tell()) >= length();
}
ssize_t UBJsonReader::length()
{
    return _length;
}
ssize_t UBJsonReader::tell()
{
    if (!_buffer)
        return -1;
    return _position;
}
rapidjson::Value* UBJsonReader::parseArray()
{
    rapidjson::Value* result = new rapidjson::Value(rapidjson::kArrayType);
    unsigned char type=readByte();
    unsigned char valueType = 0;
    if (type == '$') 
    {	
        valueType=readByte();
        type=readByte();
    }
    long size = -1;
    if (type == '#') 
    {
        size = parseSize(readByte(), false, -1);
        if (size == 0) return result;
        type = valueType == 0 ? readByte() : valueType;
    }
    long c = 0;
    while (_validLength > 0 && type != ']') 
    {
        rapidjson::Value* val = parse(type); 
        result->PushBack(*val, *_alloctor);
        delete val;
        if (size > 0 && ++c >= size) break;
        type = valueType == 0 ? readByte() : valueType;
    }
    return result;
}
rapidjson::Value* UBJsonReader::parseObject()
{
    rapidjson::Value* result = nullptr;
    if(!_isRoot)
    {
        result = _document;
        _isRoot = true;
    }
    else
    {
        //rapidjson::Value object(rapidjson::kObjectType);
        result=new rapidjson::Value(rapidjson::kObjectType);
    }
    unsigned char type = readByte();
    unsigned char valueType = 0;
    if (type == '$') 
    {	
        valueType=readByte();
        type=readByte();
    }
    long size = -1;
    if (type == '#') 
    {
        size = parseSize(readByte(), false, -1);
        if (size == 0) return result;
        type = readByte();
    }
    long c = 0;
    while (_validLength > 0 && type != '}') 
    {
        const char* key = parseString(true, type);
        rapidjson::Value* child = parse(valueType == 0 ? readByte() : valueType);
        result->AddMember(key,*child, *_alloctor);
        //delete[] key;
        delete child;
        if (size > 0 && ++c >= size) break;
        type =readByte();
    }
    return result;
}
rapidjson::Value* UBJsonReader::parseData(unsigned char blockType)
{
    unsigned char dataType = readByte();
    long size = blockType == 'A' ? readUInt() : (long)readUChar();
    rapidjson::Value* result =new rapidjson::Value(rapidjson::kArrayType);
    for (long i = 0; i < size; i++)
    {
        {
            rapidjson::Value* val = parse(dataType);
            result->PushBack(*val, *_alloctor);
            delete val;
        }  
    }
    return result;
}
long UBJsonReader::parseSize(unsigned char type,bool useIntOnError,long defaultValue)
{
    if (type == 'i')
    {
        return (long)readUChar();
    }
    if (type == 'I') 
    {
        return (long)readUShort();
    }
    if (type == 'l') 
    {
        return (long)readUInt();
    }
    if (type == 'L') 
    {
        long value;
        read(&value,sizeof(long),1);
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        swap<sizeof(long)>((char*)&value);
        //#endif
        return value;
    }
    if (useIntOnError) 
    {

        long result = (long)((short)type & 0xFF) << 24;
        result |= (long)((short)readByte() & 0xFF) << 16;
        result |= (long)((short)readByte() & 0xFF) << 8;
        result |= (long)((short)readByte() & 0xFF);
        return result;
    }
    return defaultValue;
}
short UBJsonReader::readUChar()
{
    unsigned char data;
    read(&data,sizeof(unsigned char),1);
    return (short)((short)data & 0xFF);
}
unsigned short UBJsonReader::readUShort()
{
    unsigned short data; 
    read(&data,sizeof(unsigned short),1);
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    swap<sizeof(unsigned short)>((char*)&data);
    //#endif
    return data;
}

unsigned int  UBJsonReader::readUInt()
{
    unsigned int data;
    read(&data,sizeof(unsigned int),1);
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    swap<sizeof(unsigned int)>((char*)&data);
    //#endif
    return data;
}

unsigned char UBJsonReader::readByte()
{
    unsigned char data;
    read(&data,sizeof(unsigned char),1);
    return data;
}
const char* UBJsonReader::parseString(bool sOptional,unsigned char type)
{
    long size = -1;
    if (type == 'S') 
        size = (long)readUInt();
    else if (type == 's')
        size = (long)readUChar();
    else if (sOptional)
        size = parseSize(type, false, -1);

    return size > 0 ? readString(size) : "";
}
char*  UBJsonReader::readString(long size)
{
    char* data=new char[size+1];
    read(data,size,1);
    data[size]='\0';
    return data;
}

NS_CC_END