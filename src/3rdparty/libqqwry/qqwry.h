/*
 * Copyright 2008 Surf Chen <http://www.surfchen.org>
 *
 *
 * This source code is under the terms of the
 * GNU Lesser General Public License.
 * see <http://www.gnu.org/licenses/lgpl.txt>
 */

#include <stdint.h>

/*
 * ���Լ���addr1��addr2�����ڴ棬�ҵĽ�����:addr1Ϊ64�ֽڣ�addr2Ϊ128�ֽڡ�
 * ����ⲻ���Լ������ڴ棬���ǰѽ��д��addr1��addr2���ڴ档
 * ��������ƿ���ʹ�õ��÷��������ʹ���Լ����ڴ���ơ�
 *
 * addr1�Ǵ�ķ�Χ������������
 * addr2��С�ķ�Χ������������
 *
 * get_location��get_location_by_long��������ǰ�ߴ��ݵ�ip��һ���ַ���������
 * 222.89.22.122�����Ҳ������ͨ�����õĸ�ʽ�����ߴ��ݵ�ip��һ��ʮ���Ƶ�ipv4��ַ
 */
#ifdef __cplusplus
extern "C" {
#endif
int qqwry_get_location(char *addr1,char *addr2,const char *ip,FILE *qqwry_file);
int qqwry_get_location_by_long(char *addr1,char *addr2,const uint32_t ip,FILE *qqwry_file);
#ifdef __cplusplus
}
#endif
