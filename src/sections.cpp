#include "sections.h"
#include "elf_identification.h"
#include "elf_header.h"
#include "lib_elf.h"
#include "helper.h"

LibElf::Sections::Sections(LibElf *lib_elf)
{
    this->lib_elf = lib_elf;
}

LibElf::Sections::~Sections()
{
    this->clear();
}

bool LibElf::Sections::load()
{
    // Try to read section headers
    if (!read_headers())
        return false;

    // Try to read section data
    if (!read_sections())
        return false;

    // Set flag
    ok = true;

    // Everything went fine
    return true;
}

bool LibElf::Sections::save()
{
    // Try to write section headers data
    if (!write_headers())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::Sections::is_ok()
{
    return ok;
}

void LibElf::Sections::clear()
{
    // Reset flag
    ok = false;

    // Clear vectors
    sections.clear();
    headers.clear();
}

LibElf::SectionHeader *LibElf::Sections::get_header(Elf_Half shndx)
{
    return headers.at(shndx).get();
}

LibElf::Section *LibElf::Sections::get_section(Elf_Half shndx)
{
    return sections.at(shndx).get();
}

bool LibElf::Sections::read_headers()
{
    // Set offset for section headers to read
    Elf_Off sh_off = lib_elf->get_elf_header()->get_shoff();
    lib_elf->get_ifstream()->seekg(sh_off);

    for (Elf_Half i = 0; i < lib_elf->get_elf_header()->get_shnum(); ++i)
    {
        // Create new section header
        auto header = std::make_shared<SectionHeader>(lib_elf);

        // Try to section header data
        if (!header->load())
            return false;

        // Save pointer
        headers.push_back(header);
    }

    // Everything went fine
    return true;
}

bool LibElf::Sections::read_sections()
{
    for (Elf_Half i = 0; i < lib_elf->get_elf_header()->get_shnum(); ++i)
    {
        SectionHeader *header = get_header(i);

        // Create new section
        auto section = std::make_shared<Section>(lib_elf, i);

        // If header's type is NOBITS then skip loading
        if (header->get_type() != SHT_NOBITS)
            // Try to load data to section
            if (!section->load())
                return false;

        // Save pointer
        sections.push_back(section);
    }

    // Everything went fine
    return true;
}

bool LibElf::Sections::write_headers()
{
    // Set offset for section headers to write
    Elf_Off sh_off = lib_elf->get_elf_header()->get_shoff();
    lib_elf->get_ofstream()->seekp(sh_off);

    for (Elf_Half i = 0; i < headers.size(); ++i)
    {
        // Get section header
        SectionHeader *header = get_header(i);

        // Try to write section header data
        if (!header->save())
            return false;
    }

    // Everything went fine
    return true;
}

LibElf::SectionHeader::SectionHeader(LibElf *lib_elf)
{
    this->lib_elf = lib_elf;
    this->elf_identification = lib_elf->get_elf_identification();
    this->elf_header = lib_elf->get_elf_header();
}

LibElf::SectionHeader::~SectionHeader()
{
}

bool LibElf::SectionHeader::load()
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

bool LibElf::SectionHeader::save()
{
    // Try to write ELF header data
    if (!write())
        return false;

    // Everything went fine
    return true;
}

Elf_Word LibElf::SectionHeader::get_name()
{
    return name;
}

Elf_Word LibElf::SectionHeader::get_type()
{
    return type;
}

Elf_Xword LibElf::SectionHeader::get_flags()
{
    return flags;
}

Elf_Addr LibElf::SectionHeader::get_addr()
{
    return addr;
}

Elf_Off LibElf::SectionHeader::get_offset()
{
    return offset;
}

Elf_Xword LibElf::SectionHeader::get_size()
{
    return size;
}

Elf_Word LibElf::SectionHeader::get_link()
{
    return link;
}

Elf_Word LibElf::SectionHeader::get_info()
{
    return info;
}

Elf_Xword LibElf::SectionHeader::get_addralign()
{
    return addralign;
}

Elf_Xword LibElf::SectionHeader::get_entsize()
{
    return entsize;
}

void LibElf::SectionHeader::set_name(Elf_Word value)
{
    name = value;
}

void LibElf::SectionHeader::set_type(Elf_Word value)
{
    type = value;
}

void LibElf::SectionHeader::set_flags(Elf_Xword value)
{
    flags = value;
}

void LibElf::SectionHeader::set_addr(Elf_Addr value)
{
    addr = value;
}

void LibElf::SectionHeader::set_offset(Elf_Off value)
{
    offset = value;
}

void LibElf::SectionHeader::set_size(Elf_Xword value)
{
    size = value;
}

void LibElf::SectionHeader::set_link(Elf_Word value)
{
    link = value;
}

void LibElf::SectionHeader::set_info(Elf_Word value)
{
    info = value;
}

void LibElf::SectionHeader::set_addralign(Elf_Xword value)
{
    addralign = value;
}

void LibElf::SectionHeader::set_entsize(Elf_Xword value)
{
    entsize = value;
}

bool LibElf::SectionHeader::check_name()
{
    Elf_Half string_table_index = lib_elf->get_elf_header()->get_shstrndx();
    SectionHeader *string_table_header =
        lib_elf->get_sections()->get_header(string_table_index);

    if (get_name() >= string_table_header->get_size())
        return false;

    return true;
}

bool LibElf::SectionHeader::check_type()
{
    if (SHT_SYMTAB_SHNDX < get_type() && get_type() < SHT_LOOS)
        return false;

    return true;
}

bool LibElf::SectionHeader::check_flags()
{
    if (get_type() == SHT_NULL)
        return true;

    return true;
}

bool LibElf::SectionHeader::check_addr()
{
    if (get_type() == SHT_NULL)
        return true;

    return true;
}

bool LibElf::SectionHeader::check_offset()
{
    if (get_type() == SHT_NULL)
        return true;

    if (get_offset() > lib_elf->get_filesize())
        return false;

    return true;
}

bool LibElf::SectionHeader::check_size()
{
    if (get_type() == SHT_NULL)
        return true;

    return true;
}

bool LibElf::SectionHeader::check_link()
{
    if (get_type() == SHT_NULL)
        return true;

    return true;
}

bool LibElf::SectionHeader::check_info()
{
    if (get_type() == SHT_NULL)
        return true;

    return true;
}

bool LibElf::SectionHeader::check_addralign()
{
    if (get_type() == SHT_NULL)
        return true;

    if (get_addralign() == 0)
        return true;

    // Check if alignment of power of 2
    if (!((get_addralign() != 0) && !(get_addralign() & (get_addralign() - 1))))
        return false;

    return true;
}

bool LibElf::SectionHeader::check_entsize()
{
    if (get_type() == SHT_NULL)
        return true;

    return true;
}

std::string LibElf::SectionHeader::get_name_string()
{
    Elf_Half string_table_index = lib_elf->get_elf_header()->get_shstrndx();
    Section *string_table =
        lib_elf->get_sections()->get_section(string_table_index);

    return string_table->get_pointer(get_name());
}

std::string LibElf::SectionHeader::get_type_string()
{
    if (SHT_LOOS <= get_type() && get_type() <= SHT_HIOS)
        return "OS specific";
    if (SHT_LOPROC <= get_type() && get_type() <= SHT_HIPROC)
        return "Processor specific";
    if (SHT_LOUSER <= get_type() && get_type() <= SHT_HIUSER)
        return "Application specific";
    if (sh_type.find(get_type()) != sh_type.end())
        return sh_type.at(get_type());

    return "Unknown";
}

std::string LibElf::SectionHeader::get_flags_string()
{
    std::string string;

    if ((get_flags() & SHF_WRITE) == SHF_WRITE)
        Helper::append(&string, sh_flags.at(SHF_WRITE));
    if ((get_flags() & SHF_ALLOC) == SHF_ALLOC)
        Helper::append(&string, sh_flags.at(SHF_ALLOC));
    if ((get_flags() & SHF_EXECINSTR) == SHF_EXECINSTR)
        Helper::append(&string, sh_flags.at(SHF_EXECINSTR));
    if ((get_flags() & SHF_MERGE) == SHF_MERGE)
        Helper::append(&string, sh_flags.at(SHF_MERGE));
    if ((get_flags() & SHF_STRINGS) == SHF_STRINGS)
        Helper::append(&string, sh_flags.at(SHF_STRINGS));
    if ((get_flags() & SHF_INFO_LINK) == SHF_INFO_LINK)
        Helper::append(&string, sh_flags.at(SHF_INFO_LINK));
    if ((get_flags() & SHF_LINK_ORDER) == SHF_LINK_ORDER)
        Helper::append(&string, sh_flags.at(SHF_WRITE));
    if ((get_flags() & SHF_OS_NONCONFORMING) == SHF_OS_NONCONFORMING)
        Helper::append(&string, sh_flags.at(SHF_OS_NONCONFORMING));
    if ((get_flags() & SHF_GROUP) == SHF_GROUP)
        Helper::append(&string, sh_flags.at(SHF_GROUP));
    if ((get_flags() & SHF_TLS) == SHF_TLS)
        Helper::append(&string, sh_flags.at(SHF_TLS));
    if ((get_flags() & SHF_COMPRESSED) == SHF_COMPRESSED)
        Helper::append(&string, sh_flags.at(SHF_COMPRESSED));
    if ((get_flags() & SHF_MASKOS) == SHF_MASKOS)
        Helper::append(&string, sh_flags.at(SHF_MASKOS));
    if ((get_flags() & SHF_MASKPROC) == SHF_MASKPROC)
        Helper::append(&string, sh_flags.at(SHF_MASKPROC));

    return string;
}

std::string LibElf::SectionHeader::get_addr_string()
{
    return std::to_string(get_addr());
}

std::string LibElf::SectionHeader::get_offset_string()
{
    return std::to_string(get_offset());
}

std::string LibElf::SectionHeader::get_size_string()
{
    return std::to_string(get_size());
}

std::string LibElf::SectionHeader::get_link_string()
{
    return std::to_string(get_link());
}

std::string LibElf::SectionHeader::get_info_string()
{
    return std::to_string(get_info());
}

std::string LibElf::SectionHeader::get_addralign_string()
{
    return std::to_string(get_addralign());
}

std::string LibElf::SectionHeader::get_entsize_string()
{
    return std::to_string(get_entsize());
}

bool LibElf::SectionHeader::read()
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

bool LibElf::SectionHeader::read_32_bit()
{
    // Get stream
    std::ifstream *ifs = lib_elf->get_ifstream();

    // Try to read data
    ifs->read(reinterpret_cast<char *>(&name), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&type), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&flags), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&addr), sizeof(Elf32_Addr));
    ifs->read(reinterpret_cast<char *>(&offset), sizeof(Elf32_Off));
    ifs->read(reinterpret_cast<char *>(&size), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&link), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&info), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&addralign), sizeof(Elf32_Word));
    ifs->read(reinterpret_cast<char *>(&entsize), sizeof(Elf32_Word));

    // Check if stream is good
    if (!ifs->good())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::SectionHeader::read_64_bit()
{
    // Get stream
    std::ifstream *ifs = lib_elf->get_ifstream();

    // Try to read data
    ifs->read(reinterpret_cast<char *>(&name), sizeof(Elf64_Word));
    ifs->read(reinterpret_cast<char *>(&type), sizeof(Elf64_Word));
    ifs->read(reinterpret_cast<char *>(&flags), sizeof(Elf64_Xword));
    ifs->read(reinterpret_cast<char *>(&addr), sizeof(Elf64_Addr));
    ifs->read(reinterpret_cast<char *>(&offset), sizeof(Elf64_Off));
    ifs->read(reinterpret_cast<char *>(&size), sizeof(Elf64_Xword));
    ifs->read(reinterpret_cast<char *>(&link), sizeof(Elf64_Word));
    ifs->read(reinterpret_cast<char *>(&info), sizeof(Elf64_Word));
    ifs->read(reinterpret_cast<char *>(&addralign), sizeof(Elf64_Xword));
    ifs->read(reinterpret_cast<char *>(&entsize), sizeof(Elf64_Xword));

    // Check if stream is good
    if (!ifs->good())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::SectionHeader::write()
{
    // Check if class is set correctly
    if (!elf_identification->is_32_bit() && !elf_identification->is_64_bit())
        return false;
    // Try to write values for 32-bit architecture
    else if (elf_identification->is_32_bit() && !write_32_bit())
        return false;
    // Try to write values for 64-bit architecture
    else if (elf_identification->is_64_bit() && !write_64_bit())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::SectionHeader::write_32_bit()
{
    // Get stream
    std::ofstream *ofs = lib_elf->get_ofstream();

    // Try to write data
    ofs->write(reinterpret_cast<char *>(&name), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&type), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&flags), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&addr), sizeof(Elf32_Addr));
    ofs->write(reinterpret_cast<char *>(&offset), sizeof(Elf32_Off));
    ofs->write(reinterpret_cast<char *>(&size), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&link), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&info), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&addralign), sizeof(Elf32_Word));
    ofs->write(reinterpret_cast<char *>(&entsize), sizeof(Elf32_Word));

    // Check if stream is good
    if (!ofs->good())
        return false;

    // Everything went fine
    return true;
}

