$NetBSD$

Do not pull in openwin.

--- make/autoconf/lib-x11.m4.orig	2019-01-08 09:40:29.000000000 +0000
+++ make/autoconf/lib-x11.m4
@@ -94,7 +94,7 @@ AC_DEFUN_ONCE([LIB_SETUP_X11],
       AC_MSG_ERROR([Could not find X11 libraries. $HELP_MSG])
     fi
 
-    if test "x$OPENJDK_TARGET_OS" = xsolaris; then
+    if test "x$OPENJDK_TARGET_OS" = xnothankyou; then
       OPENWIN_HOME="/usr/openwin"
       X_CFLAGS="-I$SYSROOT$OPENWIN_HOME/include -I$SYSROOT$OPENWIN_HOME/include/X11/extensions"
       X_LIBS="-L$SYSROOT$OPENWIN_HOME/lib$OPENJDK_TARGET_CPU_ISADIR \
