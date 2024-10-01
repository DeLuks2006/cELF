#ifndef print_h
#include "elf.h"

const char* get_ph_type(uint32_t type); 
void printELF(Elf64_Ehdr* elf_header);
void printPH(Elf64_Phdr* program_header);
#endif // !print_h
