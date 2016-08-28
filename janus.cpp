// janus.cpp

#include "interface.hpp"
#include "simple_interface_manager.hpp"
#include "readline_atom.hpp"
#include "writeline_atom.hpp"

int main(int argc, char *argv[])
{
  janus::SimpleInterfaceManager manager;
  janus::ReadlineAtom readline_atom;
  janus::WritelineAtom writeline_atom;
  manager.AddInterface(readline_atom.GetReadInterface());
  manager.AddInterface(writeline_atom.GetWriteInterface());
  manager.AddConnection(readline_atom.GetReadInterface(), writeline_atom.GetWriteInterface());
  manager.propagate();
  return 0;
}