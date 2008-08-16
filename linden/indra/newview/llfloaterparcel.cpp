/** 
 * @file llfloaterparcel.cpp
 * @brief LLFloaterParcel class implementation
 * Parcel information as shown in a floating window from secondlife:// command
 * handler.  
 *
 * $LicenseInfo:firstyear=2002&license=internal$
 * 
 * Copyright (c) 2002-2007, Linden Research, Inc.
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

#include "llfloaterparcel.h"

// viewer project includes
#include "llcommandhandler.h"
#include "llpanelplace.h"
#include "llvieweruictrlfactory.h"

// linden library includes
#include "lluuid.h"

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------

LLMap< const LLUUID, LLFloaterParcelInfo* > gPlaceInfoInstances;

class LLParcelHandler : public LLCommandHandler
{
public:
	LLParcelHandler() : LLCommandHandler("parcel") { }
	bool handle(const std::vector<std::string>& params)
	{
		if (params.size() < 2)
		{
			return false;
		}
		LLUUID parcel_id;
		if (!parcel_id.set(params[0], FALSE))
		{
			return false;
		}
		if (params[1] == "about")
		{
			LLFloaterParcelInfo::show(parcel_id);
			return true;
		}
		return false;
	}
};
LLParcelHandler gParcelHandler;

//-----------------------------------------------------------------------------
// Member functions
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------

void*	LLFloaterParcelInfo::createPanelPlace(void*	data)
{
	LLFloaterParcelInfo* self = (LLFloaterParcelInfo*)data;
	self->mPanelParcelp = new LLPanelPlace(); // allow edit self
	gUICtrlFactory->buildPanel(self->mPanelParcelp, "panel_place.xml");
	return self->mPanelParcelp;
}

//----------------------------------------------------------------------------


LLFloaterParcelInfo::LLFloaterParcelInfo(const std::string& name, const LLUUID &parcel_id)
:	LLFloater(name),
	mParcelID( parcel_id )
{
	mFactoryMap["place_details_panel"] = LLCallbackMap(LLFloaterParcelInfo::createPanelPlace, this);
	gUICtrlFactory->buildFloater(this, "floater_preview_url.xml", &getFactoryMap());
	gPlaceInfoInstances.addData(parcel_id, this);
}

// virtual
LLFloaterParcelInfo::~LLFloaterParcelInfo()
{
	// child views automatically deleted
	gPlaceInfoInstances.removeData(mParcelID);

}

void LLFloaterParcelInfo::displayParcelInfo(const LLUUID& parcel_id)
{
	mPanelParcelp->setParcelID(parcel_id);
}

// static
LLFloaterParcelInfo* LLFloaterParcelInfo::show(const LLUUID &parcel_id)
{
	if (parcel_id.isNull())
	{
		return NULL;
	}

	LLFloaterParcelInfo *floater;
	if (gPlaceInfoInstances.checkData(parcel_id))
	{
		// ...bring that window to front
		floater = gPlaceInfoInstances.getData(parcel_id);
		floater->open();	/*Flawfinder: ignore*/
		floater->setFrontmost(true);
	}
	else
	{
		floater =  new LLFloaterParcelInfo("parcelinfo", parcel_id );
		floater->center();
		floater->open();	/*Flawfinder: ignore*/
		floater->displayParcelInfo(parcel_id);
		floater->setFrontmost(true);
	}

	return floater;
}


