
print ".text\n\n\n";

print <<DEFINE;

#ifndef CHDK_APP
  // For applications
  #define LABEL(l) .globl l;\
  l:;
#else
  // For CHDK core itself
  #define LABEL(l)
#endif



DEFINE

while(<>) {
   
   next unless /([0-9a-fA-F]+) \s+ \w \s+ ([\w\d_]+) /x;
   
   print "LABEL($2)\n";
   print "  LDR pc, [pc, #-4]\n";
   print "  .word 0x$1\n";
   print "  .asciz \"$2\"\n";
   print "  .align 3";
   print "\n\n";

}

