#include <idc.idc>
#include "scan-lib.idc"

/**
 * Searches for the shell_register calls and renames all the appropriate shell functions
 */

static main()
{
  auto shell_register, y, inst;
  auto name, name_addr, details, details_addr, addr;

  shell_register = LocByName("shell_register");

  for( y=RfirstB0(shell_register); y != BADADDR; y=RnextB0(shell_register, y) )
  {
      inst = y;

      if (-1 == strstr(GetDisasm(inst), "call:D")) continue;
      if (GetOpnd(inst, 0) != "@ r12") continue;

      inst = PrevHead(inst, inst-10);

      if (-1 == strstr(GetDisasm(inst), "ldi:32")) continue;
      if (GetOpnd(inst, 1) != "r12") continue;
      if (GetOpnd(inst, 0) != "#shell_register") continue;

      inst = PrevHead(inst, inst-10);

      if (-1 == strstr(GetDisasm(inst), "ldi:32")) continue;
      if (GetOpnd(inst, 1) != "r0") continue;
      details_addr = GetOperandValue(inst, 0);
      details = GetString(details_addr, -1, 0);

      inst = PrevHead(inst, inst-10);

      if (-1 == strstr(GetDisasm(inst), "ldi:32")) continue;
      if (GetOpnd(inst, 1) != "r7") continue;
      addr = GetOperandValue(inst, 0);

      inst = PrevHead(inst, inst-10);

      if (-1 == strstr(GetDisasm(inst), "ldi:32")) continue;
      if (GetOpnd(inst, 1) != "r6") continue;
      name_addr = GetOperandValue(inst, 0);
      name = GetString(name_addr, -1, 0);

      Message("%x %s %s (%d)\n", addr, name, details,
              MakeName(addr, "shell_" + name)
              );

      AutoMark(addr, AU_PROC);      
      MakeFunction(addr, BADADDR);
      MakeStr(name_addr, BADADDR);
      MakeStr(details_addr, BADADDR);
      SetFunctionCmt(addr, details, 1);

  }


}

