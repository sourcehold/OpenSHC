/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'util/assertion.h'
*/

#define static_assert_cpp98(condition) typedef int _static_assert_cpp98_obj[(condition) ? 1 : -1];
#define static_assert_cpp98_obj(condition, obj) typedef int _static_assert_cpp98 ## _ ## obj[(condition) ? 1 : -1];