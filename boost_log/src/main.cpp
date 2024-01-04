#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

int main()
{
    // Initialize the log
    boost::log::add_common_attributes();

    boost::log::add_file_log(
        boost::log::keywords::file_name = "sample.log",
        boost ::log ::keywords ::rotation_size = 1 * 1024 * 1024,
        boost::log ::keywords ::auto_flush = true);

    int myInt = 42;
    BOOST_LOG_TRIVIAL(info) << "This is an informational message. Integer value: " << myInt;
    std::cout << "Success";
    return 0;
}
