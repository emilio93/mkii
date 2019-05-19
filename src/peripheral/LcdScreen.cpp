#include "peripheral/LcdScreen.hpp"

Graphics_Display peripheral::LcdScreen::m_stCrystalfontz128x128 = {
    sizeof(Graphics_Display), 0, peripheral::lcdScreen::VERTICAL_MAX,
    peripheral::lcdScreen::HORIZONTAL_MAX};

const Graphics_Display_Functions
    peripheral::LcdScreen::m_stCrystalfontz128x128_funcs = {
        peripheral::LcdScreen::PixelDraw,
        peripheral::LcdScreen::PixelDrawMultiple,
        peripheral::LcdScreen::LineDrawH,
        peripheral::LcdScreen::LineDrawV,
        peripheral::LcdScreen::RectFill,
        peripheral::LcdScreen::ColorTranslate,
        peripheral::LcdScreen::Flush,
        peripheral::LcdScreen::ClearScreen};

peripheral::LcdScreen::LcdScreen(peripheral::lcdScreen::Spi* i_pSpi) {
	this->SetSpi(i_pSpi);
}

peripheral::lcdScreen::Spi* peripheral::LcdScreen::m_pSpi = NULL;
uint8_t peripheral::LcdScreen::m_u8Orientation = 0;

void peripheral::LcdScreen::Init(void) {
	peripheral::LcdScreen::GetSpi()->PortInit();
	peripheral::LcdScreen::GetSpi()->SpiInit();

	peripheral::LcdScreen::GetSpi()->GetRstGPIO()->SetOutput(false);
	delay(50);
	peripheral::LcdScreen::GetSpi()->GetRstGPIO()->SetOutput(true);
	delay(120);

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_SLPOUT);
	delay(200);

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_GAMSET);
	peripheral::LcdScreen::GetSpi()->WriteData(0x04);

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_SETPWCTR);
	peripheral::LcdScreen::GetSpi()->WriteData(0x0A);
	peripheral::LcdScreen::GetSpi()->WriteData(0x14);

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_SETSTBA);
	peripheral::LcdScreen::GetSpi()->WriteData(0x0A);
	peripheral::LcdScreen::GetSpi()->WriteData(0x00);

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_COLMOD);
	peripheral::LcdScreen::GetSpi()->WriteData(0x05);
	delay(10);

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_MADCTL);
	peripheral::LcdScreen::GetSpi()->WriteData(
	    peripheral::lcdScreen::CM_MADCTL_BGR);

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_NORON);

	this->SetScreenWidth(peripheral::lcdScreen::VERTICAL_MAX);
	this->SetScreenHeigth(peripheral::lcdScreen::HORIZONTAL_MAX);
	this->SetPenSolid(0);
	this->SetFontSolid(1);
	this->SetFlagRead(0);
	this->SetTouchTrim(0);

	peripheral::LcdScreen::SetDrawFrame(0, 0, 127, 127);
	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_RAMWR);
	int i;
	for (i = 0; i < 16384; i++) {
		peripheral::LcdScreen::GetSpi()->WriteData(0xFF);
		peripheral::LcdScreen::GetSpi()->WriteData(0xFF);
	}

	delay(10);
	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_DISPON);
}

void peripheral::LcdScreen::SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1,
                                         uint16_t y1) {
	switch (peripheral::LcdScreen::GetOrientation()) {
		case 0:
			x0 += 2;
			y0 += 3;
			x1 += 2;
			y1 += 3;
			break;
		case 1:
			x0 += 3;
			y0 += 2;
			x1 += 3;
			y1 += 2;
			break;
		case 2:
			x0 += 2;
			y0 += 1;
			x1 += 2;
			y1 += 1;
			break;
		case 3:
			x0 += 1;
			y0 += 2;
			x1 += 1;
			y1 += 2;
			break;
		default:
			break;
	}

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_CASET);
	peripheral::LcdScreen::GetSpi()->WriteData((uint8_t)(x0 >> 8));
	peripheral::LcdScreen::GetSpi()->WriteData((uint8_t)(x0));
	peripheral::LcdScreen::GetSpi()->WriteData((uint8_t)(x1 >> 8));
	peripheral::LcdScreen::GetSpi()->WriteData((uint8_t)(x1));

	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_RASET);
	peripheral::LcdScreen::GetSpi()->WriteData((uint8_t)(y0 >> 8));
	peripheral::LcdScreen::GetSpi()->WriteData((uint8_t)(y0));
	peripheral::LcdScreen::GetSpi()->WriteData((uint8_t)(y1 >> 8));
	peripheral::LcdScreen::GetSpi()->WriteData((uint8_t)(y1));
}

