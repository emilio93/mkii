#ifndef MKII_PERIPHERAL_LCDSCREEN_H
#define MKII_PERIPHERAL_LCDSCREEN_H

#include <ti/grlib/grlib.h>
#include "driverlib.h"

#include "peripheral/GPIO.hpp"
#include "peripheral/gpio/OutputGPIO.hpp"
#include "peripheral/lcdScreen/Spi.hpp"

namespace peripheral {

namespace lcdScreen {
// LCD Screen Dimensions
const uint8_t VERTICAL_MAX = 128;
const uint8_t HORIZONTAL_MAX = 128;

const uint8_t ORIENTATION_UP = 0;
const uint8_t ORIENTATION_LEFT = 1;
const uint8_t ORIENTATION_DOWN = 2;
const uint8_t ORIENTATION_RIGHT = 3;

// ST7735 LCD controller Command Set
const uint8_t CM_NOP = 0x00;
const uint8_t CM_SWRESET = 0x01;
const uint8_t CM_RDDID = 0x04;
const uint8_t CM_RDDST = 0x09;
const uint8_t CM_SLPIN = 0x10;
const uint8_t CM_SLPOUT = 0x11;
const uint8_t CM_PTLON = 0x12;
const uint8_t CM_NORON = 0x13;
const uint8_t CM_INVOFF = 0x20;
const uint8_t CM_INVON = 0x21;
const uint8_t CM_GAMSET = 0x26;
const uint8_t CM_DISPOFF = 0x28;
const uint8_t CM_DISPON = 0x29;
const uint8_t CM_CASET = 0x2A;
const uint8_t CM_RASET = 0x2B;
const uint8_t CM_RAMWR = 0x2C;
const uint8_t CM_RGBSET = 0x2d;
const uint8_t CM_RAMRD = 0x2E;
const uint8_t CM_PTLAR = 0x30;
const uint8_t CM_MADCTL = 0x36;
const uint8_t CM_COLMOD = 0x3A;
const uint8_t CM_SETPWCTR = 0xB1;
const uint8_t CM_SETDISPL = 0xB2;
const uint8_t CM_FRMCTR3 = 0xB3;
const uint8_t CM_SETCYC = 0xB4;
const uint8_t CM_SETBGP = 0xb5;
const uint8_t CM_SETVCOM = 0xB6;
const uint8_t CM_SETSTBA = 0xC0;
const uint8_t CM_SETID = 0xC3;
const uint8_t CM_GETHID = 0xd0;
const uint8_t CM_SETGAMMA = 0xE0;
const uint8_t CM_MADCTL_MY = 0x80;
const uint8_t CM_MADCTL_MX = 0x40;
const uint8_t CM_MADCTL_MV = 0x20;
const uint8_t CM_MADCTL_ML = 0x10;
const uint8_t CM_MADCTL_BGR = 0x08;
const uint8_t CM_MADCTL_MH = 0x04;

}  // namespace lcdScreen

class LcdScreen {
 public:
	LcdScreen(peripheral::lcdScreen::Spi* i_pSpi);

	void Init(void);

	static void SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

	static void SetOrientation(uint8_t orientation);

	static peripheral::lcdScreen::Spi* GetSpi(void);

	static void SetSpi(peripheral::lcdScreen::Spi* i_pSpi);

	static uint8_t GetOrientation(void);
	static void SetOruentation(uint8_t);

	uint16_t GetScreenWidth(void);
	void SetScreenWidth(uint16_t i_u16ScreenWidth);

	uint16_t GetScreenHeigth(void);
	void SetScreenHeigth(uint16_t i_u16ScreenHeigth);

	uint8_t GetPenSolid(void);
	void SetPenSolid(uint8_t i_u8PenSolid);

	uint8_t GetFontSolid(void);
	void SetFontSolid(uint8_t i_u8FontSolid);

	uint8_t GetFlagRead(void);
	void SetFlagRead(uint8_t i_u8FlagRead);

	uint16_t GetTouchTrim(void);
	void SetTouchTrim(uint16_t i_u16TouchTrim);

 private:
	static peripheral::lcdScreen::Spi* m_pSpi;

	uint16_t m_u16ScreenWidth;
	uint16_t m_u16ScreenHeigth;
	uint8_t m_u8PenSolid;
	uint8_t m_u8FontSolid;
	uint8_t m_u8FlagRead;
	uint16_t m_u16TouchTrim;

	static uint8_t m_u8Orientation;

	static void PixelDraw(const Graphics_Display* pDisplay, int16_t lX,
	                      int16_t lY, uint16_t ulValue);
	static void PixelDrawMultiple(const Graphics_Display* pDisplay, int16_t lX,
	                              int16_t lY, int16_t lX0, int16_t lCount,
	                              int16_t lBPP, const uint8_t* pucData,
	                              const uint32_t* pucPalette);
	static void LineDrawH(const Graphics_Display* pDisplay, int16_t lX1,
	                      int16_t lX2, int16_t lY, uint16_t ulValue);
	static void LineDrawV(const Graphics_Display* pDisplay, int16_t lX,
	                      int16_t lY1, int16_t lY2, uint16_t ulValue);
	static void RectFill(const Graphics_Display* pDisplay,
	                     const Graphics_Rectangle* pRect, uint16_t ulValue);
	static uint32_t ColorTranslate(const Graphics_Display* pDisplay,
	                               uint32_t ulValue);
	static void Flush(const Graphics_Display* pDisplay);
	static void ClearScreen(const Graphics_Display* pDisplay, uint16_t ulValue);

	Graphics_Display m_stCrystalfontz128x128 = {
	    sizeof(Graphics_Display),
	    0,
	    peripheral::lcdScreen::VERTICAL_MAX,
	    peripheral::lcdScreen::HORIZONTAL_MAX,
	};

	const Graphics_Display_Functions m_stCrystalfontz128x128_funcs = {
	    peripheral::LcdScreen::PixelDraw,
	    peripheral::LcdScreen::PixelDrawMultiple,
	    peripheral::LcdScreen::LineDrawH,
	    peripheral::LcdScreen::LineDrawV,
	    peripheral::LcdScreen::RectFill,
	    peripheral::LcdScreen::ColorTranslate,
	    peripheral::LcdScreen::Flush,
	    peripheral::LcdScreen::ClearScreen};
};

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_LCDSCREEN_H */
