#include <CommunicationParameters.h>
#include <iostream>

int main()
{
	CommunicationParameters deneme;

	deneme.updateParameterValue("PortNo", 1000);

	auto result = deneme.getParameterValue("PortNo");

	if (result)
		std::cout << "PortNumber is: " << std::any_cast<int>(result.value()) << "\n";
	
	auto result2 = deneme.getParameterValue("PortNo2");
	
	int portNo;
	if (deneme.getParameterValue<int>("PortNo", portNo))
		std::cout << "PortNumber is: " << portNo << "\n";

	auto result3= deneme.getParameterValue("PortNo2");

	if (result3 == std::nullopt)
		std::cout << "No parameter is found named as PortNo2!" << "\n";

	return 0;
}