void peripheral::LcdScreen::SetOrientation(uint8_t i_u8orientation) {
	peripheral::LcdScreen::m_u8Orientation = i_u8orientation;
	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_MADCTL);
	switch (peripheral::LcdScreen::GetOrientation()) {
		case peripheral::lcdScreen::ORIENTATION_UP:
			peripheral::LcdScreen::GetSpi()->WriteData(
			    peripheral::lcdScreen::CM_MADCTL_MX |
			    peripheral::lcdScreen::CM_MADCTL_MY |
			    peripheral::lcdScreen::CM_MADCTL_BGR);
			break;
		case peripheral::lcdScreen::ORIENTATION_LEFT:
			peripheral::LcdScreen::GetSpi()->WriteData(
			    peripheral::lcdScreen::CM_MADCTL_MY |
			    peripheral::lcdScreen::CM_MADCTL_MV |
			    peripheral::lcdScreen::CM_MADCTL_BGR);
			break;
		case peripheral::lcdScreen::ORIENTATION_DOWN:
			peripheral::LcdScreen::GetSpi()->WriteData(
			    peripheral::lcdScreen::CM_MADCTL_BGR);
			break;
		case peripheral::lcdScreen::ORIENTATION_RIGHT:
			peripheral::LcdScreen::GetSpi()->WriteData(
			    peripheral::lcdScreen::CM_MADCTL_MX |
			    peripheral::lcdScreen::CM_MADCTL_MV |
			    peripheral::lcdScreen::CM_MADCTL_BGR);
			break;
	}
}

peripheral::lcdScreen::Spi* peripheral::LcdScreen::GetSpi(void) {
	return peripheral::LcdScreen::m_pSpi;
}

void peripheral::LcdScreen::SetSpi(peripheral::lcdScreen::Spi* i_pSpi) {
	peripheral::LcdScreen::m_pSpi = i_pSpi;
}

uint8_t peripheral::LcdScreen::GetOrientation(void) {
	return peripheral::LcdScreen::m_u8Orientation;
}

uint16_t peripheral::LcdScreen::GetScreenWidth(void) {
	return this->m_u16ScreenWidth;
}
void peripheral::LcdScreen::SetScreenWidth(uint16_t i_u16ScreenWidth) {
	this->m_u16ScreenWidth = i_u16ScreenWidth;
}

uint16_t peripheral::LcdScreen::GetScreenHeigth(void) {
	return this->m_u16ScreenHeigth;
}
void peripheral::LcdScreen::SetScreenHeigth(uint16_t i_u16ScreenHeigth) {
	this->m_u16ScreenHeigth = i_u16ScreenHeigth;
}

uint8_t peripheral::LcdScreen::GetPenSolid(void) { return this->m_u8PenSolid; }
void peripheral::LcdScreen::SetPenSolid(uint8_t i_u8PenSolid) {
	this->m_u8PenSolid = i_u8PenSolid;
}

uint8_t peripheral::LcdScreen::GetFontSolid(void) {
	return this->m_u8FontSolid;
}
void peripheral::LcdScreen::SetFontSolid(uint8_t i_u8FontSolid) {
	this->m_u8FontSolid = i_u8FontSolid;
}

uint8_t peripheral::LcdScreen::GetFlagRead(void) { return this->m_u8FlagRead; }
void peripheral::LcdScreen::SetFlagRead(uint8_t i_u8FlagRead) {
	this->m_u8FlagRead = i_u8FlagRead;
}

uint16_t peripheral::LcdScreen::GetTouchTrim(void) {
	return this->m_u16TouchTrim;
}
void peripheral::LcdScreen::SetTouchTrim(uint16_t i_u16TouchTrim) {
	this->m_u16TouchTrim = i_u16TouchTrim;
}

