/**
 * \file
 * \brief CryptoAuthLib Basic API methods - a simple crypto authentication API.
 * These methods manage a global ATCADevice object behind the scenes. They also
 * manage the wake/idle state transitions so callers don't need to.
 *
 * \copyright (c) 2017 Microchip Technology Inc. and its subsidiaries.
 *            You may use this software and any derivatives exclusively with
 *            Microchip products.
 *
 * \page License
 *
 * (c) 2017 Microchip Technology Inc. and its subsidiaries. You may use this
 * software and any derivatives exclusively with Microchip products.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIPS TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
 * TERMS.
 */

#include "cryptoauthlib/cryptoauthlib_defs.h"

#include "cryptoauthlib.h"
#include "crypto/atca_crypto_sw_sha2.h"

#ifndef ATCA_BASIC_H_
#define ATCA_BASIC_H_

#define TBD   void

/** \defgroup atcab_ Basic Crypto API methods (atcab_)
 *
 * \brief
 * These methods provide the most convenient, simple API to CryptoAuth chips
 *
   @{ */

#ifdef __cplusplus
extern "C" {
#endif

#define BLOCK_NUMBER(a) (a / 32)
#define WORD_OFFSET(a)  ((a % 32) / 4)

extern ATCADevice _gDevice;

// Basic global methods
CRYPTOAUTHLIB_API ATCA_STATUS atcab_version(char *ver_str);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_static_init(ATCAIfaceCfg *cfg, ATCADevice dev, ATCACommand cmd, ATCAIface iface);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_init(ATCAIfaceCfg *cfg);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_init_device(ATCADevice ca_device);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_release(void);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_static_release(void);
CRYPTOAUTHLIB_API ATCADevice atcab_get_device(void);
CRYPTOAUTHLIB_API ATCA_STATUS _atcab_exit(void);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_wakeup(void);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_idle(void);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sleep(void);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_cfg_discover(ATCAIfaceCfg cfg_array[], int max);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_get_addr(uint8_t zone, uint16_t slot, uint8_t block, uint8_t offset, uint16_t* addr);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_get_zone_size(uint8_t zone, uint16_t slot, size_t* size);

// AES command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes(uint8_t mode, uint16_t key_id, const uint8_t* aes_in, uint8_t* aes_out);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_encrypt(uint16_t key_id, uint8_t key_block, const uint8_t* plaintext, uint8_t* ciphertext);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_decrypt(uint16_t key_id, uint8_t key_block, const uint8_t* ciphertext, uint8_t* plaintext);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_gfm(const uint8_t* h, const uint8_t* input, uint8_t* output);

typedef struct atca_aes_cbc_ctx
{
    uint16_t key_id;                     //!< Key location. Can either be a slot number or ATCA_TEMPKEY_KEYID for TempKey.
    uint8_t  key_block;                  //!< Index of the 16-byte block to use within the key location for the actual key.
    uint8_t  ciphertext[AES_DATA_SIZE];  //!< Ciphertext from last operation.
} atca_aes_cbc_ctx_t;

CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_cbc_init(atca_aes_cbc_ctx_t* ctx, uint16_t key_id, uint8_t key_block, const uint8_t* iv);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_cbc_encrypt_block(atca_aes_cbc_ctx_t* ctx, const uint8_t* plaintext, uint8_t* ciphertext);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_cbc_decrypt_block(atca_aes_cbc_ctx_t* ctx, const uint8_t* ciphertext, uint8_t* plaintext);

typedef struct atca_aes_cmac_ctx
{
    atca_aes_cbc_ctx_t cbc_ctx;              //!< CBC context
    uint32_t           block_size;           //!< Number of bytes in current block.
    uint8_t            block[AES_DATA_SIZE]; //!< Unprocessed message storage.
} atca_aes_cmac_ctx_t;

CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_cmac_init(atca_aes_cmac_ctx_t* ctx, uint16_t key_id, uint8_t key_block);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_cmac_update(atca_aes_cmac_ctx_t* ctx, const uint8_t* data, uint32_t data_size);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_aes_cmac_finish(atca_aes_cmac_ctx_t* ctx, uint8_t* cmac, uint32_t cmac_size);

// CheckMAC command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_checkmac(uint8_t mode, uint16_t key_id, const uint8_t *challenge, const uint8_t *response, const uint8_t *other_data);

// Counter command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_counter(uint8_t mode, uint16_t counter_id, uint32_t* counter_value);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_counter_increment(uint16_t counter_id, uint32_t* counter_value);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_counter_read(uint16_t counter_id, uint32_t* counter_value);

// DeriveKey command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_derivekey(uint8_t mode, uint16_t key_id, const uint8_t* mac);

// ECDH command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_ecdh_base(uint8_t mode, uint16_t key_id, const uint8_t* public_key, uint8_t* pms, uint8_t* out_nonce);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_ecdh(uint16_t key_id, const uint8_t* public_key, uint8_t* pms);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_ecdh_enc(uint16_t key_id, const uint8_t* public_key, uint8_t* pms, const uint8_t* read_key, uint16_t read_key_id);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_ecdh_ioenc(uint16_t key_id, const uint8_t* public_key, uint8_t* pms, const uint8_t* io_key);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_ecdh_tempkey(const uint8_t* public_key, uint8_t* pms);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_ecdh_tempkey_ioenc(const uint8_t* public_key, uint8_t* pms, const uint8_t* io_key);

// GenDig command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_gendig(uint8_t zone, uint16_t key_id, const uint8_t *other_data, uint8_t other_data_size);

// GenKey command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_genkey_base(uint8_t mode, uint16_t key_id, const uint8_t* other_data, uint8_t* public_key);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_genkey(uint16_t key_id, uint8_t* public_key);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_get_pubkey(uint16_t key_id, uint8_t* public_key);

// HMAC command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_hmac(uint8_t mode, uint16_t key_id, uint8_t* digest);

// Info command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_info_base(uint8_t mode, uint16_t param2, uint8_t* out_data);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_info(uint8_t* revision);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_info_set_latch(bool state);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_info_get_latch(bool* state);

// KDF command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_kdf(uint8_t mode, uint16_t key_id, const uint32_t details, const uint8_t* message, uint8_t* out_data, uint8_t* out_nonce);

// Lock command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_lock(uint8_t mode, uint16_t summary_crc);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_lock_config_zone(void);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_lock_config_zone_crc(uint16_t summary_crc);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_lock_data_zone(void);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_lock_data_zone_crc(uint16_t summary_crc);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_lock_data_slot(uint16_t slot);

// MAC command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_mac(uint8_t mode, uint16_t key_id, const uint8_t* challenge, uint8_t* digest);

// Nonce command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_nonce_base(uint8_t mode, uint16_t zero, const uint8_t *num_in, uint8_t* rand_out);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_nonce(const uint8_t *num_in);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_nonce_load(uint8_t target, const uint8_t *num_in, uint16_t num_in_size);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_nonce_rand(const uint8_t *num_in, uint8_t* rand_out);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_challenge(const uint8_t *num_in);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_challenge_seed_update(const uint8_t *num_in, uint8_t* rand_out);

// PrivWrite command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_priv_write(uint16_t key_id, const uint8_t priv_key[36], uint16_t write_key_id, const uint8_t write_key[32]);

// Random command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_random(uint8_t* rand_out);

// Read command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_read_zone(uint8_t zone, uint16_t slot, uint8_t block, uint8_t offset, uint8_t *data, uint8_t len);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_is_locked(uint8_t zone, bool *is_locked);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_is_slot_locked(uint16_t slot, bool *is_locked);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_read_bytes_zone(uint8_t zone, uint16_t slot, size_t offset, uint8_t *data, size_t length);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_read_serial_number(uint8_t* serial_number);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_read_pubkey(uint16_t slot, uint8_t *public_key);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_read_sig(uint16_t slot, uint8_t *sig);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_read_config_zone(uint8_t* config_data);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_cmp_config_zone(uint8_t* config_data, bool* same_config);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_read_enc(uint16_t key_id, uint8_t block, uint8_t *data, const uint8_t* enc_key, const uint16_t enc_key_id);

// SecureBoot command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_secureboot(uint8_t mode, uint16_t param2, const uint8_t* digest, const uint8_t* signature, uint8_t* mac);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_secureboot_mac(uint8_t mode, const uint8_t* digest, const uint8_t* signature, const uint8_t* num_in, const uint8_t* io_key, bool* is_verified);

// SelfTest command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_selftest(uint8_t mode, uint16_t param2, uint8_t* result);

// SHA command functions
typedef struct atca_sha256_ctx
{
    uint32_t total_msg_size;                     //!< Total number of message bytes processed
    uint32_t block_size;                         //!< Number of bytes in current block
    uint8_t  block[ATCA_SHA256_BLOCK_SIZE * 2];  //!< Unprocessed message storage
} atca_sha256_ctx_t;

typedef atca_sha256_ctx_t atca_hmac_sha256_ctx_t;

CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_base(uint8_t mode, uint16_t length, const uint8_t* data_in, uint8_t* data_out, uint16_t* data_out_size);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_start(void);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_update(const uint8_t* message);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_end(uint8_t *digest, uint16_t length, const uint8_t *message);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_read_context(uint8_t* context, uint16_t* context_size);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_write_context(const uint8_t* context, uint16_t context_size);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha(uint16_t length, const uint8_t *message, uint8_t *digest);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_hw_sha2_256(const uint8_t * data, size_t data_size, uint8_t* digest);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_hw_sha2_256_init(atca_sha256_ctx_t* ctx);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_hw_sha2_256_update(atca_sha256_ctx_t* ctx, const uint8_t* data, size_t data_size);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_hw_sha2_256_finish(atca_sha256_ctx_t* ctx, uint8_t* digest);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_hmac_init(atca_hmac_sha256_ctx_t* ctx, uint16_t key_slot);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_hmac_update(atca_hmac_sha256_ctx_t* ctx, const uint8_t* data, size_t data_size);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_hmac_finish(atca_hmac_sha256_ctx_t* ctx, uint8_t* digest, uint8_t target);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sha_hmac(const uint8_t * data, size_t data_size, uint16_t key_slot, uint8_t* digest, uint8_t target);

// Sign command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sign_base(uint8_t mode, uint16_t key_id, uint8_t *signature);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sign(uint16_t key_id, const uint8_t *msg, uint8_t *signature);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_sign_internal(uint16_t key_id, bool is_invalidate, bool is_full_sn, uint8_t *signature);

// UpdateExtra command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_updateextra(uint8_t mode, uint16_t new_value);

// Verify command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_verify(uint8_t mode, uint16_t key_id, const uint8_t* signature, const uint8_t* public_key, const uint8_t* other_data, uint8_t* mac);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_verify_extern(const uint8_t *message, const uint8_t *signature, const uint8_t *public_key, bool *is_verified);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_verify_extern_mac(const uint8_t *message, const uint8_t* signature, const uint8_t* public_key, const uint8_t* num_in, const uint8_t* io_key, bool* is_verified);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_verify_stored(const uint8_t *message, const uint8_t *signature, uint16_t key_id, bool *is_verified);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_verify_stored_mac(const uint8_t *message, const uint8_t *signature, uint16_t key_id, const uint8_t* num_in, const uint8_t* io_key, bool* is_verified);

CRYPTOAUTHLIB_API ATCA_STATUS atcab_verify_validate(uint16_t key_id, const uint8_t *signature, const uint8_t *other_data, bool *is_verified);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_verify_invalidate(uint16_t key_id, const uint8_t *signature, const uint8_t *other_data, bool *is_verified);

// Write command functions
CRYPTOAUTHLIB_API ATCA_STATUS atcab_write(uint8_t zone, uint16_t address, const uint8_t *value, const uint8_t *mac);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_write_zone(uint8_t zone, uint16_t slot, uint8_t block, uint8_t offset, const uint8_t *data, uint8_t len);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_write_bytes_zone(uint8_t zone, uint16_t slot, size_t offset_bytes, const uint8_t *data, size_t length);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_write_pubkey(uint16_t slot, const uint8_t *public_key);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_write_config_zone(const uint8_t* config_data);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_write_enc(uint16_t key_id, uint8_t block, const uint8_t *data, const uint8_t* enc_key, const uint16_t enc_key_id);
CRYPTOAUTHLIB_API ATCA_STATUS atcab_write_config_counter(uint16_t counter_id, uint32_t counter_value);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ATCA_BASIC_H_ */