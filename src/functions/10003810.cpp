#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl FUN_100014c0(char*);
extern "C" unsigned int __cdecl FUN_10010230(unsigned int);
extern "C" void __cdecl FUN_10003810(char* param_1)
{
    struct EmlRecord
    {
        unsigned char field_00;
        unsigned char field_01;
        unsigned char field_02;
        unsigned char field_03;
        unsigned int data;
        unsigned char field_08;
        unsigned char field_09;
        unsigned char field_0A;
        unsigned char field_0B;
        unsigned int field_0C;
        unsigned int field_10;
        unsigned int field_14;
    };

    extern unsigned int DAT_1003b700[];
    extern unsigned short DAT_1003bd8c;
    extern unsigned int DAT_10024650;


    extern void* __cdecl fopen(char*, char*);
    extern char* __cdecl fgets(char*, int, void*);
    extern int __cdecl FID_conflict__sscanf(const char*, const char*, ...);
    extern void* __cdecl FID_conflict__memcpy(void*, const void*, unsigned int);
    extern int __cdecl fclose(void*);

    char local_4e0[512];
    char local_2e0[512];
    unsigned int local_e0;
    unsigned int local_dc;
    unsigned int local_d8;
    unsigned int local_d4[40];
    unsigned int local_34 = 0;
    unsigned int local_30;
    unsigned int local_2c;
    int local_24;
    unsigned int local_20;
    unsigned int local_1c;
    unsigned int local_18;
    unsigned int local_14;
    unsigned int local_28;
    void* local_10;
    int local_c;
    unsigned int local_8;

    FUN_100014c0((char*)"Reading eml file %s");

    local_10 = fopen(param_1, (char*)"rt");

    do
    {
        do
        {
            fgets(local_2e0, 0x200, local_10);
        } while (local_2e0[0] == '#');
    } while (local_2e0[0] == ';');

    FID_conflict__sscanf(
        local_2e0,
        "%d %d",
        &DAT_1003b700[(unsigned int)DAT_1003bd8c * 3],
        &local_30);

    *(unsigned short*)((unsigned char*)DAT_1003b700 +
                       (unsigned int)DAT_1003bd8c * 0x0c + 4) =
        (unsigned short)local_30;

    DAT_1003b700[(unsigned int)DAT_1003bd8c * 3 + 2] =
        FUN_10010230((local_30 & 0xffff) * 0x18);

    local_c = 0;

    if (*(unsigned short*)((unsigned char*)DAT_1003b700 +
                           (unsigned int)DAT_1003bd8c * 0x0c + 4) != 0)
    {
        do
        {
            do
            {
                do
                {
                    fgets(local_2e0, 0x200, local_10);
                } while (local_2e0[0] == '#');
            } while (local_2e0[0] == ';');

            const char* source =
                "%d %d %X %X %X %X %d %f %f %f %d";
            char* destination = local_4e0;

            for (int count = 8; count != 0; count = count - 1)
            {
                *(unsigned int*)destination =
                    *(const unsigned int*)source;
                source = source + 4;
                destination = destination + 4;
            }

            *destination = *source;

            FID_conflict__sscanf(
                local_2e0,
                local_4e0,
                &local_24,
                &local_1c,
                &local_2c,
                &local_18,
                &local_28,
                &local_20,
                &local_14,
                &local_d8,
                &local_dc,
                &local_e0,
                &local_8);

            EmlRecord* record =
                (EmlRecord*)((unsigned char*)
                    DAT_1003b700[(unsigned int)DAT_1003bd8c * 3 + 2] -
                    0x18 + local_24 * 0x18);

            if (local_8 == 0)
            {
                record->data = 0;
                record->field_03 = 0;
            }
            else
            {
                unsigned long long product =
                    (unsigned long long)local_8 * 4;

                unsigned int allocation_size =
                    ((unsigned int)(product >> 32) != 0)
                        ? 0xffffffffu
                        : (unsigned int)product;

                record->data = FUN_10010230(allocation_size);

                unsigned int remaining = local_8;
                char* scan = local_4e0;

                do
                {
                    scan = scan + 1;
                } while (*scan != '\0');

                *(unsigned int*)scan = DAT_10024650;

                for (; remaining != 0; remaining = remaining - 1)
                {
                    scan = local_4e0;

                    do
                    {
                        scan = scan + 1;
                    } while (*scan != '\0');

                    *(unsigned int*)scan = DAT_10024650;
                }

                FID_conflict__sscanf(
                    local_2e0,
                    local_4e0,
                    &local_24,
                    &local_1c,
                    &local_2c,
                    &local_18,
                    &local_28,
                    &local_20,
                    &local_14,
                    &record->field_0C,
                    &record->field_10,
                    &record->field_14,
                    &local_8,
                    &local_34,
                    &local_d4[0],
                    &local_d4[1],
                    &local_d4[2],
                    &local_d4[3],
                    &local_d4[4],
                    &local_d4[5],
                    &local_d4[6],
                    &local_d4[7],
                    &local_d4[8],
                    &local_d4[9],
                    &local_d4[10],
                    &local_d4[11],
                    &local_d4[12],
                    &local_d4[13],
                    &local_d4[14],
                    &local_d4[15],
                    &local_d4[16],
                    &local_d4[17],
                    &local_d4[18],
                    &local_d4[19],
                    &local_d4[20],
                    &local_d4[21],
                    &local_d4[22],
                    &local_d4[23],
                    &local_d4[24],
                    &local_d4[25],
                    &local_d4[26],
                    &local_d4[27],
                    &local_d4[28],
                    &local_d4[29],
                    &local_d4[30],
                    &local_d4[31],
                    &local_d4[32],
                    &local_d4[33],
                    &local_d4[34],
                    &local_d4[35],
                    &local_d4[36],
                    &local_d4[37],
                    &local_d4[38],
                    &local_d4[39]);

                FID_conflict__memcpy(
                    (void*)record->data,
                    local_d4,
                    local_8 * 4);

                record->field_03 = (unsigned char)local_8;
            }

            record->field_02 = (unsigned char)local_34;
            record->field_08 = (unsigned char)local_2c;
            record->field_09 = (unsigned char)local_18;
            record->field_0A = (unsigned char)local_28;
            record->field_0B = (unsigned char)local_20;

            record->field_01 = (unsigned char)local_14;
            record->field_00 = (unsigned char)local_1c;

            local_c = local_c + 1;

        } while (local_c < (int)*(unsigned short*)((unsigned char*)DAT_1003b700 +
                                                   (unsigned int)DAT_1003bd8c *
                                                       0x0c + 4));
    }

    DAT_1003bd8c = DAT_1003bd8c + 1;
    fclose(local_10);
}