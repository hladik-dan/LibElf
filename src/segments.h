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
    class SegmentHeader;
    class Segment;

    class Segments
    {
        public:
            Segments(LibElf *lib_elf);
            ~Segments();

            bool load();
            bool save();
            bool is_ok();
            void clear();

            SegmentHeader *get_header(Elf_Half shndx);

        private:
            bool read_headers();
            bool write_headers();

        private:
            bool ok = false;

            LibElf *lib_elf;

            std::vector<std::shared_ptr<SegmentHeader>> headers;
    };

    class SegmentHeader
    {
        public:
            SegmentHeader(LibElf *lib_elf);
            ~SegmentHeader();

            bool load();
            bool save();

            Elf_Word get_type();
            Elf_Off get_offset();
            Elf_Addr get_vaddr();
            Elf_Addr get_paddr();
            Elf_Xword get_filesz();
            Elf_Xword get_memsz();
            Elf_Word get_flags();
            Elf_Xword get_align();

            void set_type(Elf_Word value);
            void set_offset(Elf_Off value);
            void set_vaddr(Elf_Addr value);
            void set_paddr(Elf_Addr value);
            void set_filesz(Elf_Word value);
            void set_memsz(Elf_Word value);
            void set_flags(Elf_Word value);
            void set_align(Elf_Word value);

            bool check_type();
            bool check_offset();
            bool check_vaddr();
            bool check_paddr();
            bool check_filesz();
            bool check_memsz();
            bool check_flags();
            bool check_align();

            std::string get_type_string();
            std::string get_offset_string();
            std::string get_vaddr_string();
            std::string get_paddr_string();
            std::string get_filesz_string();
            std::string get_memsz_string();
            std::string get_flags_string();
            std::string get_align_string();

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

            Elf_Word type = 0;
            Elf_Word flags = 0;
            Elf_Off offset = 0;
            Elf_Addr vaddr = 0;
            Elf_Addr paddr = 0;
            Elf_Xword filesz = 0;
            Elf_Xword memsz = 0;
            Elf_Xword align = 0;
    };
}
