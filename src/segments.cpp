#include "segments.h"
#include "elf_identification.h"
#include "elf_header.h"
#include "lib_elf.h"
#include "helper.h"

LibElf::Segments::Segments(LibElf *lib_elf)
{
    this->lib_elf = lib_elf;
}

LibElf::Segments::~Segments()
{
    this->clear();
}

bool LibElf::Segments::load()
{
    // Try to read segment headers
    if (!read_headers())
        return false;

    // Set flag
    ok = true;

    // Everything went fine
    return true;
}

bool LibElf::Segments::is_ok()
{
    return ok;
}

void LibElf::Segments::clear()
{
    // Reset flag
    ok = false;

    // Clear vectors
    headers.clear();
}

LibElf::SegmentHeader *LibElf::Segments::get_header(Elf_Half shndx)
{
    return headers.at(shndx).get();
}

bool LibElf::Segments::read_headers()
{
    // Set offset for segment headers to read
    Elf_Off ph_off = lib_elf->get_elf_header()->get_phoff();
    lib_elf->get_ifstream()->seekg(ph_off);

    for (Elf_Half i = 0; i < lib_elf->get_elf_header()->get_phnum(); ++i)
    {
        // Create new section header
        auto header = std::make_shared<SegmentHeader>(lib_elf);

        // Load section header data
        if (!header->load())
            return false;

        // Save pointer
        headers.push_back(header);
    }

    // Everything went fine
    return true;
}

LibElf::SegmentHeader::SegmentHeader(LibElf *lib_elf)
{
    this->lib_elf = lib_elf;
    this->elf_identification = lib_elf->get_elf_identification();
    this->elf_header = lib_elf->get_elf_header();
}

LibElf::SegmentHeader::~SegmentHeader()
{
}

bool LibElf::SegmentHeader::load()
{
    // Try to read section header data
    if (!read())
        return false;

    // Convert data to correct endianness
    if (Helper::endian() != elf_identification->get_data())
        convert();

    // Everything went fine
    return true;
}

Elf_Word LibElf::SegmentHeader::get_type()
{
    return type;
}

Elf_Off LibElf::SegmentHeader::get_offset()
{
    return offset;
}

Elf_Addr LibElf::SegmentHeader::get_vaddr()
{
    return vaddr;
}

Elf_Addr LibElf::SegmentHeader::get_paddr()
{
    return paddr;
}

Elf_Xword LibElf::SegmentHeader::get_filesz()
{
    return filesz;
}

Elf_Xword LibElf::SegmentHeader::get_memsz()
{
    return memsz;
}

Elf_Word LibElf::SegmentHeader::get_flags()
{
    return flags;
}

Elf_Xword LibElf::SegmentHeader::get_align()
{
    return align;
}

void LibElf::SegmentHeader::set_type(Elf_Word value)
{
    type = value;
}

void LibElf::SegmentHeader::set_offset(Elf_Off value)
{
    offset = value;
}

void LibElf::SegmentHeader::set_vaddr(Elf_Addr value)
{
    vaddr = value;
}

void LibElf::SegmentHeader::set_paddr(Elf_Addr value)
{
    paddr = value;
}

void LibElf::SegmentHeader::set_filesz(Elf_Word value)
{
    filesz = value;
}

void LibElf::SegmentHeader::set_memsz(Elf_Word value)
{
    memsz = value;
}

void LibElf::SegmentHeader::set_flags(Elf_Word value)
{
    flags = value;
}

void LibElf::SegmentHeader::set_align(Elf_Word value)
{
    align = value;
}

bool LibElf::SegmentHeader::check_type()
{
    if (PT_TLS < get_type() && get_type() < PT_LOOS)
        return false;

    return true;
}

bool LibElf::SegmentHeader::check_offset()
{
    if (get_type() == PT_NULL)
        return true;

    if (get_offset() > lib_elf->get_filesize())
        return false;

    return true;
}

bool LibElf::SegmentHeader::check_vaddr()
{
    if (get_type() == PT_NULL)
        return true;

    return true;
}

bool LibElf::SegmentHeader::check_paddr()
{
    if (get_type() == PT_NULL)
        return true;

    return true;
}

bool LibElf::SegmentHeader::check_filesz()
{
    if (get_type() == PT_NULL)
        return true;

    if (get_filesz() > lib_elf->get_filesize())
        return false;

    return true;
}

bool LibElf::SegmentHeader::check_memsz()
{
    if (get_type() == PT_NULL)
        return true;

    return true;
}

bool LibElf::SegmentHeader::check_flags()
{
    if (get_type() == PT_NULL)
        return true;

    return true;
}

bool LibElf::SegmentHeader::check_align()
{
    if (get_type() == PT_NULL)
        return true;

    if (get_align() == 0)
        return true;

    // Check if alignment of power of 2
    if (!((get_align() != 0) && !(get_align() & (get_align() - 1))))
        return false;

    return true;
}

