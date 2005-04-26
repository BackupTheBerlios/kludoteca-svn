/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkimage.h RTK Image object
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/*>>>>>COPYRIGHT*/
#ifndef RTKIMAGE_H
#define RTKIMAGE_H


#include <qimage.h>

#include "rtknamespace.h"

namespace RTK
{

/**
  \brief This class represents an Image or other multimedia file
 
  */
class Image
{

/*<<<<<IMAGE_CONSTRUCTOR*/
public:
	Image(String name = String::null, String url = String::null, 
		String mimetype = String::null, String imagestyle = String::null)
	:mName(name), mUrl(url), 
		mMimeType(mimetype), mImageStyle(imagestyle)
/*>>>>>IMAGE_CONSTRUCTOR*/
		, pImage(0)
	{}
	~Image() { if( pImage ) delete pImage; }
	
	const QImage *getImage(const QString &paths, const QString &pwd = QString::null);
	
/*<<<<<IMAGE_GETSET*/
public:
	/** Gets Name of the image in the map of images */
	String getName() const { return mName; };
	/** Sets the Name of the image in the map of images */
	void setName(String name) { mName = name; };
	/** Gets Url of the image */
	String getUrl() const { return mUrl; };
	/** Sets the Url of the image */
	void setUrl(String url) { mUrl = url; };
	/** Gets Mime type of the image */
	String getMimeType() const { return mMimeType; };
	/** Sets the Mime type of the image */
	void setMimeType(String mimetype) { mMimeType = mimetype; };
	/** Gets Style to apply to the background image */
	String getImageStyle() const { return mImageStyle; };
	/** Sets the Style to apply to the background image */
	void setImageStyle(String imagestyle) { mImageStyle = imagestyle; };
protected:
	String mName;
	String mUrl;
	String mMimeType;
	String mImageStyle;
/*>>>>>IMAGE_GETSET*/
private:
	void read(const QString &path, const QString &cwd  = QString::null);
	QImage *pImage;
};

}; // Namespace

#endif
