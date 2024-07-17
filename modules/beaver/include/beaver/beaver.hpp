#pragma once
// #include <...> (HPPMERGE)
#include <ranges>
#include <memory>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <map>
#include <set>
#include <unordered_map>
#include <functional>
#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <source_location>


// #include "common.hpp" (HPPMERGE)
namespace Beaver {
    // ranges
    namespace stdr = std::ranges;

    // types
    // types :: address
    using address = std::size_t;
    // types :: int
    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;
    // types :: uint
    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;
    // types :: string
    using string = std::string;
    using string_view = std::string_view;

    // container
    // container :: sequential
    template<typename T, address N>
    using Array = std::array<T, N>;
    template<typename T>
    using List = std::vector<T>;
    template<typename T>
    using Stack = std::stack<T>;
    template<typename T>
    using Queue = std::queue<T>;
    template<typename T>
    using Deque = std::deque<T>;
    // container :: tree
    template<typename T>
    using Set = std::set<T>;
    template<typename Key, typename Value>
    using Map = std::map<Key, Value>;
    // container :: hash
    template<typename T>
    using HashSet = std::unordered_set<T>;
    template<typename Key, typename Value>
    using HashMap = std::unordered_map<Key, Value>;

    // move semantics
    using std::forward;
    using std::move;

    // smart pointers
    using std::make_unique;
    using std::make_shared;
    using std::unique_ptr;
    using std::shared_ptr;
    using std::weak_ptr;

    // function
    using std::function;

    // templates
    template<typename T>
    using Opt = std::optional<T>;

    // debug
    using std::cout;
    using std::endl;
}

// #include "common_stream.hpp" (HPPMERGE)
namespace Beaver {
    // stdout
    using std::cout;
    using std::cerr;
    using std::endl;
    // io
    using std::istream;
    using std::ostream;
    // file io
    using std::fstream;
    using std::ifstream;
    using std::ofstream;
    // stringstream
    using std::stringstream;
}

// #include "meta.hpp" (HPPMERGE)
namespace Beaver {
    // Level
	enum class Level {
		Trace = 1, Debug, Info, Warn, Error, Fatal
	};
    // Location
    struct Location {
        // constructor
        Location(const std::source_location& location);
        // operator<<
        friend ostream& operator<<(ostream& stream, const Location& location);
        // member
        string file;
        uint line;
        uint column;
    };
    // Timestamp
    struct Timestamp {
        // constructor
        Timestamp();
        // operator<<
        friend ostream& operator<<(ostream& stream, const Timestamp& timestamp);
        // member
        uint hours, minutes, seconds;
    };
    // MsgMeta
    struct MsgMeta {
        // constructor
        MsgMeta(Level level, const Location& location);
        // operator<<
        friend ostream& operator<<(ostream& stream, const MsgMeta& meta);
        // member
        Level level;
        Location location;
        Timestamp timestamp;
    };
    #define LOCATION ::Beaver::Location(std::source_location::current())
}

// #include "format.hpp" (HPPMERGE)
namespace Beaver {
    // Format
    class Format {
    public:
        // constructor
        Format(string_view view);
        // operator<<
        template<typename T>
        Format& operator<<(const T& param) {
            address index = m_View.find("{}");
            if (index < string::npos) {
                m_Stream << m_View.substr(0, index) << param;
                m_View = m_View.substr(index + 2);
            }
            return *this;
        }
        // close
        string close();
    private:
        // member
        string_view m_View;
        stringstream m_Stream;
    };
}

// #include "logger.hpp" (HPPMERGE)
namespace Beaver {
    // Logger
    class Logger {
    public:
        // constructor / destructor
        Logger(const string& name);
        Logger(const string& name, const string& logfile);
        ~Logger();
        // log
        template<typename... TArgs>
        void log(const MsgMeta& meta, string_view fmt, const TArgs&... args) {
            if (int(m_Level) <= int(meta.level)) {
                stream(meta, (Format(fmt) << ... << args).close());
            }
        }
        // level
        Level getLevel() const;
        void setLevel(Level level);
    private:
        // stream
        void stream(const MsgMeta& meta, const string& msg);
        // member
        string m_Name;
        Opt<string> m_LogFile;
        Level m_Level;
        // static
        static inline std::mutex s_StreamMutex;
        static inline Map<string, fstream> s_Filestreams;
        static inline Map<string, int> s_FileRefCount;
    };
    // Macros !Make sure to define LOGGER before usage
    #define LOG_TRACE(...) LOGGER.log(::Beaver::MsgMeta(::Beaver::Level::Trace, LOCATION), __VA_ARGS__)
    #define LOG_DEBUG(...) LOGGER.log(::Beaver::MsgMeta(::Beaver::Level::Debug, LOCATION), __VA_ARGS__)
    #define LOG_INFO(...) LOGGER.log(::Beaver::MsgMeta(::Beaver::Level::Info, LOCATION), __VA_ARGS__)
    #define LOG_WARN(...) LOGGER.log(::Beaver::MsgMeta(::Beaver::Level::Warn, LOCATION), __VA_ARGS__)
    #define LOG_ERROR(...) LOGGER.log(::Beaver::MsgMeta(::Beaver::Level::Error, LOCATION), __VA_ARGS__)
    #define LOG_FATAL(...) LOGGER.log(::Beaver::MsgMeta(::Beaver::Level::Fatal, LOCATION), __VA_ARGS__)
}

// #include "default.hpp" (HPPMERGE)
namespace Beaver {
    // setDefaultLogger
    void setDefaultLogger(unique_ptr<Logger>&& logger);
    // getDefaultLogger
    Logger& getDefaultLogger();
    // Macro
    #define LOGGER ::Beaver::getDefaultLogger()
}

// #include "assert.hpp" (HPPMERGE)
namespace Beaver {
    #define ASSERT(condition) if (!(condition)) { LOG_FATAL(string("ASSERTION FAILED \"{}\""), (#condition)); exit(EXIT_FAILURE); }
    #define ASSERT_MSG(condition, format, ...) if (!(condition)) { LOG_FATAL(string("ASSERTION FAILED \"") + format + "\"", __VA_ARGS__); exit(EXIT_FAILURE); }
}