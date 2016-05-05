#pragma once

#include <memory>
#include <string>
#include <vector>
#include "lib_data.h"

namespace LibElf
{
    class LibElf;
    class ElfIdentification;
    class ElfHeader;
    class SectionHeader;
    class Section;

    class Sections
    {
        public:
            Sections(LibElf *lib_elf);
            ~Sections();

            bool load();
            bool save();
            bool is_ok();
            void clear();

            SectionHeader *get_header(Elf_Half shndx);
            Section *get_section(Elf_Half shndx);

        private:
            bool read_headers();
            bool read_sections();
            bool write_headers();

        private:
            bool ok = false;

            LibElf *lib_elf;

            std::vector<SectionHeader *> headers;
            std::vector<Section *> sections;
    };

    class SectionHeader
    {
        public:
            SectionHeader(LibElf *lib_elf);
            ~SectionHeader();

            bool load();
            bool save();

            Elf_Word get_name();
            Elf_Word get_type();
            Elf_Xword get_flags();
            Elf_Addr get_addr();
            Elf_Off get_offset();
            Elf_Xword get_size();
            Elf_Word get_link();
            Elf_Word get_info();
            Elf_Xword get_addralign();
            Elf_Xword get_entsize();

            void set_name(Elf_Word value);
            void set_type(Elf_Word value);
            void set_flags(Elf_Xword value);
            void set_addr(Elf_Addr value);
            void set_offset(Elf_Off value);
            void set_size(Elf_Xword value);
            void set_link(Elf_Word value);
            void set_info(Elf_Word value);
            void set_addralign(Elf_Xword value);
            void set_entsize(Elf_Xword value);

            bool check_name();
            bool check_type();
            bool check_flags();
            bool check_addr();
            bool check_offset();
            bool check_size();
            bool check_link();
            bool check_info();
            bool check_addralign();
            bool check_entsize();

            std::string get_name_string();
            std::string get_type_string();
            std::string get_flags_string();
            std::string get_addr_string();
            std::string get_offset_string();
            std::string get_size_string();
            std::string get_link_string();
            std::string get_info_string();
            std::string get_addralign_string();
            std::string get_entsize_string();

        private:
            bool read();
            bool read_32_bit();
            bool read_64_bit();
            bool write();
            bool write_32_bit();
            bool write_64_bit();
            void convert();
            void convert_32_bit();
            void convert_64_bit();

        private:
            LibElf *lib_elf;
            ElfIdentification *elf_identification;
            ElfHeader *elf_header;

            Elf_Word name = 0;
            Elf_Word type = 0;
            Elf_Xword flags = 0;
            Elf_Addr addr = 0;
            Elf_Off offset = 0;
            Elf_Xword size = 0;
            Elf_Word link = 0;
            Elf_Word info = 0;
            Elf_Xword addralign = 0;
            Elf_Xword entsize = 0;
    };

    class Section
    {
        public:
            Section(LibElf *lib_elf, Elf_Half shndx);
            ~Section();

            bool load();
            char *get_pointer(Elf_Xword i);

        private:
            LibElf *lib_elf;
            SectionHeader *section_header;

            Elf_Xword size;
            std::vector<char> data;
    };
}
