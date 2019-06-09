#include "QTCIExampleLibrary.h"
#include <vector>
#include <algorithm>

QTCIExampleLibrary::QTCIExampleLibrary()
{
}

void QTCIExampleLibrary::performSummation(int numCount)
{
	int result{ 0 };

	std::vector<int> v(numCount);
	std::iota(std::begin(v), std::end(v), 0);

	emit summationCompleted(std::accumulate(v.begin(), v.end(), 0));
}
