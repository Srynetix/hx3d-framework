#include "hx3d/utils/property.hpp"
#include "hx3d/utils/log.hpp"
#include "tests/tests.hpp"

namespace hx3d {

struct FloatS {
  float f;
  float g;
  float h;
};

class Obs: public PropertyObserver<FloatS> {
public:
  bool observed;

  Obs(): observed(false) {}

  virtual void observe(const FloatS& curr, const FloatS& n) override {
    observed = true;
  }
};

TEST_F(Tests, Properties) {
  Obs observer;

  Property<FloatS> prop({1.f, 1.f, 1.f});
  prop.addObserver(&observer);

  prop = {0.f, 1.f, 1.f};

  ASSERT_TRUE(observer.observed);

  bool cbValue = false;

  CallbackProperty<FloatS> cbProp({1.f, 1.f, 1.f}, [&cbValue](const FloatS& curr, const FloatS& n){
    cbValue = true;
  });

  cbProp = {0.f, 1.f, 1.f};

  ASSERT_TRUE(cbValue);
}

} /* hx3d */
