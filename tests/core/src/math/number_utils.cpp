#include "hx3d/math/number_utils.hpp"
#include "tests/tests.hpp"

namespace hx3d {

TEST_F(Tests, NumberUtils) {

  ASSERT_EQ(10, math::clamp(11, 0, 10));

  ASSERT_EQ(0, math::mclamp(500, 0, 10));
  ASSERT_EQ(1, math::mclamp(11, 0, 10));

  ASSERT_EQ(-9, math::mclamp(11, -10, 10));
  ASSERT_EQ(9, math::mclamp(-11, -10, 10));

  ASSERT_EQ(0, math::mclamp(2 + 1, 0, 3));
}

} /* hx3d */
