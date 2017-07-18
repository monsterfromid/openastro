/*****************************************************************************
 *
 * AltairgetState.c -- state querying for Altair cameras
 *
 * Copyright 2016,2017 James Fidell (james@openastroproject.org)
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

#include <oa_common.h>

#include <openastro/camera.h>

#include "oacamprivate.h"
#include "Altairoacam.h"
#include "Altairstate.h"


int
oaAltairCameraGetControlRange ( oaCamera* camera, int control, int64_t* min,
    int64_t* max, int64_t* step, int64_t* def )
{
  COMMON_INFO*	commonInfo = camera->_common;

  if ( !camera->OA_CAM_CTRL_TYPE( control )) {
    return -OA_ERR_INVALID_CONTROL;
  }

  *min = commonInfo->OA_CAM_CTRL_MIN( control );
  *max = commonInfo->OA_CAM_CTRL_MAX( control );
  *step = commonInfo->OA_CAM_CTRL_STEP( control );
  *def = commonInfo->OA_CAM_CTRL_DEF( control );
  return OA_ERR_NONE;
}


const FRAMESIZES*
oaAltairCameraGetFrameSizes ( oaCamera* camera )
{
  ALTAIRCAM_STATE*	cameraInfo = camera->_private;

  return &cameraInfo->frameSizes[ cameraInfo->binMode ];
}


int
oaAltairCameraGetFramePixelFormat ( oaCamera* camera, int depth )
{
  ALTAIRCAM_STATE*	cameraInfo = camera->_private;

  if ( !depth || depth == 8 ) {
    return cameraInfo->currentVideoFormat;
  }

  switch ( cameraInfo->currentVideoFormat ) {
    case OA_PIX_FMT_GREY8:
fprintf ( stderr, "%s: check >8-bit mono byte order\n", __FUNCTION__ );
      return OA_PIX_FMT_GREY16LE;

    case OA_PIX_FMT_RGB24:
fprintf ( stderr, "%s: check >8-bit RGB byte order\n", __FUNCTION__ );
      return OA_PIX_FMT_RGB48LE;
  }

fprintf ( stderr, "%s: check >8-bit byte order for video format %d\n", __FUNCTION__, cameraInfo->currentVideoFormat );
  return OA_PIX_FMT_RGB24;
}