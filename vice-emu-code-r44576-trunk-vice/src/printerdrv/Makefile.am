AM_CPPFLAGS = \
	@VICE_CPPFLAGS@ \
	@ARCH_INCLUDES@ \
	-I$(top_builddir)/src \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/joyport \
	-I$(top_srcdir)/src/userport \
	-I$(top_srcdir)/src/vdrive

AM_CFLAGS = @VICE_CFLAGS@

AM_CXXFLAGS = @VICE_CXXFLAGS@

AM_LDFLAGS = @VICE_LDFLAGS@


noinst_LIBRARIES = libprinterdrv.a

libprinterdrv_a_SOURCES = \
	driver-select.c \
	driver-select.h \
	drv-1520.c \
	drv-1520.h \
	drv-ascii.c \
	drv-ascii.h \
	drv-mps803.c \
	drv-mps803.h \
	drv-nl10.c \
	drv-nl10.h \
	drv-raw.c \
	drv-raw.h \
	interface-serial.c \
	interface-serial.h \
	interface-userport.c \
	interface-userport.h \
	output-graphics.c \
	output-graphics.h \
	output-select.c \
	output-select.h \
	output-text.c \
	output-text.h \
	output.h \
	printer-serial.c \
	printer-userport.c \
	printer.c \
	printer.h

