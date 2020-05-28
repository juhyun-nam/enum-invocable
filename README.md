# invocable-helper

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/8fa51ba1fa464ed58f74329731fe8071)](https://app.codacy.com/manual/juhyun-nam/invocation-binder?utm_source=github.com&utm_medium=referral&utm_content=juhyun-nam/invocation-binder&utm_campaign=Badge_Grade_Dashboard)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
[![Build Status](https://travis-ci.org/juhyun-nam/invocation-binder.svg?branch=master)](https://travis-ci.org/juhyun-nam/invocation-binder)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/juhyun-nam/invocation-binder.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/juhyun-nam/invocation-binder/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/juhyun-nam/invocation-binder.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/juhyun-nam/invocation-binder/alerts/)
[![codecov](https://codecov.io/gh/juhyun-nam/invocation-binder/branch/master/graph/badge.svg)](https://codecov.io/gh/juhyun-nam/invocation-binder)

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
