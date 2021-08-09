#include "checkSigHashAllTx1.h"

/* A length-prefixed encoding of the following Simplicity program:
 *     Simplicity.Programs.CheckSigHash.checkSigHash' Simplicity.Elements.Programs.CheckSigHashAll.Lib.hashAll
 *     (Simplicity.LibSecp256k1.Spec.PubKey 0x00000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63)
 *     (Simplicity.LibSecp256k1.Spec.Sig 0x00000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63
 *                                       0xe24bd0f462c46ce539b7d53598f96744cdf876a247e460fe095a85b090e3295c)
 * with jets.
 */
const unsigned char elementsCheckSigHashAllTx1[] = {
  0xe8, 0xe4, 0x49, 0x02, 0x04, 0x08, 0x10, 0x20, 0x41, 0x74, 0x08, 0x16, 0x80, 0xae, 0xa1, 0x28, 0xa8, 0x5a, 0x82, 0xd4,
  0x16, 0xfd, 0x02, 0x68, 0x16, 0x7c, 0x00, 0x50, 0x2d, 0x7c, 0x08, 0x5b, 0x35, 0x0a, 0x05, 0x80, 0x5a, 0x34, 0x0b, 0x4e,
  0xe1, 0x40, 0xb8, 0x17, 0x02, 0x17, 0x02, 0x0a, 0x85, 0x98, 0x5c, 0x00, 0x2e, 0x12, 0x17, 0x06, 0xe0, 0x22, 0xe0, 0x01,
  0x70, 0x8e, 0x10, 0x27, 0x10, 0x8a, 0x85, 0xc3, 0x78, 0x30, 0xb8, 0x10, 0x5c, 0x23, 0x89, 0x85, 0xa0, 0x2a, 0x16, 0x41,
  0x71, 0x57, 0x0c, 0x13, 0x11, 0x70, 0x3e, 0x0c, 0x28, 0x16, 0xdd, 0xa2, 0xe2, 0xfe, 0x26, 0x13, 0x88, 0x05, 0x42, 0xc4,
  0x2d, 0x41, 0x70, 0x3e, 0x00, 0x2e, 0x34, 0xe0, 0x22, 0x81, 0x70, 0x8e, 0x20, 0x17, 0x04, 0xe2, 0x11, 0x40, 0xb0, 0x0b,
  0x8b, 0x38, 0x60, 0xb8, 0x9b, 0x88, 0xc5, 0x02, 0xe1, 0xfc, 0x58, 0x2e, 0x28, 0xe3, 0x71, 0x40, 0xb0, 0x0b, 0x40, 0x5c,
  0x00, 0x2e, 0x26, 0x0b, 0x8d, 0xb9, 0x08, 0x2e, 0x1e, 0x17, 0x1a, 0xf1, 0x08, 0xb8, 0xd7, 0x90, 0x02, 0x81, 0x60, 0x17,
  0x1c, 0x71, 0x28, 0xb8, 0x9b, 0x8d, 0x85, 0x02, 0xe2, 0xde, 0x43, 0x0b, 0x88, 0x38, 0xd8, 0x50, 0x2c, 0x02, 0xd0, 0x17,
  0x21, 0x39, 0x00, 0x2e, 0x3e, 0xe2, 0x51, 0x40, 0xb9, 0x0f, 0xc8, 0xe1, 0x72, 0x37, 0x90, 0xe2, 0x81, 0x60, 0x17, 0x24,
  0xb9, 0x24, 0x2e, 0x44, 0x71, 0xd0, 0xa0, 0x5c, 0x73, 0xc8, 0xe1, 0x71, 0xa7, 0x22, 0x05, 0x02, 0xc0, 0x2d, 0x01, 0x70,
  0x00, 0xb8, 0xff, 0x91, 0xa2, 0xe5, 0x1f, 0x21, 0x45, 0x02, 0xe4, 0xa7, 0x27, 0x05, 0xc9, 0x5e, 0x48, 0x8a, 0x05, 0x80,
  0x5c, 0x80, 0xe4, 0x88, 0xb9, 0x0f, 0xca, 0x31, 0x40, 0xb9, 0x29, 0xc9, 0xa1, 0x72, 0x93, 0x91, 0xe2, 0x81, 0x60, 0x16,
  0x80, 0xb9, 0x23, 0xca, 0x01, 0x72, 0x3f, 0x92, 0x42, 0x81, 0x72, 0x8f, 0x94, 0xa2, 0xe4, 0x3f, 0x29, 0xc5, 0x02, 0xc0,
  0x2e, 0x50, 0x72, 0xc4, 0x4e, 0x00, 0x2e, 0x4a, 0xf2, 0x44, 0x5c, 0x8d, 0xe5, 0xa0, 0xa0, 0x58, 0x05, 0x98, 0x5b, 0xc2,
  0xe1, 0xe4, 0x51, 0x13, 0x98, 0x64, 0x90, 0x20, 0x41, 0x70, 0x13, 0x01, 0x02, 0xc0, 0x81, 0x41, 0xc2, 0xcf, 0x31, 0x66,
  0x16, 0xa0, 0x99, 0x1c, 0x1c, 0x86, 0x24, 0x81, 0x02, 0x0b, 0x80, 0xb0, 0x0b, 0x00, 0xb0, 0x1b, 0x81, 0x0a, 0x03, 0xac,
  0x83, 0x0d, 0x0c, 0x30, 0xc3, 0x0e, 0x16, 0x63, 0xe9, 0x30, 0xfa, 0x45, 0x06, 0x18, 0x61, 0xc2, 0xd2, 0x3e, 0x93, 0x0f,
  0xc0, 0x45, 0x07, 0xd4, 0x28, 0x30, 0xf9, 0x98, 0x7e, 0x0e, 0x28, 0x3f, 0x00, 0x14, 0x0b, 0x31, 0x87, 0xd4, 0x61, 0xf5,
  0x18, 0x7e, 0x20, 0x14, 0x1f, 0x84, 0x8a, 0x05, 0x98, 0x5a, 0x87, 0x0b, 0x85, 0x85, 0xc1, 0xb8, 0x21, 0xc2, 0xe0, 0x03,
  0x8e, 0x16, 0x40, 0x71, 0xa0, 0x1c, 0x92, 0x52, 0x13, 0x9d, 0xa4, 0x18, 0x83, 0x0c, 0x30, 0xc3, 0x85, 0x99, 0x24, 0x08,
  0x10, 0x5c, 0x04, 0xc0, 0x4c, 0x05, 0x80, 0x4d, 0xe7, 0x0b, 0x4e, 0x42, 0xc8, 0x2d, 0x21, 0x38, 0x21, 0xc1, 0xc8, 0x0e,
  0x02, 0x3f, 0x08, 0x30, 0xfc, 0x24, 0x50, 0x61, 0xf1, 0x30, 0xfc, 0x34, 0x50, 0x2c, 0x46, 0x1f, 0x41, 0x87, 0xd0, 0x61,
  0xf8, 0x90, 0x50, 0x2c, 0x42, 0xd0, 0x49, 0x44, 0x82, 0x81, 0x48, 0x28, 0x14, 0x82, 0x81, 0x48, 0x28, 0x17, 0x08, 0x0b,
  0x85, 0x8e, 0x17, 0x07, 0x24, 0x5d, 0x02, 0x1d, 0x02, 0x00, 0x81, 0x60, 0x26, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x82,
  0xec, 0x16, 0x90, 0xa6, 0xa1, 0x40, 0xb5, 0x05, 0x8e, 0x22, 0xc4, 0x26, 0xd1, 0x60, 0x16, 0xd0, 0xb6, 0x85, 0xb4, 0x2d,
  0xa1, 0x70, 0x61, 0x47, 0x0b, 0x8a, 0xc7, 0x0b, 0x90, 0x03, 0x05, 0xc5, 0x9c, 0x5a, 0x2e, 0x2b, 0x0b, 0x8a, 0x82, 0x72,
  0x68, 0x5c, 0x55, 0xc5, 0x42, 0x05, 0x96, 0x42, 0xe2, 0xf0, 0xb8, 0xd7, 0x8d, 0x45, 0xc6, 0x81, 0x38, 0xc8, 0x58, 0x05,
  0xa0, 0x2d, 0x01, 0x71, 0x88, 0x9c, 0x7a, 0x28, 0x16, 0xe1, 0x81, 0xe0, 0x80, 0x72, 0xc0, 0x2e, 0x59, 0x93, 0x01, 0x02,
  0x28, 0x06, 0x09, 0xe0, 0xc8, 0x83, 0x05, 0x42, 0xc8, 0x83, 0x85, 0x46, 0x18, 0x83, 0x0e, 0x30, 0xdb, 0x4e, 0x38, 0xc3,
  0xf3, 0x80, 0x71, 0xc6, 0x1b, 0x9c, 0x43, 0x0e, 0x16, 0x03, 0xf3, 0x1e, 0x61, 0xc2, 0xc0, 0x2d, 0xa1, 0x70, 0x21, 0xb8,
  0x59, 0xc7, 0x0b, 0x00, 0xb8, 0x59, 0x07, 0x1c, 0x70, 0xb1, 0x03, 0x8c, 0x42, 0xe8, 0x55, 0xe8, 0x71, 0x17, 0x42, 0xc7,
  0x42, 0xe8, 0xa0, 0x5d, 0x0b, 0x1d, 0x0b, 0x02, 0xe8, 0x6f, 0xe8, 0x55, 0x14, 0x0b, 0x00, 0xba, 0x1e, 0xba, 0x14, 0xc5,
  0xd0, 0xbf, 0xd1, 0x04, 0x28, 0x17, 0x43, 0xaf, 0x43, 0xd8, 0xba, 0x18, 0x3a, 0x18, 0x85, 0x02, 0xc0, 0x2d, 0x01, 0x74,
  0x33, 0x74, 0x38, 0x8b, 0xa2, 0x2b, 0xa1, 0x84, 0x50, 0x2e, 0x87, 0x6e, 0x87, 0x41, 0x74, 0x2b, 0x05, 0x42, 0xe8, 0x81,
  0xe8, 0x79, 0x17, 0x42, 0x90, 0x5d, 0x0d, 0x1d, 0x10, 0x42, 0x70, 0x51, 0x50, 0xb2, 0x0b, 0x68, 0x5d, 0x11, 0x1d, 0x0e,
  0xc2, 0xe8, 0x77, 0xe8, 0x6e, 0x14, 0x0b, 0xa1, 0xc3, 0xa1, 0xc0, 0x5d, 0x09, 0xa1, 0x50, 0xba, 0x1c, 0xfa, 0x1b, 0x85,
  0xd1, 0x0f, 0xd1, 0x16, 0x28, 0x17, 0x43, 0xd7, 0x43, 0x88, 0x9d, 0x0b, 0x22, 0xa1, 0x66, 0x17, 0x44, 0x5f, 0x44, 0xa0,
  0xba, 0x11, 0xc2, 0xe8, 0x87, 0xe8, 0x93, 0x17, 0x44, 0x87, 0x44, 0x08, 0xa0, 0x58, 0x05, 0xd1, 0x2f, 0xd1, 0x30, 0x2e,
  0x83, 0xd0, 0xba, 0x25, 0x7a, 0x1f, 0x45, 0xd1, 0x37, 0xd1, 0x3c, 0x28, 0x16, 0x01, 0x66, 0x16, 0xe0, 0xb8, 0x62, 0xe2,
  0xe4, 0x50, 0x2c, 0x1a, 0x80, 0x81, 0x71, 0xf8, 0xfc, 0x85, 0x30, 0xfd, 0x05, 0xe8, 0x30, 0xc1, 0x60, 0x03, 0x50, 0xb3,
  0x1f, 0xa0, 0xd8, 0xfd, 0x06, 0xe6, 0xd0, 0x28, 0x03, 0x80, 0x07, 0x10, 0x33, 0x03, 0x80, 0x87, 0xd0, 0x92, 0x17, 0x42,
  0x58, 0x0e, 0x0c, 0x2e, 0x8b, 0xee, 0x8c, 0xd1, 0x3a, 0x33, 0x44, 0xe8, 0xcd, 0x13, 0xa3, 0x34, 0x4e, 0x8c, 0xd1, 0x39,
  0xbe, 0x17, 0x46, 0x9f, 0x45, 0x70, 0x9d, 0x1a, 0x62, 0xe8, 0xd3, 0x0b, 0xa3, 0x4c, 0x2e, 0x8d, 0x30, 0xb9, 0xc4, 0x0b,
  0x30, 0xb7, 0x00, 0xe2, 0x51, 0x74, 0x4c, 0x9c, 0x51, 0xb1, 0x02, 0x3d, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xb7, 0x8c, 0xe5, 0x63, 0xf8, 0x9a, 0x0e, 0xd9, 0x41, 0x4f, 0x5a, 0xa2, 0x8a, 0xd0, 0xd9,
  0x6d, 0x67, 0x95, 0xf9, 0xc6, 0x3e, 0x24, 0xbd, 0x0f, 0x46, 0x2c, 0x46, 0xce, 0x53, 0x9b, 0x7d, 0x53, 0x59, 0x8f, 0x96,
  0x74, 0x4c, 0xdf, 0x87, 0x6a, 0x24, 0x7e, 0x46, 0x0f, 0xe0, 0x95, 0xa8, 0x5b, 0x09, 0x0e, 0x32, 0x95, 0xc0
};

const size_t sizeof_elementsCheckSigHashAllTx1 = sizeof(elementsCheckSigHashAllTx1);

/* The commitment Merkle root of the above elementsCheckSigHashAllTx1 Simplicity expression. */
const uint32_t elementsCheckSigHashAllTx1_cmr[] = {
  0x50bc0fcau, 0x63c6760au, 0x037094bau, 0x841aff28u, 0xe3dcd403u, 0x38d63f97u, 0x1ba02b9du, 0x12496100u
};

/* The identity Merkle root of the above elementsCheckSigHashAllTx1 Simplicity expression. */
const uint32_t elementsCheckSigHashAllTx1_imr[] = {
  0x40e17aeeu, 0x57e2f363u, 0xf3dcc276u, 0x16b75a2fu, 0xc9c552bdu, 0xf6c6f50du, 0x2a2c5fb5u, 0x883e21a4u
};

/* The annotated Merkle root of the above elementsCheckSigHashAllTx1 Simplicity expression. */
const uint32_t elementsCheckSigHashAllTx1_amr[] = {
  0x73fb1b8du, 0xc916003au, 0x2c733ab6u, 0x7844896eu, 0x627b23a0u, 0xd510ab58u, 0x454272e7u, 0x1b21f7ebu
};
