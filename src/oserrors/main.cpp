

#include "../../include/oserrors.h"

#include <cstring>
#include <cstdio>

namespace oserr
{

Code::operator int() {
   return error;
}

Code::Code(int e): error(e) {}


void raise(Code lastError /*= cur()*/,
        const char* const additional /*= NULL*/){
    // 获取错误信息
    auto error_message = msg(lastError);

    // 创建一个 std::error_code 对象
    std::error_code ec(lastError, std::system_category());

    // 抛出 std::system_error 异常，并包含错误信息
    if (*additional) {
      error_message += "\nadditional mesage: ";
      error_message += additional;
    }
    throw std::system_error(ec, error_message);
}

#ifdef _WIN32

#include <windows.h>
#include <string>
Code cur() {
    return Code(GetLastError());
}

static
std::string msg(Code error) {
    DWORD error_code = error;
    // 用来接收错误信息的缓冲区
    static wchar_t buffer[256];
    buffer[0] = 0;

    // 尝试获取错误信息
    if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buffer, sizeof(buffer) / sizeof(char), NULL) == 0) {
        // 如果 FormatMessage 失败，返回一个默认错误信息
        return "Unknown error";
    }

    // 去除字符串末尾的换行符和回车符
    size_t end_of_message = strlen(buffer) - 1;
    while (end_of_message > 0 && (buffer[end_of_message] == '\n' || buffer[end_of_message] == '\r')) {
        buffer[end_of_message] = '\0';
        --end_of_message;
    }

    return buffer;
}


#else
#include <cerrno>
#include <sys/stat.h>
Code cur() {
    return Code(errno);
}

//std::system_category().default_error_condition(err)
std::string msg(Code e) {
    return strerror(e);
}

#endif

} // namespace oserr
