/// \file invocation_binder.hpp
/// \brief invocation_binder main header file
/// \author juhyun-nam
///

#ifndef INVOCATION_BINDER_INVOCATION_BINDER_H_
#define INVOCATION_BINDER_INVOCATION_BINDER_H_

#include <cstddef>
namespace detail {
template <typename Binder, int N>
struct BindingHelper {
  using target_t = typename Binder::target_t;
  using enum_t = typename Binder::enum_t;
  static void Set(Binder* ptr) {
    ptr->fn_array_[N] = &target_t::template Invoke<static_cast<enum_t>(N)>;
    BindingHelper<Binder, N - 1>::Set(ptr);
  }
};
template <typename Binder>
struct BindingHelper<Binder, 0> {
  using target_t = typename Binder::target_t;
  using enum_t = typename Binder::enum_t;
  static void Set(Binder* ptr) {
    ptr->fn_array_[0] = &target_t::template Invoke<static_cast<enum_t>(0)>;
  }
};
}  // namespace detail

using std::size_t;
template <typename T, typename Enum>
class InvocationBinder {
  template <typename, int>
  friend struct detail::BindingHelper;

 public:
  using target_t = T;
  using enum_t = Enum;
  using mem_fn_t = void (T::*)();
  static constexpr size_t kMax = static_cast<size_t>(Enum::kMAX);
  InvocationBinder() {
    detail::BindingHelper<InvocationBinder, kMax - 1>::Set(this);
  }

  void Call(Enum e) { ((T*)(this)->*(fn_array_[static_cast<size_t>(e)]))(); }

 private:
  mem_fn_t fn_array_[kMax];
};

#endif  // INVOCATION_BINDER_INVOCATION_BINDER_H_
