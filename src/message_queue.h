#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>

/**
 * A simple message-queue for use with concurrent rendering
 */
template <class T> class MessageQueue {
public:
  void send(T &&msg);
  T receive();
  void clear();

private:
  std::deque<T> _queue;
  std::condition_variable _cond;
  std::mutex _mutex;
};

template <typename T> T MessageQueue<T>::receive() {
  std::unique_lock<std::mutex> lock(_mutex);
  _cond.wait(lock, [this] { return !_queue.empty(); });

  T t = std::move(_queue.back());
  _queue.pop_back();

  return t;
}

template <typename T> void MessageQueue<T>::send(T &&msg) {
  std::lock_guard<std::mutex> lock(_mutex);
  _queue.push_back(std::move(msg));

  _cond.notify_one();
}

template <typename T> void MessageQueue<T>::clear() {
  std::lock_guard<std::mutex> lock(_mutex);

  _queue.clear();

  _cond.notify_one();
}

#endif