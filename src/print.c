#include "../include/print.h"

const char* get_ph_type(uint32_t type) {
  switch(type) {
    case 0:              return "PT_NULL";
    case 1:              return "PT_LOAD";
    case 2:              return "PT_DYNAMIC";
    case 3:              return "PT_INTERP";
    case 4:              return "PT_NOTE";
    case 5:              return "PT_SHLIB";
    case 6:              return "PT_PHDR";
    case 7:              return "PT_TLS";
    case 8:              return "PT_NUM";
    case 0x60000000:     return "PT_LOOS";
    case 0x6474e550:     return "PT_GNU_EH_FRAME";
    case 0x6474e551:     return "PT_GNU_STACK";
    case 0x6474e552:     return "PT_GNU_RELRO";
    case 0x6474e553:     return "PT_GNU_PROPERTY";
    case 0x6474e554:     return "PT_GNU_SFRAME";
    case 0x6ffffffa:     return "PT_LOSUNW / PT_SUNWBSS";
    case 0x6ffffffb:     return "PT_SUNWSTACK";
    case 0x6fffffff:     return "PT_HISUNW / PT_HIOS";
    case 0x70000000:     return "PT_LOPROC";
    case 0x7fffffff:     return "PT_HIPROC";
    default: return "UNKNOWN";
  }
}

void printELF(Elf64_Ehdr* elf_header) {
  puts("");
  printf("ELF Header = %02X %02X %02X %02X\n", 
         elf_header->e_ident[0], 
         elf_header->e_ident[1], 
         elf_header->e_ident[2], 
         elf_header->e_ident[3]
  );
  printf("format: %s\n", (elf_header->e_ident[4] == 1)?"32-bit":(elf_header->e_ident[4] == 2)?"64-bit":"Unknown");
  printf("endian: %s\n", (elf_header->e_ident[5] == 1)?"little":(elf_header->e_ident[4] == 2)?"big":"Unknown");
  printf("version: 0x%02X\n", elf_header->e_ident[6]);
  printf("target os: %02X (too lazy to display the actual name, just look it up)\n", elf_header->e_ident[7]);
  printf("target version: 0x%02X\n", elf_header->e_ident[8]);
  printf("file type: %s\n", (elf_header->e_type == 2)?"executable":(elf_header->e_type == 3)?"shared object":"Unknown");
  printf("machine instruction set: 0x%02X\n", elf_header->e_machine);
  printf("entry point: 0x%lX\n", elf_header->e_entry);
  printf("program header offset: 0x%lX\n", elf_header->e_phoff);
  printf("section header offset: 0x%lX\n", elf_header->e_shoff);
  printf("flags: 0x%X\n", elf_header->e_flags);
  printf("size of ELF header: 0x%X\n", elf_header->e_ehsize);
  printf("size of program header entry: 0x%X\n", elf_header->e_phentsize); // NOTE: and this
  printf("number of program header entries: 0x%X\n", elf_header->e_phnum); // NOTE: and this
  printf("size of section header entry: 0x%X\n", elf_header->e_shentsize);
  printf("number of section header entries: 0x%X\n", elf_header->e_shnum);
  printf("section header string table index: 0x%X\n", elf_header->e_shstrndx);
  puts("");
}

void printPH(Elf64_Phdr* program_header) { 
  puts("");
  printf("type: %s (0x%X)\n", get_ph_type(program_header->p_type), program_header->p_type);
  printf("flags: 0x%X\n", program_header->p_flags);
  printf("file offset: 0x%lX\n", program_header->p_offset);
  printf("virtual addr: 0x%lX\n", program_header->p_vaddr);
  printf("physical addr: 0x%lX\n", program_header->p_paddr);
  printf("sizeof image in segment: 0x%lX\n", program_header->p_filesz);
  printf("sizeof image in memory: 0x%lX\n", program_header->p_memsz);
  printf("alignment: 0x%lX\n", program_header->p_align);
  puts("");
}
