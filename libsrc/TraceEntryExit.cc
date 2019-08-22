#include <iostream>
#include <memory>

#include "TraceEntryExit.h"

/*  Initialise static data members of class TraceEntryExit */
bool TraceEntryExit::logEntryExits = false;

/** Log function entry message. */
#define TRACE_ENTER(class_name, function_name, args) \
  std::clog << EntryPrefix << class_name << "::" << function_name; \
  if (!args.empty()) std::clog << " - " << args; \
  std::clog << "\n"; // Stream flush not required, so don't use std::endl

/** Log function exit message. */
#define TRACE_EXIT(class_name, function_name, args) \
  std::clog << Exit_Prefix << class_name << "::" << function_name; \
  if (!args.empty()) std::clog << " - " << args; \
  std::clog << "\n"; // Stream flush not required, so don't use std::endl

TraceEntryExit::TraceEntryExit(
    const std::string &class_name,
    const std::string &function_name,
    bool always_log)
    : TraceEntryExit(class_name, function_name, BLANK_STR, always_log) {
}

TraceEntryExit::TraceEntryExit(
    const std::string &class_name,
    const std::string &function_name,
    const std::string &arguments,
    bool always_log)
    : className(class_name), functionName(function_name), args(arguments), alwaysLog(always_log) {
  if (alwaysLog || logEntryExits) {
    TRACE_ENTER(this->className, this->functionName, this->args);
  }
}

TraceEntryExit::TraceEntryExit(
    const char *class_name,
    const char *function_name,
    bool always_log)
    : TraceEntryExit(class_name, function_name, BLANK, always_log) {
}

TraceEntryExit::TraceEntryExit(
    const char *class_name,
    const char *function_name,
    const char *arguments,
    bool always_log)
    : TraceEntryExit(
    *(std::make_unique<std::string>(class_name).get()),
    *(std::make_unique<std::string>(function_name).get()),
    *(std::make_unique<std::string>(arguments).get()),
    always_log) {
}

TraceEntryExit::~TraceEntryExit() {
  if (alwaysLog || logEntryExits) {
    TRACE_EXIT(this->className, this->functionName, this->args);
  }
}

bool TraceEntryExit::SetLogging(bool new_trace_level) {
  bool old_logEntryExits = logEntryExits;
  logEntryExits = new_trace_level;
  return old_logEntryExits;
}

TraceLevelOverride TraceLevelOverride::SetLogging(bool new_trace_level) {
  bool old_trace_level = TraceEntryExit::SetLogging(new_trace_level);
  return TraceLevelOverride(old_trace_level);
}

TraceLevelOverride::TraceLevelOverride(bool old_trace_level)
    : previous(old_trace_level) {
}

TraceLevelOverride::~TraceLevelOverride() {
  TraceEntryExit::SetLogging(this->previous);
}
