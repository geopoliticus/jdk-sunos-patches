$NetBSD$

Fix building on SunOS in C99 mode.

--- src/hotspot/os/solaris/os_solaris.cpp.orig	2019-01-08 09:40:30.000000000 +0000
+++ src/hotspot/os/solaris/os_solaris.cpp
@@ -169,6 +169,8 @@ extern "C" {
 
   static int lwp_cond_init(cond_t *cv, int scope, void *arg){ memset(cv, 0, sizeof(cond_t)); return 0; }
   static int lwp_cond_destroy(cond_t *cv)                   { return 0; }
+  int memcntl(void *, size_t, int, void *, int, int);
+  int meminfo(const uint64_t *, int, const uint_t *, int, uint64_t *, uint_t *);
 }
 
 // "default" initializers for pthread-based synchronization
@@ -2317,7 +2319,7 @@ void os::pd_commit_memory_or_exit(char*
 
 // Uncommit the pages in a specified region.
 void os::pd_free_memory(char* addr, size_t bytes, size_t alignment_hint) {
-  if (madvise(addr, bytes, MADV_FREE) < 0) {
+  if (posix_madvise(addr, bytes, MADV_FREE) < 0) {
     debug_only(warning("MADV_FREE failed."));
     return;
   }
@@ -2346,7 +2348,7 @@ void os::pd_realign_memory(char *addr, s
 // Tell the OS to make the range local to the first-touching LWP
 void os::numa_make_local(char *addr, size_t bytes, int lgrp_hint) {
   assert((intptr_t)addr % os::vm_page_size() == 0, "Address should be page-aligned.");
-  if (madvise(addr, bytes, MADV_ACCESS_LWP) < 0) {
+  if (posix_madvise(addr, bytes, MADV_ACCESS_LWP) < 0) {
     debug_only(warning("MADV_ACCESS_LWP failed."));
   }
 }
@@ -2354,7 +2356,7 @@ void os::numa_make_local(char *addr, siz
 // Tell the OS that this range would be accessed from different LWPs.
 void os::numa_make_global(char *addr, size_t bytes) {
   assert((intptr_t)addr % os::vm_page_size() == 0, "Address should be page-aligned.");
-  if (madvise(addr, bytes, MADV_ACCESS_MANY) < 0) {
+  if (posix_madvise(addr, bytes, MADV_ACCESS_MANY) < 0) {
     debug_only(warning("MADV_ACCESS_MANY failed."));
   }
 }
