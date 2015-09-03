#include "hx3d/utils/log.hpp"
#include "tests/tests.hpp"

namespace hx3d {

TEST_F(Tests, InfoWrite) {

  Log.Info("Ceci est une info.");
  Log.Error("Ceci est une erreur.");
  Log.Shader("Ceci est une info du shader.");
}

}
