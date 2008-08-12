
print "#include <idc.idc>
static makeNames1()
{
";


while (<>) {
  next unless /(\d+):([\d\w]+) \s+ (Abs)?  \s+    (\S+)/ix;
  next if $4 =~ /^a/;
  next if $4 =~ /^nullsub/;
  
  $addr = hex($2);
  
  $addr += 0x4000000 if $3 eq "Abs"; #dirty hack!!
  
  printf "  MakeName(0x%08x, \"$4\");\n", $addr;
  
  unless ($4 =~ /TBR_/) {
    printf "  AutoMark(0x%08x, AU_PROC);\n", $addr;
    #printf "  MakeFunction(0x%08x, BADADDR);\n", $addr;
  }
}

print "}";