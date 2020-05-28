#include "invocation_binder/invocation_binder.h"

#include <cassert>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

enum class State { kNONE, kON, kOFF, kMAX };

class Object : public InvocationBinder<Object, State> {
 public:
  template <State>
  void Invoke() {
    assert(false);
  }
  State state() const { return state_; }

 private:
  State state_{};
};

template <>
void Object::Invoke<State::kNONE>() {
  state_ = State::kNONE;
}
template <>
inline void Object::Invoke<State::kON>() {
  state_ = State::kON;
}
template <>
inline void Object::Invoke<State::kOFF>() {
  state_ = State::kOFF;
}
SCENARIO("Object can change it's state") {
  GIVEN("Object inherited from invocation binder") {
    Object o;
    REQUIRE_EQ(o.state(), State::kNONE);
    WHEN("object call State::kON") {
      o.Call(State::kON);
      THEN("it's state must be kON");
      CHECK_EQ(o.state(), State::kON);
    }
    WHEN("object call State::kOFF") {
      o.Call(State::kOFF);
      THEN("it's state must be kOFF");
      CHECK_EQ(o.state(), State::kOFF);
    }
  }
}