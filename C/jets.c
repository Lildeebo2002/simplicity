#include "jets.h"
#include "secp256k1/secp256k1.h"
#include "secp256k1/util.h"
#ifdef SECP256K1_WIDEMUL_INT128
# include "secp256k1/int128.h"
# include "secp256k1/int128_impl.h"
#else
# include "secp256k1/int128_struct.h"
# include "secp256k1/int128_struct_impl.h"
#endif

static void write128(frameItem* frame, const secp256k1_uint128* x) {
  write64(frame, secp256k1_u128_hi_u64(x));
  write64(frame, secp256k1_u128_to_u64(x));
}

/* verify : TWO |- ONE */
bool verify(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  (void) dst; /* dst is unused. */
  return readBit(&src);
}

#define LOW_(bits)                                                 \
/* low_n : ONE |- TWO^n */                                         \
bool low_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                 \
  (void) src; /* src is unused. */                                 \
  write##bits(dst, 0);                                             \
  return true;                                                     \
}
LOW_(8)
LOW_(16)
LOW_(32)
LOW_(64)

#define ONE_(bits)                                                 \
/* one_n : ONE |- TWO^n */                                         \
bool one_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                 \
  (void) src; /* src is unused. */                                 \
  write##bits(dst, 1);                                             \
  return true;                                                     \
}
ONE_(8)
ONE_(16)
ONE_(32)
ONE_(64)

#define EQ_(bits)                                                 \
/* eq_n : TWO^n * TWO^n |- TWO */                                 \
bool eq_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                \
  uint_fast##bits##_t x = read##bits(&src);                       \
  uint_fast##bits##_t y = read##bits(&src);                       \
  writeBit(dst, x == y);                                          \
  return true;                                                    \
}
EQ_(8)
EQ_(16)
EQ_(32)
EQ_(64)

/* eq_256 : TWO^256 * TWO^256 |- TWO */
bool eq_256(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  uint32_t arr[16];
  read32s(arr, 16, &src);
  for (int i = 0; i < 8; ++i) {
    if (arr[i] != arr[i+8]) {
      writeBit(dst, false);
      return true;
    }
  }
  writeBit(dst, true);
  return true;
}

#define ADD_(bits)                                                 \
/* add_n : TWO^n * TWO^n |- TWO * TWO^n */                         \
bool add_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                 \
  uint_fast##bits##_t x = read##bits(&src);                        \
  uint_fast##bits##_t y = read##bits(&src);                        \
  writeBit(dst, 1U * UINT##bits##_MAX - y < x);                    \
  write##bits(dst, (uint_fast##bits##_t)(1U * x + y));             \
  return true;                                                     \
}
ADD_(8)
ADD_(16)
ADD_(32)
ADD_(64)

#define FULL_ADD_(bits)                                                                   \
/* full_add_n : TWO * TWO^n * TWO^n |- TWO * TWO^n */                                     \
bool full_add_##bits(frameItem* dst, frameItem src, const txEnv* env) {                   \
  (void) env; /* env is unused. */                                                        \
  bool z = readBit(&src);                                                                 \
  uint_fast##bits##_t x = read##bits(&src);                                               \
  uint_fast##bits##_t y = read##bits(&src);                                               \
  writeBit(dst, 1U * UINT##bits##_MAX - y < x || 1U * UINT##bits##_MAX - z < 1U * x + y); \
  write##bits(dst, (uint_fast##bits##_t)(1U * x + y + z));                                \
  return true;                                                                            \
}
FULL_ADD_(8)
FULL_ADD_(16)
FULL_ADD_(32)
FULL_ADD_(64)

