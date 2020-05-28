#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <optional>

/**
 * A simple message-queue for use with concurrent rendering
 */
template <class T> class MessageQueue {
public:
  void send(T &&msg);
  std::optional<T> receive();
  void clear();
  void stop() { running = false; }

private:
  std::deque<T> _queue;
  std::condition_variable _cond;
  std::mutex _mutex;
  bool running{true};
};

template <typename T> std::optional<T> MessageQueue<T>::receive() {
  std::unique_lock<std::mutex> lock(_mutex);
  // Wait 20 milliseconds for a task to become available
  _cond.wait_for(lock, std::chrono::milliseconds(20));
  // When the queue is empty, return nothing so that the task can check if
  // it's still supposed to be running
  if (_queue.empty()) {
    return {};
  }

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

  _cond.notify_all();
}

#endif