#include "hx3d/utils/benchmark.hpp"
#include "hx3d/utils/algorithm.hpp"
#include "hx3d/math/random.hpp"
#include "hx3d/utils/log.hpp"

#include "tests/tests.hpp"

namespace hx3d {

TEST_F(Tests, AlgosTest) {
  Benchmark b;

  b.multiBench(
    Benchmark::Measure("Apply", [](){
      std::vector<int> v = algo::range(0, 100000);
      algo::apply(v, [](int& v){
        v += 1;
      });
    }),
    Benchmark::Measure("Apply manual", [](){
      std::vector<int> v = algo::range(0, 100000);
      for (auto& i: v) {
        i = i+1;
      }
    })
  );

  b.multiBench(
    Benchmark::Measure("Map", [](){
      std::vector<int> v = algo::range(0, 100000);
      std::vector<int> mod = algo::map(v, [](const int& i) {
        return i * 2;
      });
    }),
    Benchmark::Measure("Map manual", [](){
      std::vector<int> v = algo::range(0, 100000);
      std::vector<int> mod(v.size());
      for (auto& i: v) {
        mod[i] = i * 2;
      }
    })
  );
}

}
