#pragma once

#include <string>
#include "lib_data.h"

namespace LibElf
{
    class Helper
    {
        public:
            static void append(std::string *string, std::string append);
            static Elf_Half endian();
            static void byteswap_16(uint16_t *swap);
            static void byteswap_32(uint32_t *swap);
            static void byteswap_64(uint64_t *swap);
    };
}
