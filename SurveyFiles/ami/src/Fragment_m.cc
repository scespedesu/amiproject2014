//
// Generated file, do not edit! Created by opp_msgc 4.3 from Fragment.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Fragment_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(Fragment);

Fragment::Fragment(const char *name, int kind) : cPacket(name,kind)
{
    this->originalPacketSize_var = 0;
    this->moreFragments_var = 0;
    this->gateIndex_var = 0;
    this->fragmentId_var = 0;
}

Fragment::Fragment(const Fragment& other) : cPacket(other)
{
    copy(other);
}

Fragment::~Fragment()
{
}

Fragment& Fragment::operator=(const Fragment& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Fragment::copy(const Fragment& other)
{
    this->srcAddr_var = other.srcAddr_var;
    this->destAddr_var = other.destAddr_var;
    this->originalPacketSize_var = other.originalPacketSize_var;
    this->moreFragments_var = other.moreFragments_var;
    this->gateIndex_var = other.gateIndex_var;
    this->fragmentId_var = other.fragmentId_var;
}

void Fragment::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->srcAddr_var);
    doPacking(b,this->destAddr_var);
    doPacking(b,this->originalPacketSize_var);
    doPacking(b,this->moreFragments_var);
    doPacking(b,this->gateIndex_var);
    doPacking(b,this->fragmentId_var);
}

void Fragment::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->srcAddr_var);
    doUnpacking(b,this->destAddr_var);
    doUnpacking(b,this->originalPacketSize_var);
    doUnpacking(b,this->moreFragments_var);
    doUnpacking(b,this->gateIndex_var);
    doUnpacking(b,this->fragmentId_var);
}

IPv4Address& Fragment::getSrcAddr()
{
    return srcAddr_var;
}

void Fragment::setSrcAddr(const IPv4Address& srcAddr)
{
    this->srcAddr_var = srcAddr;
}

IPv4Address& Fragment::getDestAddr()
{
    return destAddr_var;
}

void Fragment::setDestAddr(const IPv4Address& destAddr)
{
    this->destAddr_var = destAddr;
}

int Fragment::getOriginalPacketSize() const
{
    return originalPacketSize_var;
}

void Fragment::setOriginalPacketSize(int originalPacketSize)
{
    this->originalPacketSize_var = originalPacketSize;
}

int Fragment::getMoreFragments() const
{
    return moreFragments_var;
}

void Fragment::setMoreFragments(int moreFragments)
{
    this->moreFragments_var = moreFragments;
}

int Fragment::getGateIndex() const
{
    return gateIndex_var;
}

void Fragment::setGateIndex(int gateIndex)
{
    this->gateIndex_var = gateIndex;
}

int Fragment::getFragmentId() const
{
    return fragmentId_var;
}

void Fragment::setFragmentId(int fragmentId)
{
    this->fragmentId_var = fragmentId;
}

class FragmentDescriptor : public cClassDescriptor
{
  public:
    FragmentDescriptor();
    virtual ~FragmentDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FragmentDescriptor);

FragmentDescriptor::FragmentDescriptor() : cClassDescriptor("Fragment", "cPacket")
{
}

FragmentDescriptor::~FragmentDescriptor()
{
}

bool FragmentDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Fragment *>(obj)!=NULL;
}

const char *FragmentDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FragmentDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int FragmentDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *FragmentDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "originalPacketSize",
        "moreFragments",
        "gateIndex",
        "fragmentId",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int FragmentDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+1;
    if (fieldName[0]=='o' && strcmp(fieldName, "originalPacketSize")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "moreFragments")==0) return base+3;
    if (fieldName[0]=='g' && strcmp(fieldName, "gateIndex")==0) return base+4;
    if (fieldName[0]=='f' && strcmp(fieldName, "fragmentId")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FragmentDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPv4Address",
        "IPv4Address",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *FragmentDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FragmentDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Fragment *pp = (Fragment *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FragmentDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Fragment *pp = (Fragment *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrcAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDestAddr(); return out.str();}
        case 2: return long2string(pp->getOriginalPacketSize());
        case 3: return long2string(pp->getMoreFragments());
        case 4: return long2string(pp->getGateIndex());
        case 5: return long2string(pp->getFragmentId());
        default: return "";
    }
}

bool FragmentDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Fragment *pp = (Fragment *)object; (void)pp;
    switch (field) {
        case 2: pp->setOriginalPacketSize(string2long(value)); return true;
        case 3: pp->setMoreFragments(string2long(value)); return true;
        case 4: pp->setGateIndex(string2long(value)); return true;
        case 5: pp->setFragmentId(string2long(value)); return true;
        default: return false;
    }
}

const char *FragmentDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "IPv4Address",
        "IPv4Address",
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<6) ? fieldStructNames[field] : NULL;
}

void *FragmentDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Fragment *pp = (Fragment *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSrcAddr()); break;
        case 1: return (void *)(&pp->getDestAddr()); break;
        default: return NULL;
    }
}


