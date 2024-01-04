#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <stdexcept>
#include <utility>
#include <concepts>
#include <fcntl.h>  // Header for file control operations (open)
#include <unistd.h> // Header for POSIX operating system API functions (close, lseek)
#include <cstring>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

// fd = non-negative integer that serves as an abstract handle for accessing a file or an input/output resource in a computer OS.

// File descriptors are a low-level mechanism for input and output operations in Unix-like OSs. They provide a way to interact with files, sockets and other I/O resources.

class FileDescriptor
{
public:
    template <std::integral T>
        requires std::same_as<T, int>
    explicit FileDescriptor(T fd) : m_Fd{fd}
    {
        if (m_Fd == -1)
        {
            throw std::runtime_error("Failed to create file descriptor");
        }
    }

    FileDescriptor(const std::string &filePath)
    {
        // O_TRUNC = if the file is opened for writing (or appending) (O_WRONLY or O_RDWR) truncates its size to 0 (clear that file)

        // O_CREAT = create file if does not exist

        // S_IRUSR:
        // Read permission for the owner.

        // S_IWUSR:
        // Write permission for the owner.

        // S_IRGRP:
        // Read permission for the group.

        // S_IROTH:
        // Read permission for others (those who are neither the owner nor in the group).

        m_Fd = ::open(
            filePath.c_str(),
            O_RDWR | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (m_Fd == -1)
        {
            throw std::runtime_error("Failed to open file for both reading and writing");
        }
    }

    void Write(const char *data, size_t size)
    {
        if (m_Fd != -1)
        {
            ssize_t bytesWritten = ::write(m_Fd, data, size);
            if (bytesWritten == -1)
            {
                throw std::runtime_error("Error writing to the file");
            }
            // Seek back to the beginning of the file
            off_t offset = ::lseek(m_Fd, 0, SEEK_SET);
            if (offset == -1)
            {
                throw std::runtime_error("Error seeking to the beginning of the file");
            }
        }
    }

    ssize_t Read(char *buffer, size_t size) const
    {
        if (m_Fd != -1)
        {
            return ::read(m_Fd, buffer, size);
        }
        return -1;
    }

    FileDescriptor(const FileDescriptor &) = default;
    FileDescriptor &operator=(const FileDescriptor &) = default;

    FileDescriptor(FileDescriptor &&other) noexcept : m_Fd{std::exchange(other.m_Fd, -1)} {}
    FileDescriptor &operator=(FileDescriptor &&other) noexcept
    {
        if (this != &other)
        {
            Close();
            m_Fd = std::exchange(other.m_Fd, -1);
        }
        return *this;
    }

    // attribute that is used to indicate that the return value of a function should not be ignored. It is an attribute that provides a hint to the compiler, suggesting that the return value of the function is important and should be checked. When you mark a function with nodiscard, the compiler generates a warning if the return value of that function is not used in you code. This can help catch potential bugs or unintended side effects where the return value of a function is ignored.
    [[nodiscard]] int Get() const
    {
        return m_Fd;
    }

    void Close()
    {
        if (m_Fd != -1)
        {
            ::close(m_Fd);
            m_Fd = -1;
        }
    }

    ~FileDescriptor() = default;

private:
    int m_Fd;
};

int main()
{
    try
    {
        FileDescriptor fileDescriptor("file.txt");

        const char *dataToWrite = "Data written";
        fileDescriptor.Write(dataToWrite, strlen(dataToWrite));

        char buffer[100];
        ssize_t bytesRead = fileDescriptor.Read(buffer, sizeof(buffer));
        std::cout << sizeof(buffer) << std::endl;
        std::cout << bytesRead << std::endl;
        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';
            std::cout << "Read from file: " << buffer << std::endl;
        }

        std::cout << "File descriptor: " << fileDescriptor.Get() << std::endl;
        fileDescriptor.Get(); // Warning ignoring the value of function declared as nodiscard
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
