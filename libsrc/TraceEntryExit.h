#pragma once

#include <string>
#include <string_view>

/**
 * Class: TraceLevelOverride
 * =========================
 * A RAII (Resource Acquisition Is Initialization) / aka lifetime control ("Destruction is Resource Relinquishment")
 * class to allow temporarily override the tracing level.
 */
class TraceLevelOverride {
  bool previous;

public:
  static TraceLevelOverride SetLogging(bool new_trace_level);

  explicit TraceLevelOverride(bool old_trace_level);

  // Copy constructors.
  TraceLevelOverride(const TraceLevelOverride&) = default;
  TraceLevelOverride& operator=(const TraceLevelOverride&) = default;
  // Move constructors.
  TraceLevelOverride(TraceLevelOverride&&) = default;
  TraceLevelOverride& operator=(TraceLevelOverride&&) = default;

  virtual ~TraceLevelOverride();
};

/**
 * Class: TraceEntryExit
 * =====================
 * Provides entry and exit tracing facilities.
 *
 * When the destructor is called for an object of this class,
 *  an appropriate message will be logged to the stream std::clog stream
 *  if the flag `logEntryExits` is set.
 */
class TraceEntryExit {
  static bool logEntryExits; // If true, then entry and exit trace will be logged.

  const std::string className;
  const std::string functionName;
  const std::string args;

  bool alwaysLog = false;

public:
  constexpr static std::string_view EntryPrefix = ">>>> Enter ";
  constexpr static std::string_view Exit_Prefix = "<<<< Exit_ ";

  // Copy constructors for File object.
  TraceEntryExit(const TraceEntryExit&) = default;
  TraceEntryExit& operator=(const TraceEntryExit&) = delete;
  // Move constructors for File object.
  TraceEntryExit(TraceEntryExit&&) = default;
  TraceEntryExit& operator=(TraceEntryExit&&) = delete;

  /**
   * Constructor: TraceEntryExit
   * @param class_name - Class name.
   * @param function_name - Function name.
   * @param always_log - Override the logEntryExists flag for this trace object.
   */
  TraceEntryExit(const std::string& class_name, const std::string& function_name, bool always_log = false);

  /**
   * Constructor: TraceEntryExit
   * @param class_name - Class name.
   * @param function_name - Function name.
   * @param arguments - Function arguments info, if any.
   * @param always_log - Override the logEntryExists flag for this trace object.
   */
  TraceEntryExit(const std::string& class_name,
                 const std::string& function_name,
                 const std::string& arguments,
                 bool               always_log = false);

  /**
   * Destructor: ~TraceEntryExit
   * Destroys the object,
   *  and may or may not display the exit message,
   *  depending on the value of the `logEntryExits` variable.
   */
  ~TraceEntryExit();

  static bool SetLogging(bool new_trace_level);
};
