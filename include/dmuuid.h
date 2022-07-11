
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

#include <string.h>
#include <stdio.h>

#ifndef WIN32
#include <ctype.h>
#include <uuid/uuid.h>
#else
#include <rpc.h>
#endif

#include <iostream>
#include <string>

#ifndef _MSC_VER // assume i386
typedef   signed char      i8;
typedef unsigned char      u8;
typedef          short     i16;
typedef unsigned short     u16;
typedef          int       i32;
typedef unsigned int       u32;
typedef          long long i64;
typedef unsigned long long u64;
#else // we're in windoze
typedef          __int8  i8;
typedef unsigned __int8  u8;
typedef          __int16 i16;
typedef unsigned __int16 u16;
typedef          __int32 i32;
typedef unsigned __int32 u32;
typedef          __int64 i64;
typedef unsigned __int64 u64;
#endif

#ifdef WIN32
#pragma comment(lib,"rpcrt4.lib")
#endif

/**
 * A Universal Unique IDentifier. This is a 128-bit number that is
 * statistically guaranteed to be unique.
 *
 *
 * \example
 * germ::UUID uuid1("ac4db2a0-51df-40a9-8770-be070630370e");
 * germ::UUID uuid2 = germ:UUID::generate();
 * \endexample
 */
class CUUID
{
public:
    /** The null or empty UUID. */
    static const CUUID NullUUID;

public:
    /**
     * Creates a null UUID. This will initialize the data to all zeros.
     */
    CUUID()
        : mUuid(NullUUID.mUuid)
    {}
    /**
     * Creates a UUID from the string representation. The expected format of
     * the string is: "8x-4x-4x-2x2x-2x2x2x2x2x2x".
     */
    CUUID(const std::string& uuid)
    {
        makeFromString(uuid);
    }
    /**
     * Copies the given UUID.
     */
    CUUID(const CUUID& uuid)
    {
        memcpy(&mUuid, &uuid.mUuid, sizeof(germ_uuid_t));
    }
    /**
     * Copies the given UUID into this UUID.
     */
    inline CUUID& operator=(const CUUID& uuid)
    {
        // Make sure this isn't an assignment against ourselves
        if (&uuid != this)
        {
            memcpy(&mUuid, &uuid.mUuid, sizeof(germ_uuid_t));
        }

        return *this;
}
    /**
     * Generates a new UUID.
     */
    inline static CUUID generate()
    {
        CUUID result;

        // Generate the CUUID
#ifndef WIN32
        uuid_t uuid;
        uuid_generate(uuid);
        memcpy(&result.mUuid.standard, uuid, sizeof(germ_uuid_t));
#else
        UUID   uuid;
        if (UuidCreate(&uuid) == RPC_S_OK)
        {
            unsigned   char* strUuid;
            if (UuidToStringA(&uuid, &strUuid) == RPC_S_OK)
            {
                result.makeFromString(std::string((char*)strUuid));
                if (RpcStringFreeA(&strUuid) != RPC_S_OK)
                    printf("RpcStringFree   fail!\n");
            }
            else
            {
                printf("UuidToString   fail!\n");
            }
        }
        else
        {
            printf("UuidCreate   fail!\n");
        }

#endif
        return result;
    }
public:
    /**
     * Tests if this UUID in null. The UUID is null if all the data is 0.
     */
    inline bool isNull() const
    {
        return operator==(NullUUID);
    }
    /**
     * Gets the string representation of this UUID.
     */
    inline std::string str() const
    {
        char guid_str[37];

        // Create the formatted string
#ifndef WIN32
        snprintf(guid_str, 37,
            "%08lx-%04hx-%04hx-%02x%02x-%02x%02x%02x%02x%02x%02x",
            mUuid.standard.m0,
            mUuid.standard.m1,
            mUuid.standard.m2,
            (u16)mUuid.standard.m3,
            (u16)mUuid.standard.m4,
            (u16)mUuid.standard.m5[0],
            (u16)mUuid.standard.m5[1],
            (u16)mUuid.standard.m5[2],
            (u16)mUuid.standard.m5[3],
            (u16)mUuid.standard.m5[4],
            (u16)mUuid.standard.m5[5]
        );
#else
        _snprintf(guid_str, 37,
            "%08lx-%04hx-%04hx-%02x%02x-%02x%02x%02x%02x%02x%02x",
            mUuid.standard.m0,
            mUuid.standard.m1,
            mUuid.standard.m2,
            (u16)mUuid.standard.m3,
            (u16)mUuid.standard.m4,
            (u16)mUuid.standard.m5[0],
            (u16)mUuid.standard.m5[1],
            (u16)mUuid.standard.m5[2],
            (u16)mUuid.standard.m5[3],
            (u16)mUuid.standard.m5[4],
            (u16)mUuid.standard.m5[5]
        );
#endif
        return std::string(guid_str);
    }

public:
    /**
     * Tests if this UUID is equal to the given UUID.
     */
    inline bool operator==(const CUUID& uuid) const
    {
        return ((mUuid.packed.p0 == uuid.mUuid.packed.p0) &&
            (mUuid.packed.p1 == uuid.mUuid.packed.p1) &&
            (mUuid.packed.p2 == uuid.mUuid.packed.p2) &&
            (mUuid.packed.p3 == uuid.mUuid.packed.p3));
    }
    /**
     * Tests if this UUID is not equal to the given UUID.
     */
    inline bool operator!=(const CUUID& uuid) const
    {
        return !operator==(uuid);
    }
    /**
     * Tests if this UUID is less that the given UUID.
     */
    inline bool operator<(const CUUID& uuid) const
    {
        bool is_less(false);

        // Check first 4 bytes
        if (mUuid.packed.p0 < uuid.mUuid.packed.p0)
        {
            is_less = true;
        }
        else if (mUuid.packed.p0 == uuid.mUuid.packed.p0)
        {
            // Check second 4 bytes
            if (mUuid.packed.p1 < uuid.mUuid.packed.p1)
            {
                is_less = true;
            }
            else if (mUuid.packed.p1 == uuid.mUuid.packed.p1)
            {
                // Check third 4 bytes
                if (mUuid.packed.p2 < uuid.mUuid.packed.p2)
                {
                    is_less = true;
                }
                else if (mUuid.packed.p2 == uuid.mUuid.packed.p2)
                {
                    // Check last 4 bytes
                    if (mUuid.packed.p3 < uuid.mUuid.packed.p3)
                    {
                        is_less = true;
                    }
                }
            }
        }

        return is_less;
    }
private:
    /**
     * Parses a UUID out of the given string.
     */
    inline void makeFromString(const std::string& uuid)
    {
        // Use a u16 buffer for the 8 bit values to avoid alignment problems
        u16 buf[8];
        sscanf(uuid.c_str(),
            "%08lx-%04hx-%04hx-%02hx%02hx-%02hx%02hx%02hx%02hx%02hx%02hx",
            &mUuid.standard.m0,
            &mUuid.standard.m1,
            &mUuid.standard.m2,
            &buf[0],
            &buf[1],
            &buf[2],
            &buf[3],
            &buf[4],
            &buf[5],
            &buf[6],
            &buf[7]
        );

        // Fill in the remainder of mUuid
        mUuid.standard.m3 = (u8)buf[0];
        mUuid.standard.m4 = (u8)buf[1];
        for (int i = 2; i < 8; ++i)
        {
            mUuid.standard.m5[i - 2] = (u8)buf[i];
        }
    }
private:
    /**
     * Internally store the UUID as a 128-bit union of differing ways to
     * access the memory therein.
     */
    union germ_uuid_t
    {
        /** Standard UUID memory layout. */
        struct standard_
        {
            u32 m0;
            u16 m1;
            u16 m2;
            u8  m3;
            u8  m4;
            u8  m5[6];
        } standard;

        /** Packed UUID memory layout. */
        struct packed_
        {
            u32 p0;
            u32 p1;
            u32 p2;
            u32 p3;
        } packed;
    };

    germ_uuid_t mUuid;
    };

const CUUID CUUID::NullUUID("00000000-0000-0000-0000-000000000000");

/**
 * Writes the string representation of the given UUID to the give stream.
 */
inline std::ostream& operator<<(std::ostream& out, const CUUID& uuid)
{
    return out << uuid.str();
}

#endif // __DM_UUID_H_INCLUDE__
