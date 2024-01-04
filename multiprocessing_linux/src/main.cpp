#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

class ChildProcess
{
public:
    explicit ChildProcess(int processNumber) : m_ProcessNumber(processNumber)
    {
    }

    void Run()
    {
        std::cout << "Run() - thread ID = " << std::this_thread::get_id() << "\n";
        pid_t pid = fork();
        std::cout << "Fork() - thread ID = " << std::this_thread::get_id() << "\n";

        // fork() - system call - creates a new child process, which is almost indentical copy of the parent process. This includes the same code, variables, file descriptors, thread ID.
        // p - parent
        // c - child
        // pProcessID != pProcessID1 != pProcessID2
        // pThreadID = pThreadID1 = pThreadID2
        // fork()
        // {
        //  if(PARENT_PROCESS)
        //  {
        //   return childProcessID;
        //  }
        //  if(CHILD_PROCESS)
        //  {
        //   return 0;
        //  }
        // }

        // print all threads:
        // ps -eLf
        // UID          PID    PPID     LWP  C NLWP STIME TTY          TIME CMD
        // root         629     579     629  0    1 19:24 pts/2    00:00:00 ./exe
        // root         630     629     630  0    1 19:24 pts/2    00:00:00 ./exe
        // root         631     629     631  0    1 19:24 pts/2    00:00:00 ./exe
        // How do I know that there are 1 thread and 3 processes?
        // > NLWP(./exe) = 1 -> each ./exe process has 1 thread
        // > PID(./exe) = 629/630/631 -> 3 ./exe processes

        if (pid == -1)
        {
            std::cout << "PID = " << pid << " -> FORK FAILED\n";
            throw std::runtime_error("Fork failed!");
        }
        else if (pid == 0) // checks if I am inside child process
        {
            // Child process
            std::cout << "PID = " << pid << " -> INSIDE A CHILD PROCESS\n";
            PrintChildInfo();
            exit(EXIT_SUCCESS);
        }
        else
        {
            // Parent process (parent process holds the pid of the child process)
            std::cout << "PID = " << pid << " -> INSIDE A PARENT PROCESS, WHICH HOLDS CHILD PID = " << pid << "\n";
            s_ChildProcesses.push_back(pid); // store child processes ids
        }
    }

    static void WaitAll()
    {
        for (const auto &pid : s_ChildProcesses)
        {
            int status;
            waitpid(pid, &status, 0);
            std::cout << "Child process " << pid << " exited with status " << status << std::endl;
        }
    }

    void PrintChildInfo() const
    {
        pid_t pid = getpid();
        std::cout << "Child process " << m_ProcessNumber << " with PID: " << pid << " is running." << std::endl;
        sleep(10000);
    }

private:
    int m_ProcessNumber;
    static std::vector<pid_t> s_ChildProcesses;
};

std::vector<pid_t> ChildProcess::s_ChildProcesses;

int main()
{
    constexpr int numProcesses = 2;
    std::vector<std::unique_ptr<ChildProcess>> processes;

    try
    {
        for (int i = 0; i < numProcesses; ++i)
        {
            processes.push_back(std::make_unique<ChildProcess>(i + 1));
            processes.back()->Run();
        }

        ChildProcess::WaitAll();

        std::cout << "Parent process (thread ID = " << std::this_thread::get_id() << ") done." << std::endl;
        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
