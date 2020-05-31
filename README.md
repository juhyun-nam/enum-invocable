# invocation-binder

[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
[![Build Status](https://travis-ci.org/juhyun-nam/invocation-binder.svg?branch=master)](https://travis-ci.org/juhyun-nam/invocation-binder)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/juhyun-nam/invocation-binder.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/juhyun-nam/invocation-binder/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/juhyun-nam/invocation-binder.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/juhyun-nam/invocation-binder/alerts/)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/8fa51ba1fa464ed58f74329731fe8071)](https://app.codacy.com/manual/juhyun-nam/invocation-binder?utm_source=github.com&utm_medium=referral&utm_content=juhyun-nam/invocation-binder&utm_campaign=Badge_Grade_Dashboard)
[![codecov](https://codecov.io/gh/juhyun-nam/invocation-binder/branch/master/graph/badge.svg)](https://codecov.io/gh/juhyun-nam/invocation-binder)

## 목적
Enum과 멤버 메소드의 mapped function table을 자동으로 생성.

## The Gist

```cpp
enum class State {
  kON,
  kOFF
};
int main() {
  Object obj;
  obj.Call(State::kON);  // callON
  obj.Call(State::kOFF);  // callOFF
}

```
### AS-IS

```cpp
struct Object {
  // 반복적인 함수 정의
  void CallON() { state_ = State::kON; }
  void CallOFF() { state_ = State::kOFF; }

  using StateMap = std::map<State, void(Object::*)()>;
  void Call(State s) {
    static StateMap fn_table {
      // element 추가시 실수할 가능성이 있음
      {State::kON, &Object::CallON},
      {State::kOFF, &Object::CallOFF}
    };
    // mapping 구조체에 따라 추가적 연간 가능성
    auto elem = fn_table.find(s);
    this->*(elem->second)();
  }
  State state_{};
};

```

### TO-BE

```cpp
#include "invocation_binder.h"
// CRTP
struct Object : public InvocationBinder<Object, State> {
  // template 함수로 State 타입의 tag 역할
  template <State S>
  void Invoke() {
    state_ = S;
  }
  State state_{};
};
// element 순서, 추가 고려 등을 하지 않는다.
// 명시적 인스턴스화
template void Object::Invoke<State::kON>();
template void Object::Invoke<State::kOFF>();
```
