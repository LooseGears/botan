/*
* BLAKE2b
* (C) 2016 cynecx
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_BLAKE2B_H_
#define BOTAN_BLAKE2B_H_

#include <botan/hash.h>
#include <string>
#include <memory>

BOTAN_FUTURE_INTERNAL_HEADER(blake2b.h)

namespace Botan {

/**
* BLAKE2B
*/
class BOTAN_PUBLIC_API(2,0) BLAKE2b final : public HashFunction, public SymmetricAlgorithm
   {
   public:
      /**
      * @param output_bits the output size of BLAKE2b in bits
      */
      explicit BLAKE2b(size_t output_bits = 512);
      BLAKE2b(const SymmetricKey& key, size_t output_bits = 512);
      BLAKE2b(const uint8_t key[], size_t key_length, size_t output_bits = 512);

      template<typename Alloc>
      BLAKE2b(const std::vector<uint8_t, Alloc>& key, size_t output_bits = 512) :
          BLAKE2b(key.data(), key.size(), output_bits)
      {
      }

      size_t hash_block_size() const override { return 128; }
      size_t output_length() const override { return m_output_bits / 8; }

      Key_Length_Specification key_spec() const override;

      HashFunction* clone() const override;
      std::string name() const override;
      void clear() override;

      std::unique_ptr<HashFunction> copy_state() const override;

   public:
      void key_schedule(const uint8_t key[], size_t length) override;

      void add_data(const uint8_t input[], size_t length) override;
      void final_result(uint8_t out[]) override;

   private:
      void state_init();
      void compress(const uint8_t* data, size_t blocks, uint64_t increment);

      const size_t m_output_bits;

      secure_vector<uint8_t> m_buffer;
      size_t m_bufpos;

      secure_vector<uint64_t> m_H;
      uint64_t m_T[2];
      uint64_t m_F[2];

      size_t m_key_size;
      secure_vector<uint8_t> m_padded_key_buffer;
   };

typedef BLAKE2b Blake2b;

}

#endif
