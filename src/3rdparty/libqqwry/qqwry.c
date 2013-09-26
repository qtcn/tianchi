/*
 * Copyright 2008 Surf Chen <http://www.surfchen.org>
 *
 *
 * This source code is under the terms of the
 * GNU Lesser General Public License.
 * see <http://www.gnu.org/licenses/lgpl.txt>
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BE_32(x) ((((uint8_t*)(x))[0]<<24) |\
                  (((uint8_t*)(x))[1]<<16) |\
                  (((uint8_t*)(x))[2]<<8) |\
                  ((uint8_t*)(x))[3])

#define LE_32(x) ((((uint8_t*)(x))[3]<<24) |\
                  (((uint8_t*)(x))[2]<<16) |\
                  (((uint8_t*)(x))[1]<<8) |\
                  ((uint8_t*)(x))[0])

#define LE_24(x) ((((uint8_t*)(x))[2]<<16) |\
                  (((uint8_t*)(x))[1]<<8) |\
                  ((uint8_t*)(x))[0])

#define REDIRECT_TYPE_1 0x01
#define REDIRECT_TYPE_2 0x02
           
static uint32_t ip2long(const char *ip)
{
    uint32_t    ip_long = 0;
    uint8_t     ip_len = strlen(ip);
    uint32_t    ip_sec = 0;
    int8_t      ip_level = 3;
    uint8_t     i, n;
    for (i = 0; i <= ip_len; i++)
    {
        if (i != ip_len && ip[i] != '.' && ip[i] < 48 || ip[i] > 57)
        {
            continue;
        }
        if (ip[i] == '.' || i == ip_len)
        {
            /*too many .*/
            if (ip_level == -1)
            {
                return 0;
            }
            for (n = 0; n < ip_level; n++)
            {
                ip_sec *= 256;
            }
            ip_long += ip_sec;
            if (i == ip_len)
            {
                break;
            }
            ip_level--;
            ip_sec = 0;
        }
        else
        {
            /*char '0' == int 48*/
            ip_sec = ip_sec * 10 + (ip[i] - 48);
        }
    }
    return ip_long;
}

static uint32_t search_index(const uint32_t ip, FILE *qqwry_file)
{
    uint32_t        index_ip;
    uint32_t        index_start;
    uint32_t        index_end;
    uint32_t        index_mid;
    unsigned char   head[8];
    unsigned char   index_bytes[7];

    fread(head, 8, 1, qqwry_file);
    index_start = (uint32_t)LE_32(&head[0]);
    index_end = (uint32_t)LE_32(&head[4]);
    while (1)
    {
        if ((index_end - index_start) == 7)
        {
            break;
        }
        //printf("index:%u:%u\n",index_start,index_end);
        index_mid = index_end / 7 - index_start / 7;
        if (index_mid % 2 == 0)
        {
            index_mid = index_mid / 2;
        }
        else
        {
            index_mid = (index_mid + 1) / 2;
        }
        index_mid = index_start + index_mid * 7;
        fseek(qqwry_file, index_mid, SEEK_SET);
        fread(index_bytes, 7, 1, qqwry_file);
        index_ip = (uint32_t)LE_32(&index_bytes[0]);
        if (index_ip == ip)
        {
            break;
        }
        else if (index_ip < ip)
        {
            index_start=index_mid;
        }
        else
        {
            index_end = index_mid;
        }
    }
    if (index_ip > ip)
    {
        fseek(qqwry_file, index_start, SEEK_SET);
        fread(index_bytes, 7, 1, qqwry_file);
    }
    return (uint32_t)LE_24(&index_bytes[4]);
}

static int readOrJumpRead(char *location, FILE *qqwry_file, 
        const uint32_t data_index)
{
    unsigned char c;
    unsigned char data_index_bytes[3];
    uint32_t jump_data_index = 0;
    if (data_index)
    {
        fseek(qqwry_file, data_index, SEEK_SET);
    }
    c = fgetc(qqwry_file);
    switch (c)
    {
        case REDIRECT_TYPE_2:
        case REDIRECT_TYPE_1:
            fread(data_index_bytes, 3, 1, qqwry_file);
            jump_data_index = LE_24(&data_index_bytes[0]);
            fseek(qqwry_file, jump_data_index, SEEK_SET);
            break;
        default:
            location[strlen(location)] = c;
    }
    if (c)
    {
        while (c = fgetc(qqwry_file))
        {
            location[strlen(location)] = c;
        }
    }
    return 1;
}

static int is_cz88(const char *str)
{
    int i;
    int l = strlen(str) - 7;
    for (i = 0; i < l; i++)
    {
        if (str[i] == 'C'
            && str[i + 1] == 'Z'
            && str[i + 2] == '8'
            && str[i + 3] == '8'
            && str[i + 4] == '.'
            && str[i + 5] == 'N'
            && str[i + 6] == 'E'
            && str[i + 7] == 'T')
        {
            return 1;
        }
    }
    return 0;
}

int qqwry_get_location_by_long(char *addr1, char *addr2, const uint32_t ip,
        FILE *qqwry_file)
{
    unsigned char data_index_bytes[3];
    uint32_t data_index;
    uint32_t addr2_offset;
    unsigned char c;

    if (!qqwry_file)
    {
        return 0;
    }
    fseek(qqwry_file, 0, SEEK_SET);
    data_index = search_index(ip, qqwry_file);
    //fprintf(stderr,"index:%u:%u\n",ftell(qqwry_file),data_index);

    /*ip 4 + mode byte 1*/
    fseek(qqwry_file, data_index + 4, SEEK_SET);
    c = fgetc(qqwry_file);
    if (c == REDIRECT_TYPE_1)
    {
        fread(data_index_bytes, 3, 1, qqwry_file);
        data_index = LE_24(&data_index_bytes[0]);
        fseek(qqwry_file, data_index, SEEK_SET);
        c = fgetc(qqwry_file);
        /*制造一个假的4bytes位移，抵充ip*/
        data_index -= 4;
    }

    if (c == REDIRECT_TYPE_2)
    {
        /*
         * ip 4 + mode byte 1 + addr1 offset 3
         * 这里ip的4个bytes不一定是真的，有可能是上一条注释里提到的情况
         */
        addr2_offset = data_index + 8;
        fread(data_index_bytes, 3, 1, qqwry_file);

        data_index = LE_24(&data_index_bytes[0]);
        fseek(qqwry_file, data_index, SEEK_SET);
        while (c = fgetc(qqwry_file))
        {
            addr1[strlen(addr1)] = c;
        }
        readOrJumpRead(addr2, qqwry_file, addr2_offset);
    }
    else
    {
        addr1[strlen(addr1)] = c;
        while (c = fgetc(qqwry_file))
        {
            addr1[strlen(addr1)] = c;
        }
        readOrJumpRead(addr2, qqwry_file, 0);
    }
    if (is_cz88(addr1))
    {
        addr1[0] = '\0';
    }
    if (is_cz88(addr2))
    {
        addr2[0] = '\0';
    }
    return 1;
}

int qqwry_get_location(char *addr1, char *addr2, const char *ip, FILE *qqwry_file)
{
    return qqwry_get_location_by_long(addr1, addr2, ip2long(ip), qqwry_file);
}