Graphics_Display peripheral::LcdScreen::GetCrystalfontz128x128() {
	return peripheral::LcdScreen::m_stCrystalfontz128x128;
}

Graphics_Display_Functions
peripheral::LcdScreen::GetCrystalfontz128x128_funcs() {
	return peripheral::LcdScreen::m_stCrystalfontz128x128_funcs;
}

void peripheral::LcdScreen::PixelDraw(const Graphics_Display* pDisplay,
                                      int16_t lX, int16_t lY,
                                      uint16_t ulValue) {
	peripheral::LcdScreen::SetDrawFrame(lX, lY, lX, lY);

	//
	// Write the pixel value.
	//
	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_RAMWR);
	peripheral::LcdScreen::GetSpi()->WriteData(ulValue >> 8);
	peripheral::LcdScreen::GetSpi()->WriteData(ulValue);
}

void peripheral::LcdScreen::PixelDrawMultiple(const Graphics_Display* pDisplay,
                                              int16_t lX, int16_t lY,
                                              int16_t lX0, int16_t lCount,
                                              int16_t lBPP,
                                              const uint8_t* pucData,
                                              const uint32_t* pucPalette) {
	uint16_t Data;

	//
	// Set the cursor increment to left to right, followed by top to bottom.
	//
	peripheral::LcdScreen::SetDrawFrame(lX, lY, lX + lCount, 127);
	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_RAMWR);

	//
	// Determine how to interpret the pixel data based on the number of bits
	// per pixel.
	//
	switch (lBPP) {
		// The pixel data is in 1 bit per pixel format
		case 1: {
			// Loop while there are more pixels to draw
			while (lCount > 0) {
				// Get the next byte of image data
				Data = *pucData++;

				// Loop through the pixels in this byte of image data
				for (; (lX0 < 8) && lCount; lX0++, lCount--) {
					// Draw this pixel in the appropriate color
					peripheral::LcdScreen::GetSpi()->WriteData(
					    (((uint32_t*)pucPalette)[(Data >> (7 - lX0)) & 1]) >> 8);
					peripheral::LcdScreen::GetSpi()->WriteData(
					    ((uint32_t*)pucPalette)[(Data >> (7 - lX0)) & 1]);
				}

				// Start at the beginning of the next byte of image data
				lX0 = 0;
			}
			// The image data has been drawn

			break;
		}

		// The pixel data is in 4 bit per pixel format
		case 4: {
			// Loop while there are more pixels to draw.  "Duff's device" is
			// used to jump into the middle of the loop if the first nibble of
			// the pixel data should not be used.  Duff's device makes use of
			// the fact that a case statement is legal anywhere within a
			// sub-block of a switch statement.  See
			// http://en.wikipedia.org/wiki/Duff's_device for detailed
			// information about Duff's device.
			switch (lX0 & 1) {
				case 0:

					while (lCount) {
						// Get the upper nibble of the next byte of pixel data
						// and extract the corresponding entry from the palette
						Data = (*pucData >> 4);
						Data = (*(uint16_t*)(pucPalette + Data));
						// Write to LCD screen
						peripheral::LcdScreen::GetSpi()->WriteData(Data >> 8);
						peripheral::LcdScreen::GetSpi()->WriteData(Data);

						// Decrement the count of pixels to draw
						lCount--;

						// See if there is another pixel to draw
						if (lCount) {
							case 1:
								// Get the lower nibble of the next byte of pixel
								// data and extract the corresponding entry from
								// the palette
								Data = (*pucData++ & 15);
								Data = (*(uint16_t*)(pucPalette + Data));
								// Write to LCD screen
								peripheral::LcdScreen::GetSpi()->WriteData(Data >> 8);
								peripheral::LcdScreen::GetSpi()->WriteData(Data);

								// Decrement the count of pixels to draw
								lCount--;
						}
					}
			}
			// The image data has been drawn.

			break;
		}

		// The pixel data is in 8 bit per pixel format
		case 8: {
			// Loop while there are more pixels to draw
			while (lCount--) {
				// Get the next byte of pixel data and extract the
				// corresponding entry from the palette
				Data = *pucData++;
				Data = (*(uint16_t*)(pucPalette + Data));
				// Write to LCD screen
				peripheral::LcdScreen::GetSpi()->WriteData(Data >> 8);
				peripheral::LcdScreen::GetSpi()->WriteData(Data);
			}
			// The image data has been drawn
			break;
		}

		//
		// We are being passed data in the display's native format.  Merely
		// write it directly to the display.  This is a special case which is
		// not used by the graphics library but which is helpful to
		// applications which may want to handle, for example, JPEG images.
		//
		case 16: {
			uint16_t usData;

			// Loop while there are more pixels to draw.

			while (lCount--) {
				// Get the next byte of pixel data and extract the
				// corresponding entry from the palette
				usData = *((uint16_t*)pucData);
				pucData += 2;

				// Translate this palette entry and write it to the screen
				peripheral::LcdScreen::GetSpi()->WriteData(usData >> 8);
				peripheral::LcdScreen::GetSpi()->WriteData(usData);
			}
		}
	}
}

