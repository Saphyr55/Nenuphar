#pragma once

#include <cstdint>
#include <string>
#include <memory>

namespace Nenuphar
{

    using Void = void;

    using Bool = bool;

    using Bit = bool;

    using Char = char;

    using Byte = signed char;

    using Short = short;
    using UShort = unsigned short;

    using Long = long;
    using ULong = unsigned long;

    using UInt8 = std::uint8_t;
    using UInt16 = std::uint16_t;
    using UInt32 = std::uint32_t;
    using UInt64 = std::uint64_t;
    using UInt = std::uint32_t;

    using Int8 = std::int8_t;
    using Int16 = std::int16_t;
    using Int32 = std::int32_t;
    using Int64 = std::int64_t;
    using Int = std::int32_t;

    using Float = float;
    using Double = double;
    using Float32 = float;
    using Float64 = double;

    using Word8 = UInt8;
    using Word16 = UInt16;
    using Word32 = UInt32;
    using Word64 = UInt64;

    using String = std::string;
    using StringView = std::string_view;

    using VoidPtr = void*;

    template<typename T>
    using Ptr = std::unique_ptr<T>;

    template<typename T>
    using WeakPtr = std::weak_ptr<T>;

    template<typename T>
    using UniquePtr = std::unique_ptr<T>;

    template<typename T>
    using SharedRef = std::shared_ptr<T>;


}
