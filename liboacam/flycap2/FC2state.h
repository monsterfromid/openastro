/*****************************************************************************
 *
 * FC2state.h -- Point Grey Gig-E camera state header
 *
 * Copyright 2015,2016,2018,2019 James Fidell (james@openastroproject.org)
 *
 * License:
 *
 * This file is part of the Open Astro Project.
 *
 * The Open Astro Project is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Open Astro Project is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Open Astro Project.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#ifndef OA_FC2_STATE_H
#define OA_FC2_STATE_H

#include <flycapture/C/FlyCapture2_C.h>
#include <openastro/util.h>

#include "sharedState.h"


typedef struct FC2_STATE {

#include "sharedDecs.h"

  // libdc1394 connection data
  fc2Context*		pgeContext;
  // video mode settings
  int			maxBytesPerPixel;
  unsigned int		pixelFormats;
  int			bigEndian;
  unsigned int		availableBinModes;
  // buffering for image transfers
  frameBuffer*		buffers;
	FRAME_METADATA*		metadataBuffers;
  // camera status
  int			colour;
  int			cfaPattern;
	int			haveFrameCounter;
  // image settings
  struct modeInfo*	frameModes[ OA_MAX_BINNING+1 ];
  FRAMERATES		frameRates;
  int			frameRateNumerator;
  int			frameRateDenominator;
  fc2PixelFormat	currentVideoFormat;
  int			currentFrameFormat;
  int			currentMode;
  float			currentBytesPerPixel;
  unsigned int		binMode;
  // control values
  int64_t		currentAbsoluteExposure;
  int32_t		currentRedBalance;
  int32_t		currentBlueBalance;
  // trigger/strobe data
  int32_t		triggerModeCount;
  int64_t*		triggerModes;
  int8_t		triggerEnable;
  int16_t		modeMask;
  int8_t		triggerEnabled;
  int8_t		triggerGPIO;
  int8_t		triggerCurrentMode;
  int8_t		triggerCurrentPolarity;
  int8_t		triggerDelayEnable;
  int8_t		triggerDelayEnabled;
  int64_t		triggerCurrentDelay;
  int8_t		strobeEnable;
  int8_t		strobeEnabled;
  int8_t		strobeGPIO;
  int8_t		strobeCurrentPolarity;
  int64_t		strobeCurrentDelay;
  int64_t		strobeCurrentDuration;
} FC2_STATE;

#endif	/* OA_FC2_STATE_H */
