#include "greatstr/GreatStr.h"
#include <benchmark/benchmark.h>
#include <random>
#include <string>

std::string getRandomStr(size_t Length) {
  static const char Alphanum[] = "123456789"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";
  static std::random_device Rd;
  static std::mt19937 Gen(Rd());
  static std::uniform_int_distribution<> Dis(0, sizeof(Alphanum) - 2);

  std::string Result;
  Result.reserve(Length);
  for (size_t Idx = 0; Idx < Length; ++Idx)
    Result += Alphanum[Dis(Gen)];
  return Result;
}

static void GreatStrDefaultConstructor(benchmark::State &State) {
  for (auto _ : State) {
    GreatCharStr S;
    benchmark::DoNotOptimize(S);
  }
}
BENCHMARK(GreatStrDefaultConstructor);

static void StdStringDefaultConstructor(benchmark::State &State) {
  for (auto _ : State) {
    std::string S;
    benchmark::DoNotOptimize(S);
  }
}
BENCHMARK(StdStringDefaultConstructor);

static void GreatStrFromCString(benchmark::State &State) {
  std::string Cstr = getRandomStr(State.range(0));
  for (auto _ : State) {
    GreatCharStr S(Cstr.c_str());
    benchmark::DoNotOptimize(S);
  }
}
BENCHMARK(GreatStrFromCString)->Arg(10)->Arg(100);

static void StdStringFromCString(benchmark::State &State) {
  std::string Cstr = getRandomStr(State.range(0));
  for (auto _ : State) {
    std::string S(Cstr.c_str());
    benchmark::DoNotOptimize(S);
  }
}
BENCHMARK(StdStringFromCString)->Arg(10)->Arg(100);

static void GreatStrCopyConstructor(benchmark::State &State) {
  GreatCharStr Original(getRandomStr(State.range(0)).c_str());
  for (auto _ : State) {
    GreatCharStr Copy = Original;
    benchmark::DoNotOptimize(Copy);
  }
}
BENCHMARK(GreatStrCopyConstructor)->Arg(10)->Arg(100);

static void StdStringCopyConstructor(benchmark::State &State) {
  std::string Original = getRandomStr(State.range(0));
  for (auto _ : State) {
    std::string Copy = Original;
    benchmark::DoNotOptimize(Copy);
  }
}
BENCHMARK(StdStringCopyConstructor)->Arg(10)->Arg(100);

BENCHMARK_MAIN();
