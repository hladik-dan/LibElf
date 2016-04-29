#pragma once

#include "lib_data.h"

namespace LibElf
{
    class LibElf;

    class ElfIdentification
    {
        public:
            ElfIdentification(LibElf *lib_elf);
            ~ElfIdentification();

            bool load();
            bool save();
            bool is_ok();
            void clear();

            bool is_32_bit();
            bool is_64_bit();

            unsigned char get_mag_0() const;
            unsigned char get_mag_1() const;
            unsigned char get_mag_2() const;
            unsigned char get_mag_3() const;
            unsigned char get_class() const;
            unsigned char get_data() const;
            unsigned char get_version() const;
            unsigned char get_osabi() const;
            unsigned char get_abiversion() const;

            void set_mag_0(unsigned char value);
            void set_mag_1(unsigned char value);
            void set_mag_2(unsigned char value);
            void set_mag_3(unsigned char value);
            void set_class(unsigned char value);
            void set_data(unsigned char value);
            void set_version(unsigned char value);
            void set_osabi(unsigned char value);
            void set_abiversion(unsigned char value);

            bool check_mag_0();
            bool check_mag_1();
            bool check_mag_2();
            bool check_mag_3();
            bool check_class();
            bool check_data();
            bool check_version();
            bool check_osabi();
            bool check_abiversion();

            std::string get_mag_0_string() const;
            std::string get_mag_1_string() const;
            std::string get_mag_2_string() const;
            std::string get_mag_3_string() const;
            std::string get_class_string() const;
            std::string get_data_string() const;
            std::string get_version_string() const;
            std::string get_osabi_string() const;
            std::string get_abiversion_string() const;

        private:
            bool read();
            bool write();

        private:
            bool ok = false;

            LibElf *lib_elf;

            unsigned char ident[EI_NIDENT] = { 0 };
    };
}