#define SUBTRACT_(bits)                                                 \
/* subtract_n : TWO^n * TWO^n |- TWO * TWO^n */                         \
bool subtract_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                      \
  uint_fast##bits##_t x = read##bits(&src);                             \
  uint_fast##bits##_t y = read##bits(&src);                             \
  writeBit(dst, x < y);                                                 \
  write##bits(dst, (uint_fast##bits##_t)(1U * x - y));                  \
  return true;                                                          \
}
SUBTRACT_(8)
SUBTRACT_(16)
SUBTRACT_(32)
SUBTRACT_(64)

#define FULL_SUBTRACT_(bits)                                                 \
/* full_subtract_n : TWO * TWO^n * TWO^n |- TWO * TWO^n */                   \
bool full_subtract_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                           \
  bool z = readBit(&src);                                                    \
  uint_fast##bits##_t x = read##bits(&src);                                  \
  uint_fast##bits##_t y = read##bits(&src);                                  \
  writeBit(dst, x < y || 1U * x - y < z);                                    \
  write##bits(dst, (uint_fast##bits##_t)(1U * x - y - z));                   \
  return true;                                                               \
}
FULL_SUBTRACT_(8)
FULL_SUBTRACT_(16)
FULL_SUBTRACT_(32)
FULL_SUBTRACT_(64)

#define MULTIPLY_(bits,bitsx2)                                          \
bool multiply_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                      \
  uint_fast##bitsx2##_t x = read##bits(&src);                           \
  uint_fast##bitsx2##_t y = read##bits(&src);                           \
  write##bitsx2(dst, x * y);                                            \
  return true;                                                          \
}
MULTIPLY_(8, 16)
MULTIPLY_(16, 32)
MULTIPLY_(32, 64)

bool multiply_64(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  uint_fast64_t x = read64(&src);
  uint_fast64_t y = read64(&src);
  secp256k1_uint128 r;
  secp256k1_u128_mul(&r, x, y);
  write128(dst, &r);
  return true;
}

#define FULL_MULTIPLY_(bits,bitsx2)                                          \
bool full_multiply_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                           \
  uint_fast##bitsx2##_t x = read##bits(&src);                                \
  uint_fast##bitsx2##_t y = read##bits(&src);                                \
  uint_fast##bitsx2##_t z = read##bits(&src);                                \
  uint_fast##bitsx2##_t w = read##bits(&src);                                \
  write##bitsx2(dst, x * y + z + w);                                         \
  return true;                                                               \
}
FULL_MULTIPLY_(8, 16)
FULL_MULTIPLY_(16, 32)
FULL_MULTIPLY_(32, 64)

bool full_multiply_64(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  uint_fast64_t x = read64(&src);
  uint_fast64_t y = read64(&src);
  uint_fast64_t z = read64(&src);
  uint_fast64_t w = read64(&src);
  secp256k1_uint128 r;
  secp256k1_u128_mul(&r, x, y);
  secp256k1_u128_accum_u64(&r, z);
  secp256k1_u128_accum_u64(&r, w);
  write128(dst, &r);
  return true;
}

#define LE_(bits)                                                 \
/* le_n : TWO^n * TWO^n |- TWO */                                 \
bool le_##bits(frameItem* dst, frameItem src, const txEnv* env) { \
  (void) env; /* env is unused. */                                \
  uint_fast##bits##_t x = read##bits(&src);                       \
  uint_fast##bits##_t y = read##bits(&src);                       \
  writeBit(dst, x <= y);                                          \
  return true;                                                    \
}
LE_(8)
LE_(16)
LE_(32)
LE_(64)

/* sha_256_iv : ONE |- TWO^256 */
bool sha_256_iv(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  (void) src; /* env is unused. */

  uint32_t iv[8];
  sha256_iv(iv);

  write32s(dst, iv, 8);
  return true;
}

/* sha_256_block : TWO^256 * TWO^512 |- TWO^256 */
bool sha_256_block(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  uint32_t h[8];
  uint32_t block[16];
  read32s(h, 8, &src);
  read32s(block, 16, &src);
  sha256_compression(h, block);
  write32s(dst, h, 8);
  return true;
}

