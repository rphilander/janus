#include <memory>
#include <thread>
#include <vector>

#include "readline_atom.hpp"
#include "runtime.hpp"
#include "value.hpp"
#include "writeline_atom.hpp"

using namespace janus;

void runtime_main(Runtime *runtime)
{
  runtime->Run();
}

int main(int argc, char *argv[])
{
  Runtime runtime;
  std::thread runtime_thread(runtime_main, &runtime);

  runtime.AddAtom("Writeline", "writer");
  runtime.AddAtom("Readline", "reader");
  runtime.AddConnection("writer", "output", "reader", "input");
  runtime.AddConnection("reader", "output", "writer", "input");

  ValuePtr signal = std::make_shared<Value>();
  signal->has_name = false;
  signal->value_type = ValueType::SIGNAL;
  runtime.Write("reader", "input", signal);

  runtime_thread.join();

  return 0;
}