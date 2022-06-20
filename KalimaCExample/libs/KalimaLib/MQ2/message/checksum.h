#ifndef DEF_LIBCRC_CHECKSUM_H
#define DEF_LIBCRC_CHECKSUM_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * #define CRC_POLY_xxxx
 *
 * The constants of the form CRC_POLY_xxxx define the polynomials for some well
 * known CRC calculations.
 */

#define		CRC_POLY_16		0xA001
#define		CRC_POLY_32		0xEDB88320ul
#define		CRC_POLY_64		0xC96C5795D7870F42L
#define		CRC_POLY_CCITT		0x1021
#define		CRC_POLY_DNP		0xA6BC
#define		CRC_POLY_KERMIT		0x8408
#define		CRC_POLY_SICK		0x8005

/*
 * #define CRC_START_xxxx
 *
 * The constants of the form CRC_START_xxxx define the values that are used for
 * initialization of a CRC value for common used calculation methods.
 */

#define		CRC_START_8		0x00
#define		CRC_START_16		0x0000
#define		CRC_START_MODBUS	0xFFFF
#define		CRC_START_XMODEM	0x0000
#define		CRC_START_CCITT_1D0F	0x1D0F
#define		CRC_START_CCITT_FFFF	0xFFFF
#define		CRC_START_KERMIT	0x0000
#define		CRC_START_SICK		0x0000
#define		CRC_START_DNP		0x0000
#define		CRC_START_32		0xFFFFFFFFul
#define		CRC_START_64_ECMA	0x0000000000000000ull
#define		CRC_START_64_WE		0xFFFFFFFFFFFFFFFFull

/*
 * Prototype list of global functions
 */

unsigned char *		checksum_NMEA(      const unsigned char *input_str, unsigned char *result  );
uint8_t			crc_8(              const unsigned char *input_str, size_t num_bytes       );
uint16_t		crc_16(             const unsigned char *input_str, size_t num_bytes       );
uint32_t		crc_32(             const unsigned char *input_str, size_t num_bytes       );
uint64_t		crc_64_ecma(        uint8_t *input_str, size_t num_bytes       );
uint64_t		crc_64_we(          const unsigned char *input_str, size_t num_bytes       );
uint16_t		crc_ccitt_1d0f(     const unsigned char *input_str, size_t num_bytes       );
uint16_t		crc_ccitt_ffff(     const unsigned char *input_str, size_t num_bytes       );
uint16_t		crc_dnp(            const unsigned char *input_str, size_t num_bytes       );
uint16_t		crc_kermit(         const unsigned char *input_str, size_t num_bytes       );
uint16_t		crc_modbus(         const unsigned char *input_str, size_t num_bytes       );
uint16_t		crc_sick(           const unsigned char *input_str, size_t num_bytes       );
uint16_t		crc_xmodem(         const unsigned char *input_str, size_t num_bytes       );
uint8_t			update_crc_8(       uint8_t  crc, unsigned char c                          );
uint16_t		update_crc_16(      uint16_t crc, unsigned char c                          );
uint32_t		update_crc_32(      uint32_t crc, unsigned char c                          );
uint64_t		update_crc_64_ecma( uint64_t crc, unsigned char c                          );
uint16_t		update_crc_ccitt(   uint16_t crc, unsigned char c                          );
uint16_t		update_crc_dnp(     uint16_t crc, unsigned char c                          );
uint16_t		update_crc_kermit(  uint16_t crc, unsigned char c                          );
uint16_t		update_crc_sick(    uint16_t crc, unsigned char c, unsigned char prev_byte );

/*
 * Global CRC lookup tables
 */

//extern const uint32_t	crc_tab32[];
//extern const uint64_t	crc_tab64[];

#ifdef __cplusplus
}// Extern C
#endif

#endif  // DEF_LIBCRC_CHECKSUM_H