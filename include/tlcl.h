/* Copyright (c) 2010 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* TPM Lightweight Command Library.
 *
 * A low-level library for interfacing to TPM hardware or an emulator.
 */

#ifndef TPM_LITE_TLCL_H_
#define TPM_LITE_TLCL_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define POSSIBLY_UNUSED __attribute__((unused))

#ifdef __STRICT_ANSI__
#define INLINE
#else
#define INLINE inline
#endif

/* Outputs an error message and quits the program.
 */
POSSIBLY_UNUSED
static void error(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  fprintf(stderr, "ERROR: ");
  vfprintf(stderr, format, ap);
  va_end(ap);
  exit(1);
}

/* Outputs a warning and continues.
 */
POSSIBLY_UNUSED
static void warning(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  fprintf(stderr, "WARNING: ");
  vfprintf(stderr, format, ap);
  va_end(ap);
}

#define assert(expr) do { if (!(expr)) { \
      error("assert fail: %s at %s:%d\n", \
            #expr, __FILE__, __LINE__); }} while(0)

/* Call this first.
 */
void TlclLibinit(void);

/* Sends a TPM_Startup(ST_CLEAR).  Note that this is a no-op for the emulator,
 * because it runs this command during initialization.
 */
void TlclStartup(void);

/* Run the self test.  Note---this is synchronous.  To run this in parallel
 * with other firmware, use ContinueSelfTest.
 */
void TlclSelftestfull(void);

/* Defines a space with permission [perm].  [index] is the index for the space,
 * [size] the usable data size.  Errors are ignored.
 */
void TlclDefineSpace(uint32_t index, uint32_t perm, uint32_t size);

/* Writes [length] bytes of [data] to space at [index].  The TPM error code is
 * returned (0 for success).
 */
uint32_t TlclWrite(uint32_t index, uint8_t *data, uint32_t length);

/* Reads [length] bytes from space at [index] into [data].  The TPM error code
 * is returned (0 for success).
 */
uint32_t TlclRead(uint32_t index, uint8_t *data, uint32_t length);

/* Write-locks space at [index].
 */
void TlclWriteLock(uint32_t index);

/* Read-locks space at [index].
 */
void TlclReadLock(uint32_t index);

/* Asserts physical presence in software.
 */
void TlclAssertPhysicalPresence(void);

/* Sets the nvLocked bit.
 */
void TlclSetNvLocked(void);

/* Returns 1 if the TPM is owned, 0 otherwise.
 */
int TlclIsOwned(void);

/* Issues a ForceClear.
 */
void TlclForceClear(void);

/* Issues a PhysicalEnable.
 */
void TlclPhysicalEnable(void);

/* Issues a PhysicalSetDeactivated.  Pass 0 to activate.  Returns result code.
 */
int TlclPhysicalSetDeactivated(uint8_t flag);

/* Gets some permanent flags of interest.  (Add more here as needed.)
 */
int TlclGetFlags(uint8_t* disable, uint8_t* deactivated);

#endif  /* TPM_LITE_TLCL_H_ */