std::string LibElf::SegmentHeader::get_type_string()
{
    if (PT_LOOS <= get_type() && get_type() <= PT_HIOS)
        return "OS specific";
    if (PT_LOPROC <= get_type() && get_type() <= PT_HIPROC)
        return "Processor specific";
    if (p_type.find(get_type()) != p_type.end())
        return p_type.at(get_type());

    return "Unknown";
}

std::string LibElf::SegmentHeader::get_offset_string()
{
    return std::to_string(get_offset());
}

std::string LibElf::SegmentHeader::get_vaddr_string()
{
    return std::to_string(get_vaddr());
}

std::string LibElf::SegmentHeader::get_paddr_string()
{
    return std::to_string(get_paddr());
}

std::string LibElf::SegmentHeader::get_filesz_string()
{
    return std::to_string(get_filesz());
}

std::string LibElf::SegmentHeader::get_memsz_string()
{
    return std::to_string(get_memsz());
}

std::string LibElf::SegmentHeader::get_flags_string()
{
    std::string string;

    if ((get_flags() & PF_X) == PF_X)
        Helper::append(&string, p_flags.at(PF_X));
    if ((get_flags() & PF_W) == PF_W)
        Helper::append(&string, p_flags.at(PF_W));
    if ((get_flags() & PF_R) == PF_R)
        Helper::append(&string, p_flags.at(PF_R));
    if ((get_flags() & PF_MASKOS) == PF_MASKOS)
        Helper::append(&string, p_flags.at(PF_MASKOS));
    if ((get_flags() & PF_MASKPROC) == PF_MASKPROC)
        Helper::append(&string, p_flags.at(PF_MASKPROC));

    return string;
}

std::string LibElf::SegmentHeader::get_align_string()
{
    return std::to_string(get_align());
}

bool LibElf::SegmentHeader::read()
{
    // Check if class is set correctly
    if (!elf_identification->is_32_bit() && !elf_identification->is_64_bit())
        return false;
    // Try to read values for 32-bit architecture
    else if (elf_identification->is_32_bit() && !read_32_bit())
        return false;
    // Try to read values for 64-bit architecture
    else if (elf_identification->is_64_bit() && !read_64_bit())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::SegmentHeader::read_32_bit()
{
    // Get stream
    std::ifstream *ifs = lib_elf->get_ifstream();

    // Try to read data
    ifs->read(reinterpret_cast<char *>(&type), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&offset), sizeof(Elf32_Off));
    ifs->read(reinterpret_cast<char *>(&vaddr), sizeof(Elf32_Addr));
    ifs->read(reinterpret_cast<char *>(&paddr), sizeof(Elf32_Addr));
    ifs->read(reinterpret_cast<char *>(&filesz), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&memsz), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&flags), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&align), sizeof(Elf32_Word));

    // Check if stream is good
    if (!ifs->good())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::SegmentHeader::read_64_bit()
{
    // Get stream
    std::ifstream *ifs = lib_elf->get_ifstream();

    // Try to read data
    ifs->read(reinterpret_cast<char *>(&type), sizeof(Elf64_Word));
    ifs->read(reinterpret_cast<char *>(&flags), sizeof(Elf64_Word));
    ifs->read(reinterpret_cast<char *>(&offset), sizeof(Elf64_Off));
    ifs->read(reinterpret_cast<char *>(&vaddr), sizeof(Elf64_Addr));
    ifs->read(reinterpret_cast<char *>(&paddr), sizeof(Elf64_Addr));
    ifs->read(reinterpret_cast<char *>(&filesz), sizeof(Elf64_Xword));
    ifs->read(reinterpret_cast<char *>(&memsz), sizeof(Elf64_Xword));
    ifs->read(reinterpret_cast<char *>(&align), sizeof(Elf64_Xword));

    // Check if stream is good
    if (!ifs->good())
        return false;

    // Everything went fine
    return true;
}

void LibElf::SegmentHeader::convert()
{
    if (elf_identification->is_32_bit())
        convert_32_bit();
    else if (elf_identification->is_64_bit())
        convert_64_bit();
}

void LibElf::SegmentHeader::convert_32_bit()
{
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&type));
    Helper::byteswap_32(reinterpret_cast<Elf32_Off *>(&offset));
    Helper::byteswap_32(reinterpret_cast<Elf32_Addr *>(&vaddr));
    Helper::byteswap_32(reinterpret_cast<Elf32_Addr *>(&paddr));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&filesz));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&memsz));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&flags));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&align));
}

void LibElf::SegmentHeader::convert_64_bit()
{
    Helper::byteswap_32(reinterpret_cast<Elf64_Word *>(&type));
    Helper::byteswap_32(reinterpret_cast<Elf64_Word *>(&flags));
    Helper::byteswap_64(reinterpret_cast<Elf64_Off *>(&offset));
    Helper::byteswap_64(reinterpret_cast<Elf64_Addr *>(&vaddr));
    Helper::byteswap_64(reinterpret_cast<Elf64_Addr *>(&paddr));
    Helper::byteswap_64(reinterpret_cast<Elf64_Xword *>(&filesz));
    Helper::byteswap_64(reinterpret_cast<Elf64_Xword *>(&memsz));
    Helper::byteswap_64(reinterpret_cast<Elf64_Xword *>(&align));
}
