#pragma once
#define ENABLE_JOYSTICK_INPUT 0
#define ADC_INTERFACE_VERIFIED 0
#define ENABLE_TFT 0
#define TFT_CS -1
#define TFT_DC -1
#define TFT_RST -1
#define TFT_MODEL_VERIFIED 0
#define TFT_RESET_WIRING_VERIFIED 0
#if ENABLE_JOYSTICK_INPUT && !ADC_INTERFACE_VERIFIED
#error "Verify actual board A0 input limits and joystick voltage before enabling"
#endif
#if ENABLE_TFT && (TFT_CS < 0 || TFT_DC < 0 || !TFT_MODEL_VERIFIED || !TFT_RESET_WIRING_VERIFIED)
#error "Verify ST7735 black-tab 128x160, actual pins and reset wiring before enabling"
#endif
#if ENABLE_TFT && (TFT_CS == TFT_DC || (TFT_RST >= 0 && (TFT_RST == TFT_CS || TFT_RST == TFT_DC)))
#error "TFT control pins must be distinct"
#endif