void peripheral::LcdScreen::LineDrawH(const Graphics_Display* pDisplay,
                                      int16_t lX1, int16_t lX2, int16_t lY,
                                      uint16_t ulValue) {
	peripheral::LcdScreen::SetDrawFrame(lX1, lY, lX2, lY);

	//
	// Write the pixel value.
	//
	int16_t i;
	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_RAMWR);
	for (i = lX1; i <= lX2; i++) {
		peripheral::LcdScreen::GetSpi()->WriteData(ulValue >> 8);
		peripheral::LcdScreen::GetSpi()->WriteData(ulValue);
	}
}

void peripheral::LcdScreen::LineDrawV(const Graphics_Display* pDisplay,
                                      int16_t lX, int16_t lY1, int16_t lY2,
                                      uint16_t ulValue) {
	peripheral::LcdScreen::SetDrawFrame(lX, lY1, lX, lY2);

	//
	// Write the pixel value.
	//
	int16_t i;
	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_RAMWR);
	for (i = lY1; i <= lY2; i++) {
		peripheral::LcdScreen::GetSpi()->WriteData(ulValue >> 8);
		peripheral::LcdScreen::GetSpi()->WriteData(ulValue);
	}
}

void peripheral::LcdScreen::RectFill(const Graphics_Display* pDisplay,
                                     const Graphics_Rectangle* pRect,
                                     uint16_t ulValue) {
	int16_t x0 = pRect->sXMin;
	int16_t x1 = pRect->sXMax;
	int16_t y0 = pRect->sYMin;
	int16_t y1 = pRect->sYMax;

	peripheral::LcdScreen::SetDrawFrame(x0, y0, x1, y1);

	//
	// Write the pixel value.
	//
	int16_t i;
	int16_t pixels = (x1 - x0 + 1) * (y1 - y0 + 1);
	peripheral::LcdScreen::GetSpi()->WriteCommand(
	    peripheral::lcdScreen::CM_RAMWR);
	for (i = 0; i <= pixels; i++) {
		peripheral::LcdScreen::GetSpi()->WriteData(ulValue >> 8);
		peripheral::LcdScreen::GetSpi()->WriteData(ulValue);
	}
}

uint32_t peripheral::LcdScreen::ColorTranslate(const Graphics_Display* pDisplay,
                                               uint32_t ulValue) {
	//
	// Translate from a 24-bit RGB color to a 5-6-5 RGB color.
	//
	return (((((ulValue)&0x00f80000) >> 8) | (((ulValue)&0x0000fc00) >> 5) |
	         (((ulValue)&0x000000f8) >> 3)));
}

void peripheral::LcdScreen::Flush(const Graphics_Display* pDisplay) {
	//
	// There is nothing to be done.
	//
}

void peripheral::LcdScreen::ClearScreen(const Graphics_Display* pDisplay,
                                        uint16_t ulValue) {
	Graphics_Rectangle rect = {0, 0, peripheral::lcdScreen::VERTICAL_MAX - 1,
	                           peripheral::lcdScreen::VERTICAL_MAX - 1};
	peripheral::LcdScreen::RectFill(pDisplay, &rect, ulValue);
}
