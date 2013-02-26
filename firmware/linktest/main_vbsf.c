/* Copyright (c) 2013 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "vboot_api.h"

int main(void)
{
  /* vboot_api.h - entry points INTO vboot_reference */
  VbSelectFirmware(0, 0);
  VbUpdateFirmwareBodyHash(0, 0, 0);
  return 0;
}
