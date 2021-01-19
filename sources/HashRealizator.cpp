//
// Copyright 2020 MrShip15 mr.shi15@gmail.ru
//

#include "HashRealizator.hpp"

const unsigned int Mb = 1024 * 1024;
const unsigned int OutForm = 4;

void SetLogs() {
  auto FileTraceLog = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/MrShip15/lr/lr6/LR_6/Logs"
          "/Trace_%N.log",
      boost::log::keywords::rotation_size = 10 * Mb,
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: [%Message%]");
  FileTraceLog->set_filter(boost::log::trivial::severity >=
                           boost::log::trivial::trace);
  auto FileInfoLog = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/MrShip15/lr/lr6/LR_6/Logs"
          "/Info_%N.log",
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: [%Message%]");
  FileInfoLog->set_filter(boost::log::trivial::severity ==
                          boost::log::trivial::info);
  auto ConsoleLog = boost::log::add_console_log(
      std::cout, boost::log::keywords::format =
                     "[%TimeStamp%][%Severity%][%ThreadID%]: [%Message%]");
  ConsoleLog->set_filter(boost::log::trivial::severity >=
                         boost::log::trivial::trace);
}

void JsonPrinter::NewHash(const std::string& SomeStr, const std::string& hash,
                          std::time_t timestamp) {
  std::scoped_lock<std::mutex> lock(mut);
  std::stringstream ss;
  ss << std::uppercase << std::hex << std::stoi(SomeStr);
  json j;
  j["Message"] = ss.str();
  j["Hash"] = hash;
  j["TimeStamp"] = timestamp;
  J_Arr.push_back(j);
}

std::ostream& operator<<(std::ostream& out, const JsonPrinter& JP) {
  std::scoped_lock<std::mutex> lock(JP.mut);
  out << JP.J_Arr.dump(OutForm);
  return out;
}