bool LibElf::SectionHeader::write_64_bit()
{
    // Get stream
    std::ofstream *ofs = lib_elf->get_ofstream();

    // Try to write data
    ofs->write(reinterpret_cast<char *>(&name), sizeof(Elf64_Word));
    ofs->write(reinterpret_cast<char *>(&type), sizeof(Elf64_Word));
    ofs->write(reinterpret_cast<char *>(&flags), sizeof(Elf64_Xword));
    ofs->write(reinterpret_cast<char *>(&addr), sizeof(Elf64_Addr));
    ofs->write(reinterpret_cast<char *>(&offset), sizeof(Elf64_Off));
    ofs->write(reinterpret_cast<char *>(&size), sizeof(Elf64_Xword));
    ofs->write(reinterpret_cast<char *>(&link), sizeof(Elf64_Word));
    ofs->write(reinterpret_cast<char *>(&info), sizeof(Elf64_Word));
    ofs->write(reinterpret_cast<char *>(&addralign), sizeof(Elf64_Xword));
    ofs->write(reinterpret_cast<char *>(&entsize), sizeof(Elf64_Xword));

    // Check if stream is good
    if (!ofs->good())
        return false;

    // Everything went fine
    return true;
}

void LibElf::SectionHeader::convert()
{
    if (elf_identification->is_32_bit())
        convert_32_bit();
    else if (elf_identification->is_64_bit())
        convert_64_bit();
}

