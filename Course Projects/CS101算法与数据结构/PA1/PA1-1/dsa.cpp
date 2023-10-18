#include "dsa.h"
#include <cstdlib>
#include <functional>
#include <optional>

namespace part_queue {
std::array<Value,CAPACITY>data;
size_t head , tail;
Queue::Queue() {
  head = 0;
  tail = 0;
}
bool Queue::empty() const {
  return (head == tail);
}
std::optional<Value> Queue::pop() {
  if (empty()) {
    return std::nullopt;
  } else {
    size_t temp = data[head];
    head = (head + 1) % CAPACITY;
    return temp;
  }
}
void Queue::push(Value value) {
  if (tail == CAPACITY) {
    tail = 0;
  }
  data[tail] = value;
  tail++;
}
} // namespace part_queue

namespace part_stack {
std::array<Value,CAPACITY> data;
size_t stack_top;
Stack::Stack() {
  stack_top = 0;
  data[stack_top] = 0;
}
bool Stack::empty() const {
  return (stack_top == 0);
}
std::optional<Value> Stack::pop() {
  if (empty()) {
    return std::nullopt;
  } else {
    std::optional<Value> value = data[stack_top];
    stack_top--;
    return value;
  }
}
void Stack::push(Value value) {
  if (stack_top == CAPACITY) {
    return;
  } else {
    stack_top++;
    data[stack_top] = value;
  }
}
} // namespace part_stack

namespace part_hash_table {
using Status = Slot::Status;
HashTable::HashTable(std::function<size_t(Key)> hash_func) {
  this->hash_func=hash_func;
  for (size_t i = 0; i < CAPACITY; i++) {
    slots[i].status = Status::empty;
  }
}
std::array<Slot, CAPACITY> HashTable::dump() const {
  return slots;
}
bool HashTable::insert(Key key, Value value) {
  size_t hash = hash_func(key);
  size_t index = hash % CAPACITY;
  if(lookup(key)==value){
    return false;
  }
  while(slots[index].status==Status::occupied){
    index=(index+1)%CAPACITY;
  }
  slots[index].key=key;
  slots[index].value=value;
  slots[index].status=Status::occupied;
  return true;
}
std::optional<Value> HashTable::lookup(Key key) const {
  size_t hash = hash_func(key);
  size_t index = hash % CAPACITY;
  while (slots[index].status != Status::empty) {
    if (slots[index].status==Status::occupied&&slots[index].key == key) {
      return slots[index].value;
    }
    else {
      index=(index+1)%CAPACITY;
    }
  }
  return std::nullopt;
}
bool HashTable::erase(Key key) {
  size_t hash = hash_func(key);
  size_t index = hash % CAPACITY;
  if(lookup(key)==std::nullopt){
    return false;
  }
  while (slots[index].status != Status::empty) {
    if (slots[index].status==Status::occupied&&slots[index].key == key) {
      slots[index].status=Status::erased;
      return true;
    }
    else {
      index=(index+1)%CAPACITY;
    }
  }
}
} // namespace part_hash_table