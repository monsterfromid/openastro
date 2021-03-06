/*****************************************************************************
 *
 * EUVCstate.h -- EUVC state header
 *
 * Copyright 2015,2017,2018,2019
 *   James Fidell (james@openastroproject.org)
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

#ifndef OA_EUVC_STATE_H
#define OA_EUVC_STATE_H

#include <sys/types.h>
#include <libusb-1.0/libusb.h>
#include <pthread.h>

#include "sharedState.h"

typedef struct EUVC_STATE {

#include "sharedDecs.h"

  uint8_t               cameraTypeFlags;
  uint8_t		controlInterfaceNo;
  uint8_t		controlEndpoint;
  uint8_t		streamInterfaceNo;
  uint8_t		streamEndpoint;
  uint8_t		terminalId;
  uint8_t		processingUnitId;
  uint8_t		processingSourceId;
  uint64_t		puControlsBitmap;
  uint64_t		termControlsBitmap;
  int			haveComponentWhiteBalance;
  int			colourFormats;
  uint32_t		minPixelClock;
  uint32_t		maxPixelClock;
  uint8_t		overflowTransmit;
  // USB connection data
  libusb_context*       usbContext;
  libusb_device_handle* usbHandle;
	int							reattachControlIface;
	int							reattachStreamIface;
  // video mode settings
  // buffering for image transfers
  frameBuffer*		buffers;
  struct libusb_transfer* transfers[ EUVC_NUM_TRANSFER_BUFS ];
  unsigned char*	transferBuffers[ EUVC_NUM_TRANSFER_BUFS ];
  // camera status
  unsigned int          isColour;
  unsigned int          frameFormat;
  uint64_t		droppedFrames;
  struct libusb_transfer* statusTransfer;
  uint8_t		statusBuffer[32];
  unsigned int		frameRateNumerator;
  unsigned int		frameRateDenominator;
  uint8_t		streamFrameId;
  unsigned int		receivedBytes;
  // camera settings
  unsigned int          binMode;
  unsigned int          sizeIndex;
  int32_t		currentPan;
  int32_t		currentTilt;
  // image settings
  unsigned int          bytesPerPixel;
  struct frameExtras*   frameInfo[ OA_MAX_BINNING+1 ];
  FRAMERATES*		frameRates;
  uint32_t		currentPixelClock;
  uint32_t		currentFrameRate;
  // control values
  uint8_t		autoExposure;
  uint8_t		autoWhiteBalance;
  unsigned int		currentGain;
  unsigned int		currentBrightness;
  unsigned int		currentExposure;
  unsigned int		currentBlueBalance;
  unsigned int		currentRedBalance;
  // thread management
  pthread_mutex_t       usbMutex;
  pthread_t		eventHandler;

  pthread_mutex_t	videoCallbackMutex;
	// discrete auto exposure menu item ids
	unsigned int		numAutoExposureItems;
	int64_t					autoExposureMenuItems[8];
} EUVC_STATE;

#endif	/* OA_EUVC_STATE_H */
