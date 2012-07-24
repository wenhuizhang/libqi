/*
*  Author(s):
*  - Chris  Kilner <ckilner@aldebaran-robotics.com>
*  - Cedric Gestes <gestes@aldebaran-robotics.com>
*  - Laurent Lec   <llec@aldebaran-robotics.com>
*
*  Copyright (C) 2010, 2011, 2012 Aldebaran Robotics
*/


#pragma once
#ifndef _QIMESSAGING_MESSAGE_HPP_
#define _QIMESSAGING_MESSAGE_HPP_

#include <iostream>
#include <qimessaging/api.hpp>

#include <qimessaging/buffer.hpp>
#include <qimessaging/datastream.hpp>
#include <qi/types.hpp>

namespace qi {

  /** \class qi::Message
    * This class represent a network message
    */
  class MessagePrivate;
  class QIMESSAGING_API Message {
  public:


    enum Service
    {
      Service_None             = 0,
      Service_ServiceDirectory = 1
    };

    enum Path
    {
      Path_None = 0,
      Path_Main = 1
    };

    enum Function
    {
      Function_MetaObject = 0
    };

    enum ServiceDirectoryFunction
    {
      ServiceDirectoryFunction_Service           = 1,
      ServiceDirectoryFunction_Services          = 2,
      ServiceDirectoryFunction_RegisterService   = 3,
      ServiceDirectoryFunction_UnregisterService = 4,
      ServiceDirectoryFunction_ServiceReady      = 5,
    };

    enum GatewayFunction
    {
      GatewayFunction_Connect = 1,
    };

    enum Type
    {
      Type_None  = 0,
      // Method call, Client->Server
      Type_Call  = 1,
      // Method return value, Server->Client
      Type_Reply = 2,
      // Event, or method call without caring about return. Server<->Client
      Type_Event = 3,
      Type_Error = 4,
      // Ask to be notified on events, Client->Server
      Type_Register_Event = 5,
      // Cancel a Register_Event, Client->Server
      Type_Unregister_Event = 6,
    };

    ~Message();
    Message();
    Message(const Message &msg);
    Message &operator=(const Message &msg);

    void         setId(unsigned int id);
    unsigned int id() const;

    void         setType(qi::uint32_t type);
    unsigned int type() const;

    void         setService(qi::uint32_t service);
    unsigned int service() const;

    void         setPath(qi::uint32_t path);
    unsigned int path() const;

    void         setFunction(qi::uint32_t function);
    unsigned int function() const;

    void          setBuffer(const Buffer &buffer);
    const Buffer &buffer() const;

    void         buildReplyFrom(const Message &call);
    void         buildForwardFrom(const Message &msg);

    bool         isValid();

  public:
    MessagePrivate *_p;
  };

  QIMESSAGING_API std::ostream&   operator<<(std::ostream&   os, const qi::Message& msg);
}


#endif  // _QIMESSAGING_MESSAGE_HPP_
