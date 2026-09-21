#include "utils.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <bits/chrono.h>

namespace timeutil {

void currentTime() {
	// 获取当前时间
	auto now = std::chrono::system_clock::now();
	auto now_time_t = std::chrono::system_clock::to_time_t(now);

	// 提取毫秒部分
	auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		now.time_since_epoch()) % 1000;

	// 转换为本地时间
	std::tm local = *std::localtime(&now_time_t);

	std::cout << "current time: " 
			  << std::put_time(&local, "%Y-%m-%d %H:%M:%S")
			  << "." << std::setfill('0') << std::setw(3) << now_ms.count()
		 	  << std::endl;
}

} // namespace timeutil