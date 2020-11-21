#include "MultiplayerWireworld/Automaton.hpp"
#include "MultiplayerWireworld/Shapes.hpp"
#include "test_macro.hpp"

void correct_test_passes() {}
void incorrect_test_does_not_pass() { ASSERT_EQ(1, 2); }

void assert_eq_passes_for_equal_arguments() { ASSERT_EQ(1, 1); }
void assert_eq_fails_for_inequal_arguments() { ASSERT_EQ(1, 2); }

void assert_neq_fails_for_equal_arguments() { ASSERT_NEQ(1, 1); }
void assert_neq_passes_for_inequal_arguments() { ASSERT_NEQ(1, 2); }

void assert_passes_for_valid_condition() { ASSERT(2 + 2 == 4); }
void assert_fails_for_invalid_condition() { ASSERT(2 + 2 == 5); }

void meta_tests()
{
  std::cout << "[Meta tests]\n";
  test(correct_test_passes);
  test(incorrect_test_does_not_pass);
  test(assert_eq_passes_for_equal_arguments);
  test(assert_eq_fails_for_inequal_arguments);
  test(assert_neq_fails_for_equal_arguments);
  test(assert_neq_passes_for_inequal_arguments);
  test(assert_passes_for_valid_condition);
  test(assert_fails_for_invalid_condition);
}

int main()
{
  meta_tests();
  multiplayer_wireworld_automaton::automaton::run_all_tests();
  grid_shapes::run_all_tests();
}
