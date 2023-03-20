#ifndef UUID_H_INCLUDED
#define UUID_H_INCLUDED
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
{
#endif

    struct uuuid
    {
        unsigned char bytes[16];
    };

    /**
     * Set uuid to the null_uuid.
     */
    void uuid0_generate(struct uuuid *res);

    /**
     * Generate an uuid of version 4 ( Random ) into res.
     * @note res will be the null_uuid on failure.
     */
    void uuid4_generate(struct uuuid *res);

    /**
     * Return the type of the provided uuid.
     *
     * @return 0 if it is the null-uuid
     *         1 MAC address & date-time
     *         2 DCE Security
     *         3 MD5 hash & namespace
     *         4 Random
     *         5 SHA-1 hash & namespace
     *
     *         -1 on an invalid uuid.
     */
    int uuid_type(struct uuuid *id);

    /**
     * Converts an uuid to string.
     * @param id uuid to convert.
     * @param out pointer to char-buffer where to write uuid, uuid is NOT 0-terminated
     *            and is expected to be at least 36 bytes.
     * @return out
     */
    char *uuid_to_string(struct uuuid *id, char *out);

    /**
     * Convert a string to an uuid.
     * @param str to convert.
     * @param out uuid to parse to.
     * @return true on success.
     */
    bool uuid_from_string(const unsigned char *str, struct uuuid *out);

    /**
     * Copy uuid from src to dst.
     */
    void uuuid_copy(const struct uuuid *src, struct uuuid *dst);

#ifdef __cplusplus
}

struct _uuid_to_str
{
    char str[37];
    _uuid_to_str(struct uuuid *id)
    {
        uuid_to_string(id, str);
        str[36] = '\0';
    }
};

/**
 * Helper macro to convert uuid to string.
 */
#define UUID_TO_STRING(id) _uuid_to_str(id).str

#endif // __cplusplus

#if defined(UUID_IMPLEMENTATION)

#endif // UUID_IMPLEMENTATION

#endif // UUID_H_INCLUDED