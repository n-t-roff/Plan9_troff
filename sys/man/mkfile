_MAN1DIR =	$(DWBHOME)/$(MAN1DIR)
_MAN5DIR =	$(DWBHOME)/$(MAN5DIR)

all clean:

install:
		@[ -d $(_MAN1DIR) ] || mkdir -p $(_MAN1DIR)
		cd 1; \
		for i in *; do \
			install -m 644 $$i $(_MAN1DIR)/$$i.1; \
		done
		@[ -d $(_MAN5DIR) ] || mkdir -p $(_MAN5DIR)
		cd 6; \
		for i in *; do \
			install -m 644 $$i $(_MAN5DIR)/$$i.5; \
		done

uninstall:
		cd 1; \
		for i in *; do \
			rm -f $(_MAN1DIR)/$$i.1; \
		done
		@rmdir $(_MAN1DIR) 2> /dev/null || true
		cd 6; \
		for i in *; do \
			rm -f $(_MAN5DIR)/$$i.5; \
		done
		@rmdir $(_MAN5DIR) 2> /dev/null || true