void LibElf::SectionHeader::convert_32_bit()
{
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&name));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&type));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&flags));
    Helper::byteswap_32(reinterpret_cast<Elf32_Addr *>(&addr));
    Helper::byteswap_32(reinterpret_cast<Elf32_Off *>(&offset));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&size));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&link));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&info));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&addralign));
    Helper::byteswap_32(reinterpret_cast<Elf32_Word *>(&entsize));
}

void LibElf::SectionHeader::convert_64_bit()
{
    Helper::byteswap_32(reinterpret_cast<Elf64_Word *>(&name));
    Helper::byteswap_32(reinterpret_cast<Elf64_Word *>(&type));
    Helper::byteswap_64(reinterpret_cast<Elf64_Xword *>(&flags));
    Helper::byteswap_64(reinterpret_cast<Elf64_Addr *>(&addr));
    Helper::byteswap_64(reinterpret_cast<Elf64_Off *>(&offset));
    Helper::byteswap_64(reinterpret_cast<Elf64_Xword *>(&size));
    Helper::byteswap_32(reinterpret_cast<Elf64_Word *>(&link));
    Helper::byteswap_32(reinterpret_cast<Elf64_Word *>(&info));
    Helper::byteswap_64(reinterpret_cast<Elf64_Xword *>(&addralign));
    Helper::byteswap_64(reinterpret_cast<Elf64_Xword *>(&entsize));
}

LibElf::Section::Section(LibElf *lib_elf, Elf_Half shndx)
{
    this->lib_elf = lib_elf;
    this->section_header = lib_elf->get_sections()->get_header(shndx);
    this->size = this->section_header->get_size();

    // Prepare vector
    data.resize(size);
}

LibElf::Section::~Section()
{
}

bool LibElf::Section::load()
{
    // Get stream
    std::ifstream *ifs = lib_elf->get_ifstream();

    // Set offset for data to read
    ifs->seekg(section_header->get_offset());

    // Try to read data
    ifs->read(&data[0], section_header->get_size());

    // Check if stream is good
    if (!ifs->good())
        return false;

    // Everything went fine
    return true;
}

char *LibElf::Section::get_pointer(Elf_Xword i)
{
    // Prevent from returning wrong pointer
    if (i >= size)
        return &data[0];

    return &data[i];
}
