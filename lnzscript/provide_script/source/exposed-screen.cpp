
///Function:Screen.getColor
///Arguments:int x, int y, bool bRelCds=false
///Returns:[int nR, int nG, int nB]
///Doc:Finds color of screen at coordinates. Returns array of r,g,b values (from 0 to 255), or null upon failure.
///Implementation:c++_au3
{
	CHECK_ARGS
	util_SetAU3PixelRelativeCoords(bRelCds);
	long nColor = AU3_PixelGetColor(x,y);
	if (nColor==-1)
		return eng->nullValue();
	
	QScriptValue arColors = eng->newArray(3);
	arColors.setProperty(0, QScriptValue(eng, (int) GetRValue(nColor)));
	arColors.setProperty(1, QScriptValue(eng, (int) GetGValue(nColor)));
	arColors.setProperty(2, QScriptValue(eng, (int) GetBValue(nColor)));
	return arColors;
}

///Function:Screen.copyScreenshot
///Arguments:bool bFullScreen=false
///Returns:
///Doc:Copy screenshot to the clipboard. Defaults to screenshot of the active window, specify true to take screenshot of full screen.
///Implementation:c++_au3
{
	CHECK_ARGS
	if (bFullScreen) AU3_Send("{PRINTSCREEN}",0);
	else
	{
		//apparently has to be sent a slower way. than //AU3_Send("!{PRINTSCREEN}",0);
		AU3_Send("{ALTDOWN}",0);
		AU3_Sleep(100);
		AU3_Send("{PRINTSCREEN}",0);
		AU3_Sleep(100);
		AU3_Send("{ALTUP}",0);
	}
	return eng->nullValue();
}

///Function:Screen.saveScreenshot
///Arguments:string strImageFilename, bool bFullScreen=false
///Returns:bool bStatus
///Doc:Save screenshot to an image file. Defaults to screenshot of the active window, specify true to take screenshot of full screen. Current implementation overwrites clipboard contents. Image formats: .bmp, .gif, .png, .jpg, .tiff
///Implementation:c++_qt
{
	CHECK_ARGS
	if (bFullScreen)
		return R_WinCommonGdi("screenshot", strImageFilename, "/fullscreen");
	else
		return R_WinCommonGdi("screenshot", strImageFilename);
}


///Function:Screen.convertImage
///Arguments:string strImageFilename, string strNewImageName
///Returns:bool bStatus
///Doc:Convert image file from one format from another. Image formats: .bmp, .gif, .png, .jpg, .tiff
///Implementation:c++_qt
{
	CHECK_ARGS
	return R_WinCommonGdi("convert", strImageFilename, strNewImageName);
}

//~ ///Function:nirdisabled_Screen.convertImages
//~ ///Arguments:string strImagePattern, string strOutputPattern
//~ ///Returns:bool bStatus
//~ ///Doc:Convert image files from one format from another. See example. strImagePattern is pattern like "*.bmp" or "a*.bmp". strOutputpattern is pattern like ".png". Image formats: .bmp, .gif, .png, .jpg, .tiff
//~ ///Example:Screen.convertImages('c:\\myfolder\\*.bmp','.png') //converts all .bmp images in the folder to .png.
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabled_Screen.setDisplayMode
//~ ///Arguments:int nWidth, int nHeight, int nColorBits
//~ ///Returns:bool bStatus
//~ ///Doc:Changes display settings. nColorBits is the number of colors, for example 16-bit color or 24-bit color.
//~ ///Example:Screen.displayMode(800,600,24); //set display to 800x600
//~ ///Implementation:c++_nir-cmd



///Function:Screen.searchPixelColor
///Arguments:int nR,int nG,int nB,int nLeft,int nTop,int nRight,int nBtm,bool bRelCds=0,int nStep=0,int nDiff=0
///Returns:bool bR
///Doc:Search for color on screen. Returns coordinate at which color was found, or false. nStep - number of coordinates to walk with each step, make it larger for speed and less precision. nDiff - 0-255, are similar colors accepted? By default, 0, must be exact match. If given a value of 255, accepts different colors.
///Implementation:c++_au3
{
	CHECK_ARGS
	util_SetAU3PixelRelativeCoords(bRelCds);
	POINT pos;
	AU3_PixelSearch(nLeft, nTop, nRight, nBtm, RGB(nR,nG,nB), nDiff, nStep, &pos);
	if (AU3_error()!=0) return QScriptValue(eng, false);
	QScriptValue ar = eng->newArray(2);
	ar.setProperty(0, QScriptValue(eng, (int) pos.x));
	ar.setProperty(1, QScriptValue(eng, (int) pos.y));
	return ar;
}