/* sha_256_ctx_8_init : ONE |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_init(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  (void) src; /* env is unused. */

  uint32_t iv[8];
  sha256_context ctx = sha256_init(iv);

  return write_sha256_context(dst, &ctx);
}

/* sha_256_ctx_8_add_n : CTX8 * (TWO^8)^n |- CTX8
 * where
 * n is a power of 2 less than or equal to 512
 * and
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
static bool sha_256_ctx_8_add_n(frameItem* dst, frameItem *src, size_t n) {
  simplicity_debug_assert(0 < n && n <= 512 && (n & (n - 1)) == 0);
  sha256_midstate midstate;
  unsigned char buf[512];
  sha256_context ctx = {.output = midstate.s};

  if (!read_sha256_context(&ctx, src)) return false;
  read8s(buf, n, src);
  sha256_uchars(&ctx, buf, n);
  return write_sha256_context(dst, &ctx);
}

/* sha_256_ctx_8_add_1 : CTX8 * TWO^8 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_1(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 1);
}

/* sha_256_ctx_8_add_2 : CTX8 * (TWO^8)^2 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_2(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 2);
}

/* sha_256_ctx_8_add_4 : CTX8 * (TWO^8)^4 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_4(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 4);
}

/* sha_256_ctx_8_add_8 : CTX8 * (TWO^8)^8 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_8(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 8);
}

/* sha_256_ctx_8_add_16 : CTX8 * (TWO^8)^16 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_16(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 16);
}

/* sha_256_ctx_8_add_32 : CTX8 * (TWO^8)^32 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_32(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 32);
}

/* sha_256_ctx_8_add_64 : CTX8 * (TWO^8)^64 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_64(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 64);
}

/* sha_256_ctx_8_add_128 : CTX8 * (TWO^8)^128 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_128(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 128);
}

/* sha_256_ctx_8_add_256 : CTX8 * (TWO^8)^256 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_256(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 256);
}

/* sha_256_ctx_8_add_512 : CTX8 * (TWO^8)^512 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_512(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  return sha_256_ctx_8_add_n(dst, &src, 512);
}

/* sha_256_ctx_8_add_buffer_511 : CTX8 * (TWO^8)^<512 |- CTX8
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_add_buffer_511(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  sha256_midstate midstate;
  unsigned char buf[511];
  size_t buf_len;
  sha256_context ctx = {.output = midstate.s};

  if (!read_sha256_context(&ctx, &src)) return false;

  read_buffer8(buf, &buf_len, &src, 8);
  sha256_uchars(&ctx, buf, buf_len);
  return write_sha256_context(dst, &ctx);
}

/* sha_256_ctx_8_finalize : CTX8 |- TWO^256
 * where
 * CTX8 = (TWO^8)^<64 * TWO^64 * TWO^256
 */
bool sha_256_ctx_8_finalize(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  sha256_midstate midstate;
  sha256_context ctx = {.output = midstate.s};

  if (!read_sha256_context(&ctx, &src)) return false;

  sha256_finalize(&ctx);
  write32s(dst, midstate.s, 8);
  return true;
}

/* parse_sequence : TWO^32 |- TWO^32 + TWO^32 */
bool parse_lock(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  uint_fast32_t nLockTime = read32(&src);
  writeBit(dst, 500000000U <= nLockTime);
  write32(dst, nLockTime);
  return true;
}

/* parse_sequence : TWO^32 |- S (TWO^16 + TWO^16) */
bool parse_sequence(frameItem* dst, frameItem src, const txEnv* env) {
  (void) env; /* env is unused. */
  uint_fast32_t nSequence = read32(&src);
  if (writeBit(dst, nSequence < ((uint_fast32_t)1 << 31))) {
    writeBit(dst, nSequence & ((uint_fast32_t)1 << 22));
    write16(dst, nSequence & 0xffff);
  } else {
    skipBits(dst, 17);
  }
  return true;
}
