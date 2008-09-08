
// Change to your ROM start
#define ROM_START   0xBFA00000
#define ROM_END     (0xBFA00000+0x800000)

#define TRUE   1
#define FALSE  0

static getString(addr)
{
  auto origa, stringRead;

  stringRead = "";
  origa = addr;

  while(1)
  {
      if (Byte(addr) == 0) break;
      if (addr-origa > 60) return stringRead;
      
      stringRead = form("%s%c", stringRead, Byte(addr));

      addr = addr + 1;
  }

  return stringRead;
}


static GetStringPascal(addr)
{
  auto origa, stringRead, length;

  stringRead = "";
  length = Word(addr);
  addr = addr+2;

  if (length < 2) return 0;
  if (length > 50) return 0;

  for(; length > 0; length = length-1)
  {
      auto c;
      c = Word(addr);
      if (c < 0x2D || c > 0x7F) c = '_';

      stringRead = form("%s%c", stringRead, c);
      addr = addr + 2;
  }

  return stringRead;
}


static replace(str, src, dest)
{
  auto idx;

  while(1)
  {
      idx = strstr(str,src);
      if (idx == -1) break;

      str = substr(str, 0, idx) + dest + substr(str, idx+strlen(src), strlen(str));

  }

  return str;
}

static abs(val)
{
   if (val > 0) return val;
   else return -val;

}
