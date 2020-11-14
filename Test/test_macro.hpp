#ifndef TEST_MACRO_HPP
#define TEST_MACRO_HPP

#include <iostream>
#include <sstream>
#include <string>

int indent_count = 0;

void passed(std::string test_name)
{
  for (int _ = 0; _ < indent_count; _++) std::cout << " ";
  std::cout << "\033[1;32m" << test_name << "\033[0m" << '\n';
}

void failed(std::string test_name, std::string error)
{
  for (int _ = 0; _ < indent_count; _++) std::cout << " ";
  std::cout << "\033[1;31m" << test_name << "\n  " << error << "\033[0m"
            << '\n';
}

struct FailedAssertion
{
  std::string message;
};

template <typename T, typename U>
void ASSERT_EQ(T lhs, U rhs)
{
  if (lhs != rhs)
  { throw FailedAssertion{"Assertion failed, arguments are not equal"}; };
}

template <typename T, typename U>
void ASSERT_NEQ(T lhs, U rhs)
{
  if (lhs == rhs)
  { throw FailedAssertion{"Assertion failed, arguments are equal"}; };
}

#define ASSERT(cond)                                            \
  {                                                             \
    if (!cond)                                                  \
    {                                                           \
      std::stringstream error_message;                          \
      error_message << "Assertion failed, expected: " << #cond; \
      throw FailedAssertion{error_message.str()};               \
    }                                                           \
  }

void begin_group(std::string group)
{
  std::cout << '\n';
  for (int _ = 0; _ < indent_count; _++) std::cout << " ";
  std::cout << "[" << group << "]\n";
  indent_count += 2;
}

void end_group(std::string group) { indent_count -= 2; }

#define test(t)                   \
  {                               \
    try                           \
    {                             \
      (t)();                      \
      passed(#t);                 \
    }                             \
    catch (FailedAssertion error) \
    {                             \
      failed(#t, error.message);  \
    }                             \
  }

#endif

