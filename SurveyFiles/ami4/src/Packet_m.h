//
// Generated file, do not edit! Created by opp_msgc 4.3 from Packet.msg.
//

#ifndef _PACKET_M_H_
#define _PACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0403
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "IPv4Address.h"
// }}



/**
 * Class generated from <tt>Packet.msg</tt> by opp_msgc.
 * <pre>
 * packet Packet
 * {
 *     int sourceID;
 *     IPv4Address srcAddr;
 *     IPv4Address destAddr;
 *     
 *     int packetSize;
 *     bool specialField;
 *     int outGateIndex;
 * }
 * </pre>
 */
class Packet : public ::cPacket
{
  protected:
    int sourceID_var;
    IPv4Address srcAddr_var;
    IPv4Address destAddr_var;
    int packetSize_var;
    bool specialField_var;
    int outGateIndex_var;

  private:
    void copy(const Packet& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Packet&);

  public:
    Packet(const char *name=NULL, int kind=0);
    Packet(const Packet& other);
    virtual ~Packet();
    Packet& operator=(const Packet& other);
    virtual Packet *dup() const {return new Packet(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getSourceID() const;
    virtual void setSourceID(int sourceID);
    virtual IPv4Address& getSrcAddr();
    virtual const IPv4Address& getSrcAddr() const {return const_cast<Packet*>(this)->getSrcAddr();}
    virtual void setSrcAddr(const IPv4Address& srcAddr);
    virtual IPv4Address& getDestAddr();
    virtual const IPv4Address& getDestAddr() const {return const_cast<Packet*>(this)->getDestAddr();}
    virtual void setDestAddr(const IPv4Address& destAddr);
    virtual int getPacketSize() const;
    virtual void setPacketSize(int packetSize);
    virtual bool getSpecialField() const;
    virtual void setSpecialField(bool specialField);
    virtual int getOutGateIndex() const;
    virtual void setOutGateIndex(int outGateIndex);
};

inline void doPacking(cCommBuffer *b, Packet& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Packet& obj) {obj.parsimUnpack(b);}


#endif // _PACKET_M_H_
