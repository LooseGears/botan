/*
* BLAKE2b MAC
* (C) 1999-2007,2014 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_BLAKE2MAC_H_
#define BOTAN_BLAKE2MAC_H_

#include <botan/mac.h>
#include <botan/hash/blake2b.h>

BOTAN_FUTURE_INTERNAL_HEADER(blake2mac.h)


namespace Botan {

/**
* BLAKE2b MAC
*/
class BOTAN_PUBLIC_API(2, 0) BLAKE2bMAC final : public MessageAuthenticationCode
{
public:
   std::string name() const override { return m_cipher.name(); }
   size_t output_length() const override { return m_cipher.output_length(); }
   MessageAuthenticationCode* clone() const override;

   void clear() override;

   Key_Length_Specification key_spec() const override
      {
      return m_cipher.key_spec();
      }

   void key_schedule(const uint8_t key[], size_t length) override
      {
       m_cipher.key_schedule(key, length);
      }

   void add_data(const uint8_t input[], size_t length) override
      {
      m_cipher.add_data(input, length);
      }

   void final_result(uint8_t out[]) override
      {
      m_cipher.final_result(out);
      }

   explicit BLAKE2bMAC(size_t output_bits = 512);

   BLAKE2bMAC(const BLAKE2bMAC&) = delete;
   BLAKE2bMAC& operator=(const BLAKE2bMAC&) = delete;
private:
   BLAKE2b m_cipher;
};

typedef BLAKE2bMAC Blake2bMac;

}

#endif