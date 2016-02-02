#include "Common.h"

namespace common{
	inline std::string TimeDiff(std::chrono::time_point<std::chrono::steady_clock> start){
		constexpr char app[] = { 'n', 'u', 'm' };
		auto diff = (long double)std::chrono::nanoseconds(timer.now() - start).count();

		int i = 0;
		while (diff > 1000.f && i <= 2){
			diff /= 1000.f;
			i++;
		}

		std::ostringstream str;
		str << std::setprecision(2) << std::fixed << diff << " ";
		if (i <= 2)
			str << app[i];
		str << "s";
		return std::string(str.str());
	}
}