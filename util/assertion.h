// Source - https://stackoverflow.com/questions/14621968/how-to-do-static-assert-with-macros
// Posted by Hashimoto
// Retrieved 11/4/2025, License - CC-BY-SA 4.0

template<bool Is_Condition_Met>
struct Static_assert_cpp98
{
  static void apply() {static const char junk[ Is_Condition_Met ? 1 : -1 ];}
};

template<>
struct Static_assert_cpp98<true>
{
  static void apply() {}
};

#define STATIC_ASSERT_CPP98(condition) Static_assert_cpp98<condition>::apply()
#if __cplusplus < 201103L
#define static_assert STATIC_ASSERT_CPP98
#endif