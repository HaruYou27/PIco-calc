static constexpr unsigned char discover_WIDTH = 128;
static constexpr unsigned char discover_PAGE = 8;
static constexpr unsigned char discover_data[] =
{
0xFA, 0x8B, 0xAA, 0xD9, 0xFA, 0x8B, 0xFA, 0xE9, 0x8A, 0xBB, 0xFA, 0x89, 0xAA, 0xFB, 0x8A, 0xA9, 0x8A, 0xFB, 0x9A, 0xE9, 0x9A, 0xFB, 0x8A, 0x89, 0xAA, 0xFB, 0x8A, 0x99, 0xAA, 0xFB, 0x8A, 0xA9, 0xDA, 0xFB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE9, 0xEA, 0xEB, 0xEA, 0xE8, 0xE8, 0xE8, 0xE8, 0xE1, 0xE1, 0xE2, 0xC4, 0xC8, 0x88, 0x90, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x90, 0x88, 0xC8, 0xC4, 0xE2, 0xF2, 0xF1, 0xF8, 0xF8, 0xAA, 0x89, 0xEA, 0xFB, 0x8A, 0xA9, 0x8A, 0xFB, 0xAA, 0xF9, 0xAA, 0x8B, 0xEA, 0xF9, 0x8A, 0xAB, 0x8A, 0xF9, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD0, 0xA8, 0x50, 0xA1, 0xC3, 0x84, 0x08, 0x10, 0x20, 0x40, 0x42, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x82, 0x40, 0x20, 0x10, 0x88, 0x46, 0xA1, 0xD0, 0xA8, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xAA, 0x54, 0xAA, 0xD1, 0xA8, 0x42, 0xA8, 0x00, 0xAA, 0x40, 0xA8, 0x02, 0xA8, 0x40, 0xAA, 0x00, 0xA8, 0x42, 0xA8, 0x00, 0xAA, 0x40, 0xA8, 0x02, 0xA8, 0x40, 0xAA, 0x00, 0xA8, 0x42, 0xA8, 0x00, 0xAA, 0x40, 0xA8, 0x02, 0xA8, 0x40, 0xAA, 0x00, 0xA8, 0x42, 0xA8, 0x00, 0xAA, 0x40, 0xA8, 0x02, 0xA8, 0x40, 0xAA, 0x00, 0xA8, 0x42, 0xA8, 0x00, 0xAA, 0x40, 0xA8, 0x02, 0xA8, 0x40, 0xAA, 0x00, 0xA8, 0x40, 0x00, 0x03, 0x0E, 0x70, 0x80, 0x2A, 0x00, 0xAA, 0x00, 0x00, 0x90, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02, 0x05, 0x0B, 0x17, 0x17, 0x27, 0x27, 0x26, 0x26, 0x26, 0x16, 0x0E, 0x03, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1C, 0x03, 0x00, 0x00, 0x00, 0xC0, 0x3C, 0x03, 0x80, 0x00, 0xA8, 0x42, 0xA8, 0x00, 0xAA, 0x40, 0xA8, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0D, 0x11, 0x02, 0x01, 0x13, 0x0C, 0x00, 0x03, 0x0D, 0x15, 0x11, 0x10, 0x03, 0x0D, 0x11, 0x00, 0x03, 0x0D, 0x11, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x39, 0xC2, 0x07, 0x00, 0xA0, 0x00, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x97, 0x6E, 0x1C, 0x0C, 0x09, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x09, 0x13, 0x27, 0xC3, 0x81, 0x01, 0x01, 0x43, 0x7F, 0x7E, 0x7F, 0x6D, 0x1B, 0x7F, 0xFF, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x3F, 0x00, 0x01, 0x01, 0x00, 0x80, 0x40, 0x30, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x1A, 0x22, 0x04, 0x02, 0x26, 0x18, 0x00, 0x06, 0x18, 0x28, 0x0E, 0x18, 0x20, 0x06, 0x1C, 0x24, 0x26, 0x18, 0x00, 0x26, 0x38, 0x20, 0x00, 0x00, 0x00, 0x06, 0x1A, 0x22, 0x24, 0x18, 0x00, 0x06, 0x18, 0x20, 0x06, 0x1A, 0x22, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0xE0, 0x1C, 0x03, 0x00, 0x03, 0x04, 0xC2, 0x31, 0x08, 0x04, 0x00, 0x9F, 0x2B, 0x07, 0x07, 0x07, 0x8F, 0xFF, 0xF9, 0xF4, 0xEA, 0x97, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7B, 0xF7, 0xEB, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x54, 0x18, 0x10, 0x60, 0x0C, 0x34, 0x44, 0x44, 0x38, 0x00, 0x0C, 0x34, 0x44, 0x0C, 0x70, 0x00, 0x00, 0x00, 0x0C, 0x34, 0x54, 0x44, 0x40, 0x0C, 0x50, 0x20, 0x3C, 0x40, 0x0C, 0x30, 0x50, 0x50, 0x20, 0x0C, 0x34, 0x54, 0x44, 0x40, 0x18, 0x24, 0x44, 0x44, 0x40, 0x00, 0x4C, 0x70, 0x40, 0x00, 0x00, 0x44, 0x50, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x00, 0xFF, 0x80, 0x40, 0x40, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0B, 0xF7, 0xFF, 0xFF, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xCF, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x03, 0x00, 0xF0, 0x0C, 0x03, 0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xBE, 0x9F, 0xAF, 0xA7, 0xA7, 0xA7, 0xC7, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xF8, 0xF9, 0xF2, 0xC5, 0x8A, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x7E, 0x01, 0x00, 0x83, 0x7C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0xF8, 0x06, 0x01, 0x00, 0x1F, 0x04, 0x02, 0x01, 0x00, 0x00, 0xC0, 0x30, 0x0E, 0x01, 0x7E, 0xA1, 0xD0, 0xD1, 0xD2, 0xDC, 0xC1, 0xDE, 0x80, 0x80, 0xA0, 0x00, 0x20, 0x40, 0xA0, 0x40, 0x80, 0x40, 0x80, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x31, 0x0E, 0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x11, 0x23, 0xC7, 0x0F, 0x87, 0x47, 0x87, 0x1F, };