#include "helper.h"

void LibElf::Helper::append(std::string *string, std::string append)
{
    if (!(*string).empty())
        (*string).append(" | ");
    (*string).append(append);
}

Elf_Half LibElf::Helper::endian()
{
    uint16_t num = 1;
    char *ptr = reinterpret_cast<char *>(&num);

    return (ptr[0] == 1) ? ELFDATA2LSB : ELFDATA2MSB;
}

void LibElf::Helper::byteswap_16(uint16_t *swap)
{
    *swap = (((((*swap) >> 8) & 0xff) | (((*swap) & 0xff) << 8)));
}

void LibElf::Helper::byteswap_32(uint32_t *swap)
{
    *swap = ((((*swap) & 0xff000000) >> 24) | (((*swap) & 0x00ff0000) >>  8)
             | (((*swap) & 0x0000ff00) <<  8) | (((*swap) & 0x000000ff) << 24));
}

void LibElf::Helper::byteswap_64(uint64_t *swap)
{
    *swap = ((((*swap) & 0xff00000000000000ull) >> 56)
        | (((*swap) & 0x00ff000000000000ull) >> 40)
        | (((*swap) & 0x0000ff0000000000ull) >> 24)
        | (((*swap) & 0x000000ff00000000ull) >> 8)
        | (((*swap) & 0x000000ff00000000ull) >> 8)
        | (((*swap) & 0x0000000000ff0000ull) << 24)
        | (((*swap) & 0x000000000000ff00ull) << 40)
        | (((*swap) & 0x00000000000000ffull) << 56));
}
