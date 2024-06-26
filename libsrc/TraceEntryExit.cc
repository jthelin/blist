#include "TraceEntryExit.h"

#include <iostream>

/*  Initialise static data members of class TraceEntryExit */
bool TraceEntryExit::logEntryExits = false;

/** Log function entry message. */
#define TRACE_ENTER(class_name, function_name, args)                                                                   \
  {                                                                                                                    \
    std::clog << EntryPrefix.data() << (class_name) << "::" << (function_name);                                        \
    if (!(args).empty()) {                                                                                             \
      std::clog << " - " << (args);                                                                                    \
    }                                                                                                                  \
    std::clog << "\n"; /* Stream flush not required, so don't use std::endl */                                         \
  }

/** Log function exit message. */
#define TRACE_EXIT(class_name, function_name, args)                                                                    \
  {                                                                                                                    \
    std::clog << Exit_Prefix.data() << (class_name) << "::" << (function_name);                                        \
    if (!(args).empty()) {                                                                                             \
      std::clog << " - " << (args);                                                                                    \
    }                                                                                                                  \
    std::clog << "\n"; /* Stream flush not required, so don't use std::endl */                                         \
  }

static const char* BLANK_STR = "";

TraceEntryExit::TraceEntryExit(const std::string& class_name, const std::string& function_name, const bool always_log) :
    TraceEntryExit(class_name, function_name, BLANK_STR, always_log)
{
}

TraceEntryExit::TraceEntryExit(const std::string& class_name,
                               const std::string& function_name,
                               const std::string& arguments,
                               const bool         always_log) :
    className(class_name), functionName(function_name), args(arguments), alwaysLog(always_log)
{
  if (alwaysLog || logEntryExits) {
    TRACE_ENTER(this->className, this->functionName, this->args)
  }
}

TraceEntryExit::~TraceEntryExit()
{
  if (alwaysLog || logEntryExits) {
    try {
      TRACE_EXIT(this->className, this->functionName, this->args)
    }
    catch (...) {
      std::cerr << "ERROR during TRACE_EXIT" << std::endl;
    }
  }
}

bool TraceEntryExit::SetLogging(const bool new_trace_level)
{
  const bool old_logEntryExits = logEntryExits;
  logEntryExits                = new_trace_level;
  return old_logEntryExits;
}

TraceLevelOverride TraceLevelOverride::SetLogging(const bool new_trace_level)
{
  const bool old_trace_level = TraceEntryExit::SetLogging(new_trace_level);
  return TraceLevelOverride(old_trace_level);
}

TraceLevelOverride::TraceLevelOverride(const bool old_trace_level) : previous(old_trace_level)
{
}

TraceLevelOverride::~TraceLevelOverride()
{
  TraceEntryExit::SetLogging(this->previous);
}
