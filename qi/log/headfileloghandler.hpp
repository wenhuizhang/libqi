/**
 * headfileloghandler.h
 * Author(s):
 *  - Herve Cuche <hcuche@aldebaran-robotics.com>
 */

#ifndef HEADFILELOGHANDLER_HPP_
# define HEADFILELOGHANDLER_HPP_

# include <qi/log.hpp>
# include <qi/noncopyable.hpp>
# include <string>

namespace qi {
  namespace log {
    class PrivateHeadFileLogHandler;

    class QI_API HeadFileLogHandler : qi::noncopyable
    {
    public:
      HeadFileLogHandler(const std::string &filePath,
                         int length = 2000);
      virtual ~HeadFileLogHandler();

      void log(const qi::log::LogLevel verb,
               const qi::os::timeval   date,
               const char              *category,
               const char              *msg,
               const char              *file,
               const char              *fct,
               const int               line);

    private:
      HeadFileLogHandler() {};

      PrivateHeadFileLogHandler* _private;
    }; // !HeadFileLogHandler
  }; // !log
}; // !qi

#endif // !HEADFILELOGHANDLER_HPP_
