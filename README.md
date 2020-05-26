# invocable-helper

[![Build Status](https://travis-ci.org/juhyun-nam/invocation-binder.svg?branch=master)](https://travis-ci.org/juhyun-nam/invocation-binder)

## 목적
enum이 하나 있고, enum 요소 각각에 매칭되는 멤버 함수가 있다고 가정하면,

runtime에 각 enum 요소에 대해 매칭되는 멤버함수를 호출하고 싶을 수 있다.


invocation-binder는 해당 멤버함수들에대한 함수 테이블을 compile 타임에 생성하고

runtime에 enum에 대한 멤버함수 호출을 도와준다.

## The Gist

```cpp
#include "invocable_helper.h"

class Caller : public InvocableHelper<Caller> {
 public:
  enum class State {
    ONE,
    TWO,
    THREE
  };

  template <State S>
  void call();
};

template <>
inline void Caller::call<State::ONE>() {
  // ...logic...
}

template <>
inline void Caller::call<State::TWO>() {
  // ...logic...
}

template <>
inline void Caller::call<State::THREE>() {
  // ...logic...
}

int main() {
  Caller caller;
  caller.invoke(State::ONE);
  caller.invoke(State::TWO);
  caller.invoke(State::THREE);
}
```
