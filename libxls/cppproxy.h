#ifndef CPPPROXY_H
#define CPPPROXY_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC BYTE* unicode_decode(const BYTE *s, int len, size_t *newlen, const char* encoding);

#undef EXTERNC

#endif // CPPPROXY_H
