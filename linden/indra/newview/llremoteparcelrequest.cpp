/**
 * @file llparcelrequest.cpp
 * @brief Implementation of the LLParcelRequest class.
 *
 * $LicenseInfo:firstyear=2006&license=internal$
 * 
 * Copyright (c) 2006-2007, Linden Research, Inc.
 * 
 * The following source code is PROPRIETARY AND CONFIDENTIAL. Use of
 * this source code is governed by the Linden Lab Source Code Disclosure
 * Agreement ("Agreement") previously entered between you and Linden
 * Lab. By accessing, using, copying, modifying or distributing this
 * software, you acknowledge that you have been informed of your
 * obligations under the Agreement and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#include "llviewerprecompiledheaders.h"

#include "llagent.h"
#include "llremoteparcelrequest.h"

#include "llpanelplace.h"
#include "llpanel.h"
#include "llhttpclient.h"
#include "llsdserialize.h"
#include "llviewerregion.h"
#include "llview.h"
#include "message.h"

LLRemoteParcelRequestResponder::LLRemoteParcelRequestResponder(LLViewHandle place_panel_handle)
{
	 mPlacePanelHandle = place_panel_handle;
}
/*virtual*/
void LLRemoteParcelRequestResponder::result(const LLSD& content)
{
	LLUUID parcel_id = content["parcel_id"];

	LLPanelPlace* place_panelp = (LLPanelPlace*)LLPanel::getPanelByHandle(mPlacePanelHandle);

	if(place_panelp)
	{
		place_panelp->setParcelID(parcel_id);
	}

}

/*virtual*/
void LLRemoteParcelRequestResponder::error(U32 status, const std::string& reason)
{
	llinfos << "LLRemoteParcelRequest::error("
		<< status << ": " << reason << ")" << llendl;
	LLPanelPlace* place_panelp = (LLPanelPlace*)LLPanel::getPanelByHandle(mPlacePanelHandle);

	if(place_panelp)
	{
		place_panelp->setErrorStatus(status, reason);
	}

}

