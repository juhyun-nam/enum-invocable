# invocable-helper

# The Gist

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
