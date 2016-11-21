
#include "config.h"

#include <math.h>
#include <sys/types.h>
#include <wchar.h>
#include <stdio.h>

#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <string.h>

#include <QDebug>

#ifdef HAVE_ICONV
#include <iconv.h>
#include "libxls/xlstypes.h"
#else
#include <locale.h>
#include <Windows.h>
#include <malloc.h>
#endif

#include "libxls/cppproxy.h"

// Convert unicode string to to_enc encoding
BYTE* unicode_decode(const BYTE *s, int len, size_t *newlen, const char* to_enc)
{
#if HAVE_ICONV
    // Do iconv conversion
    const char *from_enc = "UTF-16LE";
    BYTE* outbuf = 0;

    if(s && len && from_enc && to_enc)
    {
        size_t outlenleft = len;
        int outlen = len;
        size_t inlenleft = len;
        iconv_t ic = iconv_open(to_enc, from_enc);
        BYTE* src_ptr = (BYTE*) s;
        BYTE* out_ptr = 0;

        if(ic != (iconv_t)-1)
        {
            size_t st;
            outbuf = (BYTE*)malloc(outlen + 1);

            if(outbuf)
            {
                out_ptr = (BYTE*)outbuf;
                while(inlenleft)
                {
                    st = iconv(ic, (char **)&src_ptr, &inlenleft, (char **)&out_ptr,(size_t *) &outlenleft);
                    if(st == (size_t)(-1))
                    {
                        if(errno == E2BIG)
                        {
                            size_t diff = out_ptr - outbuf;
                            outlen += inlenleft;
                            outlenleft += inlenleft;
                            outbuf = (BYTE*)realloc(outbuf, outlen + 1);
                            if(!outbuf)
                            {
                                break;
                            }
                            out_ptr = outbuf + diff;
                        }
                        else
                        {
                            free(outbuf), outbuf = NULL;
                            break;
                        }
                    }
                }
            }
            iconv_close(ic);
        }
        outlen -= outlenleft;

        if (newlen)
        {
            *newlen = outbuf ? outlen : 0;
        }
        if(outbuf)
        {
            outbuf[outlen] = 0;
        }
    }
    return outbuf;
#else
    Q_UNUSED(to_enc);
    len = len / 2;
    // Do wcstombs conversion
    wchar_t *orig = NULL;
    char *converted = NULL;
    int count, count2;

    if (setlocale(LC_CTYPE, "") == NULL) {
        printf("setlocale failed: %d\n", errno);
        return (BYTE *)"*null*";
    }

    orig = (wchar_t *)alloca(sizeof(wchar_t) * (len + 1));
    memcpy(orig, s, sizeof(wchar_t) * len);
    orig[len] = NULL;

    // count = wcstombs(NULL, (wchar_t*)orig, 0);
    count = WideCharToMultiByte( CP_UTF8, 0, orig, -1, NULL, NULL, NULL, NULL );

    // qDebug() << QString::fromUtf16((ushort *)s) << ", len : " << QString::number(len) << ", count : " << QString::number(count);
    if (count <= 0) {
        if (newlen) *newlen = 0;
        return NULL;
    }

    converted = (char *)calloc(count, sizeof(char));
    // count2 = wcstombs(converted, (wchar_t*)orig, count+1);
    count2 = WideCharToMultiByte( CP_UTF8, 0, orig, -1, converted, count, NULL, NULL );
    converted[count - 1] = '\0';
    if (count2 <= 0) {
        printf("wcstombs failed (%d)\n", len);
        if (newlen) *newlen = 0;
        return (BYTE *)converted;
    } else {
        if (newlen) *newlen = count2;
        return (BYTE *)converted;
    }
#endif
}
