/*
** Author(s):
**  - Herve Cuche <hcuche@aldebaran-robotics.com>
**
** Copyright (C) 2012 Aldebaran Robotics
*/

#pragma once
#ifndef _QIMESSAGING_TRANSPORT_SERVER_P_HPP_
#define _QIMESSAGING_TRANSPORT_SERVER_P_HPP_

# include <qimessaging/api.hpp>
# include <qimessaging/url.hpp>
# include <qimessaging/session.hpp>
# include <qimessaging/transport_server.hpp>

# include <string>
# include <queue>
# include <vector>

#include <boost/thread.hpp>

namespace qi {

  class TransportServerPrivate
  {
  public:
    TransportServerPrivate(TransportServer* self, const qi::Url &url,
      EventLoop* ctx)
      : self(self)
      , tsi(0)
      , context(ctx)
      , listenUrl(url)
    {}

    virtual ~TransportServerPrivate()
    {
    }

    virtual bool listen() = 0;
    virtual void close() = 0;
    virtual void destroy() = 0;

  public:
    TransportServer                        *self;
    std::vector<TransportServerInterface *> tsi;
    boost::mutex                            mutexCallback;
    qi::EventLoop                          *context;
    qi::Url                                 listenUrl;
    std::vector<qi::Url>                    _endpoints;

  protected:
    TransportServerPrivate()
      : tsi(0)
      , context(0)
      , listenUrl("")
    {};
  };

}

#endif  // _QIMESSAGING_TRANSPORT_SERVER_P_HPP_
