// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __DM_UUID_H_INCLUDE__
#define __DM_UUID_H_INCLUDE__

#include <string>
#include <ostream>
#include <cstring> // For memset, memcpy
#include <cstdio>  // For snprintf, sscanf
#include <cstdint> // For standard integer types

#ifdef _WIN32
#include <rpc.h>
#pragma comment(lib, "rpcrt4.lib")
#else
#include <uuid/uuid.h>
#endif

/**
 * @brief A Universal Unique IDentifier. This is a 128-bit number that is
 * statistically guaranteed to be unique.
 *
 * @example
 * CUUID uuid1("ac4db2a0-51df-40a9-8770-be070630370e");
 * CUUID uuid2 = CUUID::generate();
 */
class CUUID
{
private:
    /**
     * @brief Internally store the UUID as a 128-bit union of differing ways to
     * access the memory therein.
     */
    union germ_uuid_t
    {
        /** Standard UUID memory layout (RFC 4122). */
        struct
        {
            uint32_t m0;
            uint16_t m1;
            uint16_t m2;
            uint8_t  m3;
            uint8_t  m4;
            uint8_t  m5[6];
        } standard;

        /** Packed UUID memory layout for efficient comparison. */
        struct
        {
            uint64_t p0;
            uint64_t p1;
        } packed;
    };

public:
    /** The null or empty UUID. */
    static const CUUID NullUUID;

public:
    /**
     * @brief Creates a null UUID. This will initialize the data to all zeros.
     */
    CUUID()
    {
        std::memset(&mUuid, 0, sizeof(germ_uuid_t));
    }
    /**
     * @brief Creates a UUID from the string representation. The expected format of
     * the string is: "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx".
     */
    CUUID(const std::string& uuid)
    {
        makeFromString(uuid);
    }
    /**
     * @brief Copies the given UUID.
     */
    CUUID(const CUUID& uuid)
    {
        std::memcpy(&mUuid, &uuid.mUuid, sizeof(germ_uuid_t));
    }
    /**
     * @brief Copies the given UUID into this UUID.
     */
    inline CUUID& operator=(const CUUID& uuid)
    {
        if (&uuid != this)
        {
            std::memcpy(&mUuid, &uuid.mUuid, sizeof(germ_uuid_t));
        }
        return *this;
    }
    /**
     * @brief Generates a new UUID.
     * @return A new, randomly generated CUUID object. Returns a null UUID on failure.
     */
    inline static CUUID generate()
    {
        CUUID result;

#ifdef _WIN32
        UUID uuid;
        if (UuidCreate(&uuid) == RPC_S_OK)
        {
            // The Windows UUID struct layout is compatible with RFC 4122
            result.mUuid.standard.m0 = uuid.Data1;
            result.mUuid.standard.m1 = uuid.Data2;
            result.mUuid.standard.m2 = uuid.Data3;
            result.mUuid.standard.m3 = uuid.Data4[0];
            result.mUuid.standard.m4 = uuid.Data4[1];
            std::memcpy(result.mUuid.standard.m5, &uuid.Data4[2], 6);
        }
#else
        uuid_t uuid; // This is an array of 16 unsigned chars
        uuid_generate(uuid);
        std::memcpy(&result.mUuid, uuid, sizeof(germ_uuid_t));
#endif
        return result;
    }

public:
    /**
     * @brief Tests if this UUID is null. The UUID is null if all the data is 0.
     */
    inline bool isNull() const
    {
        return (mUuid.packed.p0 == 0) && (mUuid.packed.p1 == 0);
    }
    /**
     * @brief Gets the string representation of this UUID.
     */
    inline std::string str() const
    {
        char guid_str[37];
        std::snprintf(guid_str, sizeof(guid_str),
            "%08x-%04hx-%04hx-%02x%02x-%02x%02x%02x%02x%02x%02x",
            mUuid.standard.m0,
            mUuid.standard.m1,
            mUuid.standard.m2,
            mUuid.standard.m3,
            mUuid.standard.m4,
            mUuid.standard.m5[0],
            mUuid.standard.m5[1],
            mUuid.standard.m5[2],
            mUuid.standard.m5[3],
            mUuid.standard.m5[4],
            mUuid.standard.m5[5]
        );
        return std::string(guid_str);
    }

public:
    /**
     * @brief Tests if this UUID is equal to the given UUID.
     */
    inline bool operator==(const CUUID& uuid) const
    {
        return (mUuid.packed.p0 == uuid.mUuid.packed.p0) &&
               (mUuid.packed.p1 == uuid.mUuid.packed.p1);
    }
    /**
     * @brief Tests if this UUID is not equal to the given UUID.
     */
    inline bool operator!=(const CUUID& uuid) const
    {
        return !operator==(uuid);
    }
    /**
     * @brief Tests if this UUID is less than the given UUID.
     */
    inline bool operator<(const CUUID& uuid) const
    {
        if (mUuid.packed.p0 < uuid.mUuid.packed.p0) return true;
        if (mUuid.packed.p0 > uuid.mUuid.packed.p0) return false;
        return mUuid.packed.p1 < uuid.mUuid.packed.p1;
    }

private:
    /**
     * @brief Parses a UUID out of the given string.
     */
    inline void makeFromString(const std::string& uuid)
    {
        unsigned int buf[8];
        int count = std::sscanf(uuid.c_str(),
            "%08x-%04hx-%04hx-%02x%02x-%02x%02x%02x%02x%02x%02x",
            &mUuid.standard.m0, &mUuid.standard.m1, &mUuid.standard.m2,
            &buf[0], &buf[1], &buf[2], &buf[3],
            &buf[4], &buf[5], &buf[6], &buf[7]);

        if (count == 11) // 3 large fields + 8 byte fields
        {
            mUuid.standard.m3 = static_cast<uint8_t>(buf[0]);
            mUuid.standard.m4 = static_cast<uint8_t>(buf[1]);
            for (int i = 0; i < 6; ++i)
            {
                mUuid.standard.m5[i] = static_cast<uint8_t>(buf[i + 2]);
            }
        }
        else
        {
            // On parse failure, initialize to null
            std::memset(&mUuid, 0, sizeof(germ_uuid_t));
        }
    }

private:
    germ_uuid_t mUuid;
};

const CUUID CUUID::NullUUID("00000000-0000-0000-0000-000000000000");

/**
 * @brief Writes the string representation of the given UUID to the given stream.
 */
inline std::ostream& operator<<(std::ostream& out, const CUUID& uuid)
{
    return out << uuid.str();
}

#endif // __DM_UUID_H_INCLUDE__