#pragma once
/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_FUTURE_HXX_
#define _QITYPE_DETAILS_FUTURE_HXX_

#include <vector>
#include <utility> // pair
#include <boost/thread/recursive_mutex.hpp>
#include <boost/bind.hpp>

namespace qi {

  namespace detail {

    class FutureBasePrivate;
    class QI_API FutureBase {
    public:
      FutureBase();
      ~FutureBase();
      bool wait(int msecs = 0) const;
      bool isReady() const;
      bool hasError(int msecs = 0) const;
      const std::string &error() const;
      void reset();
      boost::recursive_mutex& mutex();
    protected:
      void reportReady();
      void reportError(const std::string &message);
      void notifyReady();

    public:
      FutureBasePrivate *_p;
    };

    //common state shared between a Promise and multiple Futures
    template <typename T>
    class FutureState : public FutureBase {
    public:
      typedef typename FutureType<T>::type ValueType;
      typedef boost::signals2::connection Connection;
      typedef typename boost::signals2::signal<void (Future<T>)>::slot_type Slot;
      FutureState()
        : _value()
      {
      }

      void setValue(qi::Future<T> future, const ValueType &value)
      {
        if (wait(-1))
          throw std::runtime_error("Future value already set.");
        // report-ready + onResult() must be atomic to avoid
        // missing callbacks/double calls in case connect() is invoked at
        // the same time
        boost::recursive_mutex::scoped_lock lock(mutex());
        _value = value;
        reportReady();
        _onResult(future);
        notifyReady();
      }

      void setError(qi::Future<T> future, const std::string &message)
      {
        reportError(message);
        _onResult(future);
        notifyReady();
      }

      Connection connect(qi::Future<T> future, const Slot& s)
      {
        bool ready;
        Connection res;
        {
          boost::recursive_mutex::scoped_lock lock(mutex());
          res = _onResult.connect(s);
          ready = isReady();
        }
        //result already ready, notify the callback
        if (ready) {
          s(future);
        }
        return res;
      }

      bool disconnect(Connection i) {
        _onResult.disconnect(i);
        return true;
      }


      const ValueType &value() const    { wait(); return _value; }
      ValueType &value()                { wait(); return _value; }

    private:
      boost::signals2::signal<void (qi::Future<T>)>  _onResult;
      ValueType                         _value;
    };
  } // namespace detail

  template <typename T>
  qi::Future<T> makeFutureError(const std::string &error) {
    qi::Promise<T> prom;
    prom.setError(error);
    return prom.future();
  }
}

#endif  // _QITYPE_DETAILS_FUTURE_HXX_
