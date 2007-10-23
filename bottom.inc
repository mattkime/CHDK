
ifneq ($(strip $(OBJS)),)
#include $(OBJS:%.o=.dep/%.d)
endif

depend: depend-recursive $(foreach obj,  $(OBJS),  .dep/$(subst .o,.d,$(obj))   )



