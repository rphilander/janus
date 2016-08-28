// Copied from: http://stackoverflow.com/questions/4792449/c0x-has-no-semaphores-how-to-synchronize-threads/19659736#19659736

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
  Semaphore (unsigned int count = 0);
  void notify();
  void wait();

private:
    std::mutex m_mutex;
    std::condition_variable m_condvar;
    unsigned int m_count;
};
