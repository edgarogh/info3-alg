all: tp1

tp%: force
	cd $@; make

force:
	@true
