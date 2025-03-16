static constexpr unsigned char beep_WIDTH = 128;
static constexpr unsigned char beep_PAGE = 8;
static constexpr unsigned char beep_data[] =
{
0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAE, 0xBC, 0xB9, 0xB2, 0xE4, 0xC8, 0xD0, 0x91, 0xA0, 0x20, 0x41, 0x42, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0xA0, 0x90, 0xC8, 0xE8, 0xE4, 0xB2, 0xBA, 0xB9, 0xAC, 0xAE, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAB, 0xAE, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xA8, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xBF, 0xBC, 0xB8, 0xB0, 0xB0, 0xBF, 0xB3, 0xE1, 0xC0, 0xC0, 0x8C, 0x8E, 0x9E, 0x9C, 0x80, 0xC0, 0xE1, 0xFF, 0xBF, 0xBF, 0xAB, 0xAF, 0xAF, 0xAF, 0xAF, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF1, 0xC6, 0x98, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00, 0x00, 0x80, 0x60, 0x10, 0xCC, 0xE3, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x07, 0xC0, 0xF0, 0xF8, 0xEC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8B, 0xFF, 0x17, 0xFE, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xBF, 0xF9, 0xF0, 0xF0, 0xC0, 0x80, 0x06, 0x0C, 0xF8, 0xFC, 0x9F, 0x0F, 0x03, 0x00, 0x00, 0x60, 0xC0, 0x82, 0xC7, 0xEE, 0x7C, 0x1C, 0x06, 0x01, 0x01, 0x41, 0x7B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x07, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x09, 0x03, 0x7F, 0x9F, 0x3F, 0x7F, 0x3F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x70, 0x0F, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x3F, 0x0F, 0x03, 0x00, 0x80, 0xE0, 0xB0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xC7, 0x83, 0x00, 0x10, 0x38, 0x78, 0x31, 0x03, 0x07, 0xE3, 0xE0, 0xF0, 0x38, 0x0F, 0x03, 0x00, 0x00, 0x21, 0x71, 0xE3, 0xC2, 0xC3, 0xE7, 0x3C, 0x0F, 0x0F, 0x1F, 0x1F, 0x3E, 0x3F, 0x3F, 0x7E, 0xDF, 0xF0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFE, 0xE0, 0x00, 0x01, 0x00, 0xC0, 0x7F, 0xFE, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xF8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0xF1, 0xE4, 0xEF, 0xCF, 0xDF, 0xD8, 0xC1, 0xC3, 0xDF, 0xFF, 0x1C, 0x00, 0x00, 0x00, 0x03, 0x3C, 0xC1, 0x1F, 0xFF, 0xEF, 0xFF, 0xEF, 0xE7, 0xE7, 0xE3, 0xF1, 0xF1, 0xF0, 0x74, 0x10, 0x02, 0x01, 0x41, 0x03, 0x8F, 0xCF, 0xCF, 0xEF, 0xFF, 0xFF, 0xFF, 0x7E, 0x1E, 0x06, 0x82, 0xC2, 0x86, 0x0E, 0x1E, 0x3E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x2E, 0xFE, 0xFE, 0x5E, 0xFE, 0xFE, 0xFE, 0xFE, 0x2E, 0xFE, 0xFE, 0xFE, 0xFA, 0x32, 0x02, 0x0E, 0x8E, 0xC6, 0x06, 0x0E, 0x3E, 0x7E, 0x0E, 0x06, 0x02, 0x12, 0x3A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFD, 0xFF, 0xFF, 0x7F, 0xFF, 0xDF, 0x77, 0xDF, 0xF7, 0xDF, 0xF7, 0x3F, 0x0F, 0x07, 0x76, 0x80, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0, 0x81, 0x07, 0x9D, 0x9F, 0x9A, 0x99, 0x9B, 0x9E, 0x99, 0x9C, 0x99, 0x9F, 0x9E, 0x99, 0x9F, 0x98, 0x9A, 0x9B, 0x9D, 0x9F, 0x9D, 0x9E, 0x99, 0x9F, 0x98, 0x9A, 0x9B, 0x9D, 0x9F, 0x9D, 0x9E, 0x9C, 0x9A, 0x99, 0x9F, 0x9D, 0x97, 0x9D, 0x97, 0x9D, 0x97, 0x9D, 0x97, 0x9D, 0x97, 0x9D, 0xFF, 0xFD, 0xFF, 0xF6, 0xFF, 0xFC, 0x01, 0x7E, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFA, 0xD7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF9, 0xFD, 0xFD, 0xFD, 0xFC, 0xC1, 0x8C, 0x37, 0xFF, 0xFD, 0xFF, 0xF6, 0xFF, 0xFD, 0xFF, 0xF6, 0xFF, 0xFD, 0xFF, 0xF6, 0xFF, 0xFD, 0xFF, 0xF6, 0xFF, 0xFF, 0xF6, 0xF8, 0xE0, 0x81, 0x07, 0x1F, 0x7F, 0xFF, 0xE9, 0xE7, 0xEF, 0x79, 0xE5, 0xE5, 0x6F, 0xFD, 0x61, 0xE9, 0xEF, 0x7F, 0xE9, 0x67, 0x6F, 0x7F, 0xFF, 0xFF, 0xF9, 0xE5, 0x6D, 0xE3, 0x7F, 0x71, 0x6B, 0xEF, 0xEF, 0xFF, 0xFF, 0x7F, 0xFF, 0x69, 0xE7, 0xEF, 0xF9, 0xE7, 0xF1, 0xE7, 0xFF, 0xF9, 0xE5, 0xE5, 0xEF, 0xFF, 0xFF, 0xD5, 0x7E, 0xD5, 0xFF, 0xF8, 0x03, 0xFC, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x18, 0xF8, 0xF8, 0xBC, 0x5C, 0xBC, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xF8, 0xF0, 0xC0, 0x81, 0x0A, 0x85, 0x70, 0x0F, 0xE0, 0x7E, 0xD5, 0xFF, 0xD5, 0x7E, 0xD5, 0xFF, 0xD5, 0x7E, 0xD5, 0xFF, 0xD5, 0x7F, 0xD6, 0xF8, 0xE0, 0x81, 0x06, 0x1F, 0x7E, 0xFE, 0xE6, 0x97, 0x97, 0xBE, 0xE6, 0x9F, 0xBF, 0xDE, 0xB6, 0x8E, 0xFF, 0xE7, 0x96, 0x96, 0xBF, 0xE6, 0x8E, 0xA6, 0xDF, 0xFF, 0xE7, 0x96, 0xB6, 0xAF, 0xFF, 0xE6, 0x96, 0x97, 0xBE, 0xE6, 0x9E, 0xB7, 0xCE, 0xFE, 0xEE, 0xD7, 0xB6, 0x9F, 0xFE, 0xF7, 0x96, 0xCF, 0x9E, 0xFF, 0xFE, 0xFE, 0xF8, 0xE0, 0x82, 0x53, 0xE4, 0x48, 0x10, 0xE0, 0x00, 0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x08, 0x13, 0x24, 0x47, 0x84, 0x06, 0x0E, 0xFF, 0x42, 0x41, 0x3C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x84, 0x42, 0xA1, 0x00, 0x00, 0xFC, 0x03, 0xE8, 0x55, 0xAA, 0x55, 0xEA, 0x55, 0xAA, 0x55, 0xEA, 0x55, 0xAA, 0x7F, 0x80, 0x20, 0x24, 0x2E, 0xA4, 0xA0, 0xA4, 0x20, 0xA4, 0xA0, 0x24, 0xA0, 0x24, 0xA0, 0x24, 0xA0, 0x24, 0xA0, 0x24, 0xA0, 0x20, 0xA0, 0x20, 0xA0, 0x20, 0xA0, 0xA0, 0x20, 0xA0, 0x20, 0xA0, 0x20, 0xA0, 0x20, 0xA0, 0x20, 0xA0, 0x20, 0xA4, 0xAA, 0xAE, 0xAA, 0x2E, 0xAA, 0xAE, 0xAA, 0xAE, 0xAA, 0xAE, 0xAA, 0xAE, 0xA4, 0xA0, 0x80, 0x00, 0x20, 0x80, 0x00, };