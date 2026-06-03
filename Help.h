//---------------------------------------------------------------------------

#ifndef HelpH
#define HelpH

#include <type_traits>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define ENABLE_DEBUG_OUTPUT 1

#if ENABLE_DEBUG_OUTPUT

// 输出调试信息
template <typename T>
void OutputDebugMsg(const T* lpFormat, ...)
{
//    std::conditional_t<std::is_same<T, char>::value, AnsiString, UnicodeString> pCommonStrBuffer{};

    AnsiString  pCommonStrBuffer{};
    va_list arg_list{};
    va_start(arg_list, lpFormat);
    pCommonStrBuffer.vprintf(lpFormat, arg_list);
    OutputDebugStringA(("调试信息: " + pCommonStrBuffer).c_str());
    va_end(arg_list);
}

#else

template <typename T>
void OutputDebugMsg(const T* lpFormat, ...)
{
}

#endif

void OpenAndInitConsole();

bool IsAddressValid(uintptr_t address);

// 通过偏移数组获取目标数据
template <typename T>
T GetTargetValue(const uintptr_t* OffsetArray = nullptr, size_t ArrayLength = 0, uintptr_t BaseAddress = 0)
{
    // 使用 __assume 提示编译器优化（C++ Builder 支持）
    if (OffsetArray == nullptr || ArrayLength == 0)
    {
        __assume(false); // 告诉编译器这种情况不会发生
        return T{};
    }

    uintptr_t currentAddr = BaseAddress;

    for (size_t i = 0; i < ArrayLength - 1; ++i)
    {
        currentAddr += OffsetArray[i];
        if (!IsAddressValid(currentAddr))
            return T{};
        currentAddr = *reinterpret_cast<uintptr_t*>(currentAddr);
        if (currentAddr == 0)
            return T{};
    }

    // 最终地址
    currentAddr += OffsetArray[ArrayLength - 1];

    OutputDebugMsg("最终地址 = %p", currentAddr);
    // 验证并返回
    if (!IsAddressValid(currentAddr))
        return T{};
    return *reinterpret_cast<T*>(currentAddr);
}

//---------------------------------------------------------------------------
#endif
