#include <malloc.h>
#include "../include/file_reader.h"
#include "../include/jvm_structs.h"
#include <stdio.h>

const char *geninf_template = ".geninf:\n\tminver %s\n\tmajver %s\n\tcpool %s\n\taccf %s\n\ttclass %s\n\tsclass %s\n\ticnt %s\n\tfcnt %s\n\tmcnt %s\n\tacnt %s\n\n";

u8 read_bytes_to_u8(const char *bytecode, unsigned int *b_ptr) {
    unsigned int dref_b_ptr = *b_ptr;
    u8 ret_val = ((unsigned long long) *(bytecode + dref_b_ptr)) << 56
                                 | ((unsigned long long) *(bytecode + dref_b_ptr + 1)) << 48
                                 | ((unsigned long long) *(bytecode + dref_b_ptr + 2)) << 40
                                 | ((unsigned long long) *(bytecode + dref_b_ptr + 3)) << 32
                                 | ((unsigned long long) *(bytecode + dref_b_ptr + 4)) << 24
                                 | ((unsigned long long) *(bytecode + dref_b_ptr + 5)) << 16
                                 | ((unsigned long long) *(bytecode + dref_b_ptr + 6)) << 8
                                 | ((unsigned long long) *(bytecode + dref_b_ptr + 7));
    *b_ptr = dref_b_ptr + 8;
    return ret_val;
}

u4 read_bytes_to_u4(const char *bytecode, unsigned int *b_ptr) {
    unsigned int dref_b_ptr = *b_ptr;
    u4 ret_val = *(bytecode + dref_b_ptr) << 24
                           | *(bytecode + dref_b_ptr + 1) << 16
                           | *(bytecode + dref_b_ptr + 2) << 8
                           | *(bytecode + dref_b_ptr + 3);
    *b_ptr = dref_b_ptr + 4;
    return ret_val;
}

u2 read_bytes_to_u2(const char *bytecode, unsigned int *b_ptr) {
    unsigned int dref_b_ptr = *b_ptr;
    u2 ret_val = *(bytecode + dref_b_ptr) << 8
                           | *(bytecode + dref_b_ptr + 1);
    *b_ptr = dref_b_ptr + 2;
    return ret_val;
}

void read_magic(ClassFile *classFile, char *bytecode, unsigned int *b_ptr) {
    u4 magic = read_bytes_to_u4(bytecode, b_ptr);
    classFile->magic = magic;
}

void read_ver(ClassFile *classFile, char *bytecode, unsigned int *b_ptr) {
    u2 minor = read_bytes_to_u2(bytecode, b_ptr);
    u2 major = read_bytes_to_u2(bytecode, b_ptr);
    classFile->minor_version = minor;
    classFile->major_version = major;
}

void read_cp(ClassFile *classFile, char *bytecode, unsigned int *b_ptr) {
    u2 cp_cnt = read_bytes_to_u2(bytecode, b_ptr);

    classFile->constant_pool_count = cp_cnt;
}

void decompile_from_file(char *filename, char *out_path) {
    char *bytecode = read_raw_bytecode_from_file(filename);

    unsigned int *ptr = (unsigned int *) malloc(sizeof(unsigned int *));
    *ptr = 0;

    ClassFile *classFile = (ClassFile *) malloc(sizeof(ClassFile *));

    read_magic(classFile, bytecode, ptr);
    read_ver(classFile, bytecode, ptr);
}

void decompile_from_files(char **filename_array, int count, char *out_path) {
    for (int i = 0; i < count; ++i) {
        char *filename = *(filename_array + i);
        decompile_from_file(filename, out_path);
    }
}

int main() {

    decompile_from_file("D:\\IT\\C\\JVMA\\AutoKick.class", NULL);

    return 0;
}
