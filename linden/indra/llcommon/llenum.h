/** 
 * @file llenum.h
 * @author Tom Yedwab
 * @brief Utility class for storing enum value <-> string lookup.
 *
 * Copyright (c) 2006-2007, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlife.com/developers/opensource/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at http://secondlife.com/developers/opensource/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 */

#ifndef LL_LLENUM_H
#define LL_LLENUM_H

class LLEnum
{
public:
	typedef std::pair<const std::string, const U32> enum_t;
	enum
	{
		UNDEFINED = 0xffffffff,
	};

	LLEnum(const enum_t values_array[], const U32 length)
	{
		for (U32 i=0; i<length; ++i)
		{
			mEnumMap.insert(values_array[i]);
			if (values_array[i].second >= mEnumArray.size())
			{
				mEnumArray.resize(values_array[i].second+1);
			}
			mEnumArray[values_array[i].second] = values_array[i].first;
		}
	}

	U32 operator[](std::string str)
	{
		std::map<const std::string, const U32>::iterator itor;
		itor = mEnumMap.find(str);
		if (itor != mEnumMap.end())
		{
			return itor->second;
		}
		return UNDEFINED;
	}

	const std::string operator[](U32 index)
	{
		if (index < mEnumArray.size())
		{
			return mEnumArray[index];
		}
		return "";
	}

private:
	std::map<const std::string, const U32> mEnumMap;
	std::vector<std::string> mEnumArray;
};

#endif // LL_LLENUM_H
