/*
* BLAKE2b MAC
* (C) 1999-2007,2014 Jack Lloyd
* (C) 2020           Tom Crowley
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_BLAKE2MAC_H_
#define BOTAN_BLAKE2MAC_H_

#include <botan/mac.h>
#include <botan/blake2b.h>

BOTAN_FUTURE_INTERNAL_HEADER(blake2bmac.h)


namespace Botan {

/**
* BLAKE2b MAC
*/
class BOTAN_PUBLIC_API(2, 0) BLAKE2bMAC final : public MessageAuthenticationCode
{
public:
   std::string name() const override { return m_blake.name(); }
   size_t output_length() const override { return m_blake.output_length(); }
   MessageAuthenticationCode* clone() const override;

   void clear() override;

   Key_Length_Specification key_spec() const override
      {
      return m_blake.key_spec();
      }

   void key_schedule(const uint8_t key[], size_t length) override
      {
       m_blake.key_schedule(key, length);
      }

   void add_data(const uint8_t input[], size_t length) override
      {
      verify_key_set(m_blake.key_size() > 0);
      m_blake.add_data(input, length);
      }

   void final_result(uint8_t out[]) override
      {
      verify_key_set(m_blake.key_size() > 0);
      m_blake.final_result(out);
      }

   explicit BLAKE2bMAC(size_t output_bits = 512);

   BLAKE2bMAC(const BLAKE2bMAC&) = delete;
   BLAKE2bMAC& operator=(const BLAKE2bMAC&) = delete;
private:
   BLAKE2b m_blake;
};

typedef BLAKE2bMAC Blake2bMac;

}

#endif
